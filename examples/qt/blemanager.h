#pragma once

#include <QQmlEngine>
#include <QObject>
#include <QVariant>
#include <QMap>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QLowEnergyService>

#include "blevalueparser.h"


class BLEManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QVariant statusString READ statusString NOTIFY statusStringUpdated)

    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveUpdated)

    Q_PROPERTY(QVariant availableDevices READ availableDevices NOTIFY availableDevicesUpdated)
    Q_PROPERTY(bool isDeviceDiscoveryInProgress READ isDeviceDiscoveryInProgress NOTIFY isDeviceDiscoveryInProgressUpdated)
    Q_PROPERTY(bool isDeviceConnected READ isDeviceConnected NOTIFY isDeviceConnectedUpdated)

    Q_PROPERTY(QVariant availableServices READ availableServices NOTIFY availableServicesUpdated)
    Q_PROPERTY(bool isServicesDiscoveryInProgress READ isServicesDiscoveryInProgress NOTIFY isServicesDiscoveryInProgressUpdated)

    Q_PROPERTY(QVariant availableCharacteristics READ availableCharacteristics NOTIFY availableCharacteristicsUpdated)
    Q_PROPERTY(bool isCharacteristicsDiscoveryInProgress READ isCharacteristicsDiscoveryInProgress NOTIFY isCharacteristicsDiscoveryInProgressUpdated)
    Q_PROPERTY(bool isSubscribed READ isSubscribed NOTIFY isSubscribedUpdated)

    Q_PROPERTY(QVariant characteristicName READ characteristicName NOTIFY characteristicNameUpdated)
    Q_PROPERTY(QVariant characteristicValue READ characteristicValue NOTIFY characteristicValueUpdated)
    Q_PROPERTY(QVariant characteristicValueParsed READ characteristicValueParsed NOTIFY characteristicValueUpdated)
    Q_PROPERTY(QVariant characteristicIsRead READ characteristicIsRead CONSTANT)
    Q_PROPERTY(QVariant characteristicIsNotify READ characteristicIsNotify CONSTANT)

public:
    explicit BLEManager(QObject *parent = nullptr);
    ~BLEManager();

    QVariant statusString() const;

    bool isActive() const;

    QVariant availableDevices() const;
    bool isDeviceDiscoveryInProgress() const;
    bool isDeviceConnected() const;

    QVariant availableServices() const;
    bool isServicesDiscoveryInProgress() const;

    QVariant availableCharacteristics() const;
    bool isCharacteristicsDiscoveryInProgress() const;
    bool isSubscribed() const;

    QVariant characteristicName() const;
    QVariant characteristicValue() const;
    QVariant characteristicValueParsed() const;
    QVariant characteristicIsRead() const;
    QVariant characteristicIsNotify() const;

public slots:
    void startDevicesDiscovery();
    void stopDevicesDiscovery();

    void disconnectFromDevice();
    void connectToDevice(int index);

    void disconnectFromService();
    void connectToService(int index);

    void disconnectFromCharacteristic();
    void connectToCharacteristic(int index);

    void readCharacteristicValue();
    void unsubscribeFromNotifications();
    void subscribeToNotifications();

signals:
    void statusStringUpdated();

    void isActiveUpdated();

    void availableDevicesUpdated();
    void isDeviceDiscoveryInProgressUpdated();
    void isDeviceConnectedUpdated();

    void availableServicesUpdated();
    void isServicesDiscoveryInProgressUpdated();

    void availableCharacteristicsUpdated();
    void isCharacteristicsDiscoveryInProgressUpdated();
    void isSubscribedUpdated();

    void characteristicNameUpdated();
    void characteristicValueUpdated();

private slots:
    // Local Device
    void hostModeStateChanged(QBluetoothLocalDevice::HostMode state);
    void remoteDeviceConnected(const QBluetoothAddress &address);
    void remoteDeviceDisconnected(const QBluetoothAddress &address);
    void pairingFinished(const QBluetoothAddress &address, QBluetoothLocalDevice::Pairing pairing);
    void pairingDisplayPinCode(const QBluetoothAddress &address, const QString& pin);
    void pairingDisplayConfirmation(const QBluetoothAddress &address, const QString& pin);
    void localDeviceError(QBluetoothLocalDevice::Error error);

    // Agent
    void deviceDiscovered(const QBluetoothDeviceInfo &info);
    void deviceUpdated(const QBluetoothDeviceInfo &info, QBluetoothDeviceInfo::Fields updatedFields);
    void deviceDiscoveryFinished();
    void deviceDiscoveryCanceled();
    void deviceDiscoveryError(QBluetoothDeviceDiscoveryAgent::Error error);

    // Controller
    void bleDeviceConnected();
    void bleDeviceDisconnected();
    void bleDeviceStateChanged(QLowEnergyController::ControllerState state);
    void bleDeviceConnectionUpdated(const QLowEnergyConnectionParameters &parameters);
    void serviceDiscovered(const QBluetoothUuid &gatt);
    void serviceDiscoveryFinished();
    void bleDeviceError(QLowEnergyController::Error error);

    // Service
    void serviceStateChanged(QLowEnergyService::ServiceState newState);
    void characteristicRead(const QLowEnergyCharacteristic &info, const QByteArray &value);
    void characteristicWritten(const QLowEnergyCharacteristic &info, const QByteArray &value);
    void characteristicChanged(const QLowEnergyCharacteristic &info, const QByteArray &value);
    void descriptorWritten(const QLowEnergyDescriptor &info, const QByteArray &value);

private:
    bvp::BLEValueParser m_bleValueParser;

    mutable QString m_statusString;

    QBluetoothLocalDevice m_localDevice;

    QBluetoothDeviceDiscoveryAgent *m_discoveryAgent{nullptr};
    QObjectList m_availableDevices;

    QLowEnergyController *m_controller{nullptr};
    QObjectList m_availableServices;

    QLowEnergyService *m_service{nullptr};
    QObjectList m_availableCharacteristics;

    std::unique_ptr<QLowEnergyCharacteristic> m_characteristic{nullptr};
    QString m_characteristicName;
    QByteArray m_characteristicValue;
    QLowEnergyDescriptor m_notificationDescriptor;

    void updateServiceState(QLowEnergyService::ServiceState newState);
};
