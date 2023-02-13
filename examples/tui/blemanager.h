#pragma once

#include <simpleble/SimpleBLE.h>
#include <blevalueparser/bvp.h>


class BLEManager
{
public:
    typedef void (*ValueUpdatedCallback)(void *context, const std::string &data);

    explicit BLEManager(void *callbackContext, ValueUpdatedCallback onValueUpdated);

    std::string lastStatus() const;

    bool detectAdapters();

    std::vector<SimpleBLE::Safe::Adapter> availableAdapters() const;
    bool selectAdapter(size_t index);
    static std::string adapterName(SimpleBLE::Safe::Adapter &adapter);
    std::string adapterName() const;
    static std::string adapterAddress(SimpleBLE::Safe::Adapter &adapter);
    std::string adapterAddress() const;

    bool discoveryDevices(int timeout_ms);

    std::vector<SimpleBLE::Safe::Peripheral> availableDevices() const;
    bool selectDevice(size_t index);
    static std::string deviceName(SimpleBLE::Safe::Peripheral &device);
    std::string deviceName() const;
    static std::string deviceAddress(SimpleBLE::Safe::Peripheral &device);
    std::string deviceAddress() const;

    bool connectToDevice();
    bool disconnectFromDevice();

    std::vector<SimpleBLE::Service> availableServices() const;
    bool selectService(size_t index);
    static std::string serviceName(SimpleBLE::Service &service);
    std::string serviceName() const;
    static std::string serviceUUID(SimpleBLE::Service &service);
    std::string serviceUUID() const;

    bool connectToService();

    std::vector<SimpleBLE::Characteristic> availableCharacteristics() const;
    bool selectCharacteristic(size_t index);
    static std::string characteristicName(SimpleBLE::Characteristic &characteristic);
    std::string characteristicName() const;
    static std::string characteristicUUID(SimpleBLE::Characteristic &characteristic);
    std::string characteristicUUID() const;

    bool connectToCharacteristic();

    std::string m_value;

private:
    void *m_callbackContext;
    ValueUpdatedCallback m_onValueUpdated;

    std::string m_status;

    std::vector<SimpleBLE::Safe::Adapter> m_availableAdapters;
    std::unique_ptr<SimpleBLE::Safe::Adapter> m_adapter{nullptr};

    std::vector<SimpleBLE::Safe::Peripheral> m_availableDevices;
    std::unique_ptr<SimpleBLE::Safe::Peripheral> m_device{nullptr};
    std::unique_ptr<bvp::PnPID> m_devicePnPID{nullptr};

    std::vector<SimpleBLE::Service> m_availableServices;
    std::unique_ptr<SimpleBLE::Service> m_service{nullptr};

    std::vector<SimpleBLE::Characteristic> m_availableCharacteristics;
    std::unique_ptr<SimpleBLE::Characteristic> m_characteristic{nullptr};
};
