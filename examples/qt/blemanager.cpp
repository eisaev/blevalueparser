#include "blemanager.h"

#include <QDebug>
#include <QLowEnergyConnectionParameters>

#include "bledeviceinfo.h"
#include "bleserviceinfo.h"
#include "blecharacteristicinfo.h"


namespace
{
constexpr int discoveryTimeout = 10000;
constexpr const char enableNotification[2] = { '\x01', '\x00' };
constexpr const char disableNotification[2] = { '\x00', '\x00' };
}

BLEManager::BLEManager(QObject *parent) : QObject{parent}
{
    connect(&m_localDevice, &QBluetoothLocalDevice::hostModeStateChanged,
            this, &BLEManager::hostModeStateChanged);
    connect(&m_localDevice, &QBluetoothLocalDevice::deviceConnected,
            this, &BLEManager::remoteDeviceConnected);
    connect(&m_localDevice, &QBluetoothLocalDevice::deviceDisconnected,
            this, &BLEManager::remoteDeviceDisconnected);
    connect(&m_localDevice, &QBluetoothLocalDevice::pairingFinished,
            this, &BLEManager::pairingFinished);
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
    connect(&m_localDevice, &QBluetoothLocalDevice::pairingDisplayPinCode,
            this, &BLEManager::pairingDisplayPinCode);
    connect(&m_localDevice, &QBluetoothLocalDevice::pairingDisplayConfirmation,
            this, &BLEManager::pairingDisplayConfirmation);
    connect(&m_localDevice, &QBluetoothLocalDevice::error,
            this, &BLEManager::localDeviceError);
#else
    connect(&m_localDevice, &QBluetoothLocalDevice::errorOccurred,
            this, &BLEManager::localDeviceError);
#endif

    if (isActive())
    {
        startDevicesDiscovery();
    }
    else
    {
        m_statusString = tr("Error: No active BT adapters found");
    }
}

BLEManager::~BLEManager()
{
    qDebug() << __FUNCTION__;
    qDeleteAll(m_availableDevices);
    m_availableDevices.clear();
    qDeleteAll(m_availableServices);
    m_availableServices.clear();
    qDeleteAll(m_availableCharacteristics);
    m_availableCharacteristics.clear();
}

bool BLEManager::isActive() const
{
    qDebug() << __FUNCTION__;
    return m_localDevice.isValid() && m_localDevice.hostMode() != QBluetoothLocalDevice::HostPoweredOff;
}

void BLEManager::startDevicesDiscovery()
{
    qDebug() << __FUNCTION__;

    if (!isActive())
    {
        m_statusString = tr("Error: No active BT adapters found");
        emit statusStringUpdated();
        return;
    }

    m_statusString = tr("Devices discovery...");
    emit statusStringUpdated();

    qDeleteAll(m_availableDevices);
    m_availableDevices.clear();

    if (m_discoveryAgent)
    {
        delete m_discoveryAgent;
    }
    m_discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    m_discoveryAgent->setLowEnergyDiscoveryTimeout(discoveryTimeout);

    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &BLEManager::deviceDiscovered);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &BLEManager::deviceDiscoveryFinished);
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::canceled,
            this, &BLEManager::deviceDiscoveryCanceled);
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
    connect(m_discoveryAgent, static_cast<void (QBluetoothDeviceDiscoveryAgent::*)(QBluetoothDeviceDiscoveryAgent::Error)>(&QBluetoothDeviceDiscoveryAgent::error),
            this, &BLEManager::deviceDiscoveryError);
#else
    connect(m_discoveryAgent, &QBluetoothDeviceDiscoveryAgent::errorOccurred,
            this, &BLEManager::deviceDiscoveryError);
#endif

    m_discoveryAgent->start(QBluetoothDeviceDiscoveryAgent::LowEnergyMethod);
    emit isDeviceDiscoveryInProgressUpdated();
}

void BLEManager::stopDevicesDiscovery()
{
    qDebug() << __FUNCTION__;
    if (!m_discoveryAgent)
    {
        return;
    }

    m_discoveryAgent->stop();
}

QVariant BLEManager::statusString() const
{
    return m_statusString;
}

QVariant BLEManager::availableDevices() const
{
    qDebug() << __FUNCTION__;
    return QVariant::fromValue(m_availableDevices);
}

bool BLEManager::isDeviceDiscoveryInProgress() const
{
    qDebug() << __FUNCTION__;
    if (!m_discoveryAgent)
    {
        return false;
    }

    return m_discoveryAgent->isActive();
}

bool BLEManager::isDeviceConnected() const
{
    qDebug() << __FUNCTION__;
    if (!m_controller)
    {
        return false;
    }

    qDebug() << m_controller->state();
    if (m_controller->state() == QLowEnergyController::UnconnectedState ||
        m_controller->state() == QLowEnergyController::ClosingState ||
        m_controller->state() == QLowEnergyController::ConnectingState)
    {
        return false;
    }

    return true;
}

QVariant BLEManager::availableServices() const
{
    qDebug() << __FUNCTION__;
    return QVariant::fromValue(m_availableServices);
}

bool BLEManager::isServicesDiscoveryInProgress() const
{
    qDebug() << __FUNCTION__;
    if (m_controller)
    {
        qDebug() << m_controller->state();
        if (QLowEnergyController::ControllerState::ConnectingState == m_controller->state() ||
            QLowEnergyController::ControllerState::ConnectedState == m_controller->state() ||
            QLowEnergyController::ControllerState::DiscoveringState == m_controller->state())
        {
            return true;
        }
    }

    return false;
}

QVariant BLEManager::availableCharacteristics() const
{
    qDebug() << __FUNCTION__;
    return QVariant::fromValue(m_availableCharacteristics);
}

bool BLEManager::isCharacteristicsDiscoveryInProgress() const
{
    qDebug() << __FUNCTION__;
    if (!m_service)
    {
        return false;
    }

#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
    return m_service->state() == QLowEnergyService::DiscoveringServices;
#else
    return m_service->state() == QLowEnergyService::RemoteServiceDiscovering;
#endif
}

bool BLEManager::isSubscribed() const
{
    qDebug() << __FUNCTION__;
    if (m_notificationDescriptor.isValid() &&
        m_service &&
        m_notificationDescriptor.value() == enableNotification)
    {
        return true;
    }

    return false;
}

QVariant BLEManager::characteristicName() const
{
    qDebug() << __FUNCTION__;
    if (!m_characteristic)
    {
        return "";
    }

    return QVariant::fromValue(m_characteristicName);
}

QVariant BLEManager::characteristicValue() const
{
    qDebug() << __FUNCTION__;
    if (!m_characteristic)
    {
        return "";
    }

    return QVariant::fromValue(m_characteristicValue.toHex(' '));
}

QVariant BLEManager::characteristicValueParsed() const
{
    qDebug() << __FUNCTION__;
    if (!m_characteristic)
    {
        return "";
    }

    auto characteristicType = bvp::CharacteristicType(m_characteristic->uuid().toUInt32());
    auto parsed = m_bleValueParser.make_value(characteristicType,
                                              m_characteristicValue.constData(),
                                              m_characteristicValue.size());

    QString parsedString = QString::fromStdString(parsed->toString());

    return QVariant::fromValue(parsedString);
}

QVariant BLEManager::characteristicIsRead() const
{
    qDebug() << __FUNCTION__;
    if (!m_characteristic)
    {
        return false;
    }

    return m_characteristic->properties().testFlag(QLowEnergyCharacteristic::PropertyType::Read);
}

QVariant BLEManager::characteristicIsNotify() const
{
    qDebug() << __FUNCTION__;
    if (!m_characteristic)
    {
        return false;
    }

    return m_characteristic->properties().testFlag(QLowEnergyCharacteristic::PropertyType::Notify);
}

void BLEManager::hostModeStateChanged(QBluetoothLocalDevice::HostMode state)
{
    qDebug() << __FUNCTION__;
    qDebug() << state;

    if (isActive())
    {
        m_statusString.clear();
    }
    else
    {
        m_statusString = tr("Error: No active BT adapters found");
    }
    emit statusStringUpdated();
}

void BLEManager::remoteDeviceConnected(const QBluetoothAddress &address)
{
    qDebug() << __FUNCTION__;
    qDebug() << address;
}

void BLEManager::remoteDeviceDisconnected(const QBluetoothAddress &address)
{
    qDebug() << __FUNCTION__;
    qDebug() << address;
}

void BLEManager::pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing)
{
    qDebug() << __FUNCTION__;
    qDebug() << address;
    qDebug() << pairing;
}

void BLEManager::pairingDisplayPinCode(const QBluetoothAddress &address, const QString& pin)
{
    qDebug() << __FUNCTION__;
    qDebug() << address;
    qDebug() << pin;
}

void BLEManager::pairingDisplayConfirmation(const QBluetoothAddress &address, const QString& pin)
{
    qDebug() << __FUNCTION__;
    qDebug() << address;
    qDebug() << pin;
}

void BLEManager::localDeviceError(QBluetoothLocalDevice::Error error)
{
    qDebug() << __FUNCTION__;
    qDebug() << error;

    switch (error)
    {
        case QBluetoothLocalDevice::NoError:
            m_statusString.clear();
            break;
        case QBluetoothLocalDevice::PairingError:
            m_statusString = tr("Error: Pairing error");
            break;
        case QBluetoothLocalDevice::UnknownError:
            m_statusString = tr("Error: Unknown");
            break;
    }

    emit statusStringUpdated();
}

void BLEManager::deviceDiscovered(const QBluetoothDeviceInfo &info)
{
    qDebug() << __FUNCTION__;

    // Skip non BLE devices
    if (!(info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration))
    {
        return;
    }

    bool updated = false;
    for (auto device : qAsConst(m_availableDevices))
    {
        if (qobject_cast<BleDeviceInfo *>(device)->update(info))
        {
            updated = true;
            break;
        }
    }
    if (!updated)
    {
        m_availableDevices.append(new BleDeviceInfo(info, m_availableDevices.size()));
        //qDebug() << m_device.pairingStatus(info.address());
    }

    emit availableDevicesUpdated();
}

void BLEManager::deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields)
{
    qDebug() << __FUNCTION__;
    qDebug() << info.name() << " (" << info.address() << ")";
    qDebug() << updatedFields;
}

void BLEManager::deviceDiscoveryFinished()
{
    qDebug() << __FUNCTION__;
    m_statusString = tr("Devices discovery finished");
    emit statusStringUpdated();
    emit isDeviceDiscoveryInProgressUpdated();
}

void BLEManager::deviceDiscoveryCanceled()
{
    qDebug() << __FUNCTION__;
    m_statusString = tr("Devices discovery canceled");
    emit statusStringUpdated();
    emit isDeviceDiscoveryInProgressUpdated();
}

void BLEManager::deviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error)
{
    qDebug() << __FUNCTION__;
    qDebug() << error;

    if (error != QBluetoothDeviceDiscoveryAgent::NoError)
    {
        qDeleteAll(m_availableDevices);
        m_availableDevices.clear();
        emit availableDevicesUpdated();
        emit isActiveUpdated();
    }

    if (m_discoveryAgent)
    {
        m_statusString = m_discoveryAgent->errorString();
    }
    else
    {
        switch (error)
        {
            case QBluetoothDeviceDiscoveryAgent::NoError:
                m_statusString.clear();
                break;
            case QBluetoothDeviceDiscoveryAgent::InputOutputError:
                m_statusString = tr("Error: I/O error");
                break;
            case QBluetoothDeviceDiscoveryAgent::PoweredOffError:
                m_statusString = tr("Error: Powered off");
                break;
            case QBluetoothDeviceDiscoveryAgent::InvalidBluetoothAdapterError:
                m_statusString = tr("Error: Invalid BT adapter");
                break;
            case QBluetoothDeviceDiscoveryAgent::UnsupportedPlatformError:
                m_statusString = tr("Error: Unsupported platform");
                break;
            case QBluetoothDeviceDiscoveryAgent::UnsupportedDiscoveryMethod:
                m_statusString = tr("Error: Unsupported discovery method");
                break;
#if QT_VERSION >= QT_VERSION_CHECK(6, 2, 0)
            case QBluetoothDeviceDiscoveryAgent::LocationServiceTurnedOffError:
                m_statusString = tr("Error: Location service turned off");
                break;
#endif
            case QBluetoothDeviceDiscoveryAgent::UnknownError:
                m_statusString = tr("Error: Unknown");
                break;
        }
    }
    emit statusStringUpdated();
    emit isDeviceDiscoveryInProgressUpdated();
}

void BLEManager::disconnectFromDevice()
{
    qDebug() << __FUNCTION__;
    if (m_controller)
    {
        m_controller->disconnectFromDevice();
        delete m_controller;
        m_controller = nullptr;
    }

    qDeleteAll(m_availableServices);
    m_availableServices.clear();
    emit availableServicesUpdated();
}

void BLEManager::connectToDevice(int index)
{
    qDebug() << __FUNCTION__;
    qDebug() << index;
    disconnectFromDevice();

    auto bleDeviceInfo = qobject_cast<BleDeviceInfo *>(m_availableDevices.at(index));
    if (!bleDeviceInfo)
    {
        m_statusString = tr("Error: Invalid device info");
        emit statusStringUpdated();
        return;
    }

    m_statusString = tr("Connecting to '%1' (%2)...").arg(bleDeviceInfo->name(), bleDeviceInfo->address());
    emit statusStringUpdated();

    auto deviceInfo = bleDeviceInfo->getDeviceInfo();
    qDebug() << deviceInfo.name();
    qDebug() << deviceInfo.deviceUuid();
    m_controller = QLowEnergyController::createCentral(deviceInfo, this);

    connect(m_controller, &QLowEnergyController::connected,
            this, &BLEManager::bleDeviceConnected);
    connect(m_controller, &QLowEnergyController::disconnected,
            this, &BLEManager::bleDeviceDisconnected);
    connect(m_controller, &QLowEnergyController::stateChanged,
            this, &BLEManager::bleDeviceStateChanged);
    connect(m_controller, &QLowEnergyController::connectionUpdated,
            this, &BLEManager::bleDeviceConnectionUpdated);
    connect(m_controller, &QLowEnergyController::serviceDiscovered,
            this, &BLEManager::serviceDiscovered);
    connect(m_controller, &QLowEnergyController::discoveryFinished,
            this, &BLEManager::serviceDiscoveryFinished);
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
    connect(m_controller, static_cast<void (QLowEnergyController::*)(QLowEnergyController::Error)>(&QLowEnergyController::error),
            this, &BLEManager::bleDeviceError);
#else
    connect(m_controller, &QLowEnergyController::errorOccurred,
            this, &BLEManager::bleDeviceError);
#endif

    m_controller->connectToDevice();
    emit isServicesDiscoveryInProgressUpdated();
}

void BLEManager::bleDeviceConnected()
{
    qDebug() << __FUNCTION__;

    if (m_controller)
    {

#ifdef Q_OS_DARWIN
        m_statusString = tr("Connected to '%1' (%2)").arg(m_controller->remoteName(), m_controller->remoteDeviceUuid().toString());
#else
        m_statusString = tr("Connected to '%1' (%2)").arg(m_controller->remoteName(), m_controller->remoteAddress().toString());
#endif
        emit statusStringUpdated();
        m_controller->discoverServices();
    }

    emit isDeviceConnectedUpdated();
}

void BLEManager::bleDeviceDisconnected()
{
    qDebug() << __FUNCTION__;

    if (m_controller)
    {
#ifdef Q_OS_DARWIN
        m_statusString = tr("Disconnected from '%1' (%2)").arg(m_controller->remoteName(), m_controller->remoteDeviceUuid().toString());
#else
        m_statusString = tr("Disconnected from '%1' (%2)").arg(m_controller->remoteName(), m_controller->remoteAddress().toString());
#endif
        emit statusStringUpdated();
    }

    emit isDeviceConnectedUpdated();
}

void BLEManager::bleDeviceStateChanged(QLowEnergyController::ControllerState state)
{
    qDebug() << __FUNCTION__;
    qDebug() << state;
    emit isDeviceConnectedUpdated();
}

void BLEManager::bleDeviceConnectionUpdated(const QLowEnergyConnectionParameters &parameters)
{
    qDebug() << __FUNCTION__;
    qDebug() << parameters.latency();
    qDebug() << parameters.maximumInterval();
    qDebug() << parameters.minimumInterval();
    qDebug() << parameters.supervisionTimeout();
}

void BLEManager::serviceDiscovered(const QBluetoothUuid &gatt)
{
    qDebug() << __FUNCTION__;
    qDebug() << gatt.toString();
    m_availableServices.append(new BleServiceInfo(gatt, m_availableServices.size()));
}

void BLEManager::serviceDiscoveryFinished()
{
    qDebug() << __FUNCTION__;
    emit isServicesDiscoveryInProgressUpdated();
    emit availableServicesUpdated();
}

void BLEManager::bleDeviceError(QLowEnergyController::Error error)
{
    qDebug() << __FUNCTION__;
    qDebug() << error;
    if (m_controller)
    {
        m_statusString = m_controller->errorString();
    }
    else
    {
        switch (error)
        {
            case QLowEnergyController::NoError:
                m_statusString.clear();
                break;
            case QLowEnergyController::UnknownError:
                m_statusString = tr("Error: Unknown error");
                break;
            case QLowEnergyController::UnknownRemoteDeviceError:
                m_statusString = tr("Error: Unknown remote device error");
                break;
            case QLowEnergyController::NetworkError:
                m_statusString = tr("Error: Network error");
                break;
            case QLowEnergyController::InvalidBluetoothAdapterError:
                m_statusString = tr("Error: Invalid BT adapter");
                break;
            case QLowEnergyController::ConnectionError:
                m_statusString = tr("Error: Connection error");
                break;
            case QLowEnergyController::AdvertisingError:
                m_statusString = tr("Error: Advertising error");
                break;
            case QLowEnergyController::RemoteHostClosedError:
                m_statusString = tr("Error: Remote host closed");
                break;
            case QLowEnergyController::AuthorizationError:
                m_statusString = tr("Error: Authorization error");
                break;
        }
    }
    emit statusStringUpdated();
}

void BLEManager::updateServiceState(QLowEnergyService::ServiceState newState)
{
    qDebug() << __FUNCTION__;
    qDebug() << newState;
    switch (newState)
    {
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
        case QLowEnergyService::DiscoveryRequired:
#else
        case QLowEnergyService::RemoteService:
#endif
        {
            m_service->discoverDetails();
            emit isCharacteristicsDiscoveryInProgressUpdated();
            break;
        }
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
        case QLowEnergyService::DiscoveringServices:
#else
        case QLowEnergyService::RemoteServiceDiscovering:
#endif
            break;
#if QT_VERSION < QT_VERSION_CHECK(6, 2, 0)
        case QLowEnergyService::ServiceDiscovered:
#else
        case QLowEnergyService::RemoteServiceDiscovered:
#endif
        {
//            qDebug() << "vvv Included Services vvv";
//            auto services = m_service->includedServices();
//            for (auto service : services) {
//                auto s = BleServiceInfo(service);
//            }
//            qDebug() << "^^^ Included Services ^^^";

            qDebug() << "vvv Characteristics vvv";
            auto characteristics = m_service->characteristics();
            for (const auto &characteristic : characteristics)
            {
                m_availableCharacteristics.append(new BleCharacteristicInfo(characteristic, m_availableCharacteristics.size()));
            }
            emit isCharacteristicsDiscoveryInProgressUpdated();
            emit availableCharacteristicsUpdated();
            qDebug() << "^^^ Characteristics ^^^";

            break;
        }
        case QLowEnergyService::InvalidService:
            qDebug() << "InvalidService";
        case QLowEnergyService::LocalService:
            break;
    }
}

void BLEManager::disconnectFromService()
{
    qDebug() << __FUNCTION__;

    if (m_service)
    {
        delete m_service;
        m_service = nullptr;
    }

    qDeleteAll(m_availableCharacteristics);
    m_availableCharacteristics.clear();
    emit availableCharacteristicsUpdated();
}

void BLEManager::connectToService(int index)
{
    qDebug() << __FUNCTION__;
    qDebug() << index;
    disconnectFromService();

    auto bleServiceInfo = qobject_cast<BleServiceInfo *>(m_availableServices.at(index));
    if (!bleServiceInfo)
    {
        m_statusString = tr("Error: Invalid service info");
        emit statusStringUpdated();
        return;
    }

    auto serviceUuid = bleServiceInfo->getServiceClassUuid();
    qDebug() << serviceUuid;
    m_service = m_controller->createServiceObject(serviceUuid, this);

    connect(m_service, &QLowEnergyService::stateChanged,
            this, &BLEManager::serviceStateChanged);
    connect(m_service, &QLowEnergyService::characteristicRead,
            this, &BLEManager::characteristicRead);
    connect(m_service, &QLowEnergyService::characteristicWritten,
            this, &BLEManager::characteristicWritten);
    //
    connect(m_service, &QLowEnergyService::characteristicChanged,
            this, &BLEManager::characteristicChanged);
    connect(m_service, &QLowEnergyService::descriptorWritten,
            this, &BLEManager::descriptorWritten);

    updateServiceState(m_service->state());
}

void BLEManager::serviceStateChanged(QLowEnergyService::ServiceState newState)
{
    qDebug() << __FUNCTION__;
    updateServiceState(newState);
}

void BLEManager::characteristicRead(const QLowEnergyCharacteristic &info,
                                    const QByteArray &value)
{
    qDebug() << __FUNCTION__;
    m_characteristicValue = value;
    emit characteristicValueUpdated();
}

void BLEManager::characteristicWritten(const QLowEnergyCharacteristic &info,
                                       const QByteArray &value)
{
    qDebug() << __FUNCTION__;
}

void BLEManager::disconnectFromCharacteristic()
{
    qDebug() << __FUNCTION__;
    if (m_characteristic)
    {
        m_characteristic.reset();
        m_characteristic = nullptr;
    }
    m_characteristicName.clear();
}

void BLEManager::connectToCharacteristic(int index)
{
    qDebug() << __FUNCTION__;
    qDebug() << index;
    disconnectFromCharacteristic();

    auto bleCharacteristicInfo = qobject_cast<BleCharacteristicInfo *>(m_availableCharacteristics.at(index));
    if (!bleCharacteristicInfo)
    {
        m_statusString = tr("Error: Invalid characteristic info");
        emit statusStringUpdated();
        return;
    }

    m_characteristic = std::make_unique<QLowEnergyCharacteristic>(bleCharacteristicInfo->getServiceCharacteristic());
    auto descriptors = m_characteristic->descriptors();
    for (const auto &descriptor : descriptors)
    {
        qDebug() << "descriptor:" << descriptor.name() << descriptor.type() << descriptor.value();
    }
    auto properties = m_characteristic->properties();
    qDebug() << "properties:" << properties;
    //
    QObject *object = m_availableCharacteristics.at(index);
    m_characteristicName = qobject_cast<BleCharacteristicInfo *>(object)->description();
    qDebug() << m_characteristicName;
    m_characteristicValue = m_characteristic->value();
    qDebug() << m_characteristicValue;
}

void BLEManager::readCharacteristicValue()
{
    qDebug() << __FUNCTION__;
    m_service->readCharacteristic(*m_characteristic);
}

void BLEManager::unsubscribeFromNotifications()
{
    qDebug() << __FUNCTION__;
    if (isSubscribed())
    {
        m_service->writeDescriptor(m_notificationDescriptor, disableNotification);
    }
}

void BLEManager::subscribeToNotifications()
{
    qDebug() << __FUNCTION__;

#if 0
    auto isValidCccd = [](QLowEnergyDescriptor descriptor)
    {
        return descriptor.isValid() &&
               descriptor.type() == QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration;
    };
    auto descriptors = m_characteristic->descriptors();
    auto descriptor = std::find_if(std::begin(descriptors), std::end(descriptors), isValidCccd);

    if (descriptor == std::end(descriptors))
    {
        return;
    }

    m_notificationDescriptor = *descriptor;
    m_service->writeDescriptor(m_notificationDescriptor, enableNotification);
#else
    for (const auto &descriptor : m_characteristic->descriptors())
    {
        if (descriptor.isValid() &&
            descriptor.type() == QBluetoothUuid::DescriptorType::ClientCharacteristicConfiguration)
        {
            m_notificationDescriptor = descriptor;
            m_service->writeDescriptor(m_notificationDescriptor, enableNotification);
            //emit isSubscribedUpdated();
            break;
        }
    }
#endif
}

void BLEManager::characteristicChanged(const QLowEnergyCharacteristic &info, const QByteArray &value)
{
    qDebug() << __FUNCTION__;
    qDebug() << value;
    m_characteristicValue = value;
    emit characteristicValueUpdated();
}

void BLEManager::descriptorWritten(const QLowEnergyDescriptor &info, const QByteArray &value)
{
    qDebug() << __FUNCTION__;
    if (info.isValid() &&
        info == m_notificationDescriptor &&
        value == enableNotification || value == disableNotification)
    {
        emit isSubscribedUpdated();
    }
}
