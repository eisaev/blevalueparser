#include "blemanager.h"

#include <iostream>

#include "blevalueparser/blenames.h"


BLEManager::BLEManager(void *callbackContext, ValueUpdatedCallback onValueUpdated) :
    m_callbackContext{callbackContext},
    m_onValueUpdated{onValueUpdated}
{}

std::string BLEManager::lastStatus() const
{
    return m_status;
}

bool BLEManager::detectAdapters()
{
    m_availableAdapters.clear();

    if (!SimpleBLE::Safe::Adapter::bluetooth_enabled()) {
        m_status = "Warning: Bluetooth is not enabled.";
        return false;
    }

    const auto adapter_list_opt = SimpleBLE::Safe::Adapter::get_adapters();
    if (!adapter_list_opt.has_value()) {
        m_status = "Error: Failed to get adapters.";
        return false;
    }

    if (adapter_list_opt->empty()) {
        m_status = "Warning: No adapter was found.";
        return false;
    }

    m_availableAdapters = adapter_list_opt.value();
    return true;
}

std::vector<SimpleBLE::Safe::Adapter> BLEManager::availableAdapters() const
{
    return m_availableAdapters;
}

bool BLEManager::selectAdapter(size_t index)
{
    if (index > m_availableAdapters.size() - 1)
    {
        m_status = "Error: Index out of range.";
        return false;
    }

    m_adapter = std::make_unique<SimpleBLE::Safe::Adapter>(m_availableAdapters[index]);
    if (!m_adapter.get())
    {
        m_status = "Error: Failed to use selected adapter.";
        return false;
    }

    return true;
}

std::string BLEManager::adapterName(SimpleBLE::Safe::Adapter &adapter)
{
    std::string result = adapter.identifier().value_or("<NoName>");
    if (result.empty())
    {
        result = "<NoName>";
    }

    return result;
}

std::string BLEManager::adapterName() const
{
    if (!m_adapter)
    {
        return "<NotSelected>";
    }

    return adapterName(*m_adapter);
}

std::string BLEManager::adapterAddress(SimpleBLE::Safe::Adapter &adapter)
{
    std::string result = adapter.address().value_or("<NoAddress>");
    if (result.empty())
    {
        result = "<NoAddress>";
    }

    return result;
}

std::string BLEManager::adapterAddress() const
{
    if (!m_adapter)
    {
        return "<NotSelected>";
    }

    return adapterAddress(*m_adapter);
}

bool BLEManager::discoveryDevices(int timeout_ms)
{
    m_availableDevices.clear();

    if (!m_adapter)
    {
        m_status = "Warning: Adapter not selected.";
        return false;
    }

    m_adapter->set_callback_on_scan_start([]() { std::cout << "Scanning." << std::flush;;  });

    m_adapter->set_callback_on_scan_found(
        [&](SimpleBLE::Safe::Peripheral peripheral)
        {
            std::cout << "." << std::flush;;
            m_availableDevices.push_back(peripheral);
        }
    );

    m_adapter->set_callback_on_scan_stop([]() { std::cout << " Done" << std::endl; });

    m_adapter->scan_for(timeout_ms);

    return true;
}

std::vector<SimpleBLE::Safe::Peripheral> BLEManager::availableDevices() const
{
    return m_availableDevices;
}

bool BLEManager::selectDevice(size_t index)
{
    if (index > m_availableDevices.size() - 1)
    {
        std::cerr << "Index out of range." << std::endl;
        return false;
    }

    m_device = std::make_unique<SimpleBLE::Safe::Peripheral>(m_availableDevices[index]);
    if (!m_device.get())
    {
        return false;
    }

    return true;
}

std::string BLEManager::deviceName(SimpleBLE::Safe::Peripheral &device)
{
    std::string result = device.identifier().value_or("<NoName>");
    if (result.empty())
    {
        result = "<NoName>";
    }

    return result;
}

std::string BLEManager::deviceName() const
{
    if (!m_device)
    {
        return "<NotSelected>";
    }

    return deviceName(*m_device);
}

std::string BLEManager::deviceAddress(SimpleBLE::Safe::Peripheral &device)
{
    std::string result = device.address().value_or("<NoAddress>");
    if (result.empty())
    {
        result = "<NoAddress>";
    }

    return result;
}

std::string BLEManager::deviceAddress() const
{
    if (!m_device)
    {
        return "<NotSelected>";
    }

    return deviceAddress(*m_device);
}

bool BLEManager::connectToDevice()
{
    m_availableServices.clear();

    if (!m_device)
    {
        m_status = "Warning: Device not selected.";
        return false;
    }

    if (!m_device->connect())
    {
        m_status = "Error: Connection failed.";
        return false;
    }

    const auto services_opt = m_device->services();
    if (!services_opt.has_value()) {
        m_status = "Info: No services found.";
        return false;
    }

    m_availableServices = services_opt.value();
    return true;
}

bool BLEManager::disconnectFromDevice()
{
    m_availableServices.clear();
    m_availableCharacteristics.clear();

    if (!m_device)
    {
        m_status = "Warning: Device not selected.";
        return false;
    }

    if (!m_device->disconnect())
    {
        m_status = "Error: Disconnection failed.";
        return false;
    }

    return true;
}

std::vector<SimpleBLE::Service> BLEManager::availableServices() const
{
    return m_availableServices;
}

bool BLEManager::selectService(size_t index)
{
    if (index > m_availableServices.size() - 1)
    {
        std::cerr << "Index out of range." << std::endl;
        return false;
    }

    m_service = std::make_unique<SimpleBLE::Service>(m_availableServices[index]);
    if (!m_service.get())
    {
        return false;
    }

    return true;
}

std::string BLEManager::serviceName(SimpleBLE::Service &service)
{
    return bvp::getBleName(service.uuid());
}

std::string BLEManager::serviceName() const
{
    if (!m_service)
    {
        return "<NotSelected>";
    }

    return serviceName(*m_service);
}

std::string BLEManager::serviceUUID(SimpleBLE::Service &service)
{
    return service.uuid();
}

std::string BLEManager::serviceUUID() const
{
    if (!m_service)
    {
        return "<NotSelected>";
    }

    return serviceUUID(*m_service);
}

bool BLEManager::connectToService()
{
    m_availableCharacteristics.clear();

    if (!m_service)
    {
        m_status = "Warning: Service not selected.";
        return false;
    }

    m_availableCharacteristics = m_service->characteristics();
    if (m_availableCharacteristics.empty()) {
        m_status = "Info: No characteristics found.";
        return false;
    }

    return true;
}

std::vector<SimpleBLE::Characteristic> BLEManager::availableCharacteristics() const
{
    return m_availableCharacteristics;
}

bool BLEManager::selectCharacteristic(size_t index)
{
    if (index > m_availableCharacteristics.size() - 1)
    {
        std::cerr << "Index out of range." << std::endl;
        return false;
    }

    m_characteristic = std::make_unique<SimpleBLE::Characteristic>(m_availableCharacteristics[index]);
    if (!m_characteristic.get())
    {
        return false;
    }

    return true;
}

std::string BLEManager::characteristicName(SimpleBLE::Characteristic &characteristic)
{
    return bvp::getBleName(characteristic.uuid());
}

std::string BLEManager::characteristicName() const
{
    if (!m_characteristic)
    {
        return "<NotSelected>";
    }

    return characteristicName(*m_characteristic);
}

std::string BLEManager::characteristicUUID(SimpleBLE::Characteristic &characteristic)
{
    return characteristic.uuid();
}

std::string BLEManager::characteristicUUID() const
{
    if (!m_characteristic)
    {
        return "<NotSelected>";
    }

    return characteristicUUID(*m_characteristic);
}

bool BLEManager::connectToCharacteristic()
{
    if (!m_characteristic)
    {
        m_status = "Warning: Characteristic not selected.";
        return false;
    }

    if (m_characteristic->can_read())
    {
        std::cout << "Trying to read data... ";
        auto bytes_opt = m_device->read(m_service->uuid(), m_characteristic->uuid());
        if (!bytes_opt.has_value())
        {
            std::cout << "Failed" << std::endl;
            m_status = "Error: Reading failed.";
            return false;
        }
        std::cout << "Done" << std::endl;

        if (m_onValueUpdated)
        {
            m_onValueUpdated(m_callbackContext, bytes_opt.value());
        }
    }

    if (m_characteristic->can_notify() || m_characteristic->can_indicate())
    {
        std::cout << "Trying to subscribe for notifications... ";
        if (!m_device->notify(m_service->uuid(),
                              m_characteristic->uuid(),
                              [&](SimpleBLE::ByteArray bytes) { if (m_onValueUpdated) m_onValueUpdated(m_callbackContext, bytes); }))
        {
            std::cout << "Failed" << std::endl;
            m_status = "Error: Subscription failed.";
            return false;
        }
        std::cout << "Done" << std::endl;
    }

    return true;
}
