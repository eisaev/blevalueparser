#include "demoapplication.h"

#include <iostream>
#include <chrono>
#include <thread>

#include "blevalueparser/blenames.h"

using namespace std::chrono_literals;


DemoApplication::DemoApplication() : m_bleManager{this, onValueUpdated}
{
    bool result;

    result = false;
    do
    {
        if (adapterView())
        {
            result = true;
            break;
        }

        std::cout << m_bleManager.lastStatus() << std::endl;
    } while (getUserSelectionBool("Retry (y/n)?"));

    if (!result)
    {
        exit(0);
    }

    std::cout << m_bleManager.adapterName()
              << " (" << m_bleManager.adapterAddress() << ")"
              << " selected" << std::endl;

    result = false;
    do
    {
        if (deviceView())
        {
            result = true;
            break;
        }

        std::cout << m_bleManager.lastStatus() << std::endl;
    } while (getUserSelectionBool("Retry (y/n)?"));

    if (!result)
    {
        exit(0);
    }

    std::cout << m_bleManager.deviceName()
              << " (" << m_bleManager.deviceAddress() << ")"
              << " selected" << std::endl;

    result = false;
    do
    {
        if (serviceView())
        {
            result = true;
            break;
        }

        std::cout << m_bleManager.lastStatus() << std::endl;
    } while (getUserSelectionBool("Retry (y/n)?"));

    if (!result)
    {
        exit(0);
    }

    std::cout << m_bleManager.serviceName()
              << " (" << m_bleManager.serviceUUID() << ")"
              << " selected" << std::endl;

    result = false;
    do
    {
        if (characteristicView())
        {
            result = true;
            break;
        }

        std::cout << m_bleManager.lastStatus() << std::endl;
    } while (getUserSelectionBool("Retry (y/n)?"));

    if (!result)
    {
        exit(0);
    }

    std::cout << m_bleManager.characteristicName()
              << " (" << m_bleManager.characteristicUUID() << ")"
              << " selected" << std::endl;

    do
    {
        if (valueView())
        {
            char ch;
            while (std::cin >> ch) {
                std::this_thread::sleep_for(1s);
            }
            break;
        }
        else
        {
            std::cout << m_bleManager.lastStatus() << std::endl;
        }
    } while (getUserSelectionBool("Retry (y/n)?"));

    m_bleManager.disconnectFromDevice();
}

void DemoApplication::onValueUpdated(void *context, const std::string &data)
{
    std::cout << "Raw data:" << std::endl;
    for (auto ch : data)
    {
        std::cout << std::uppercase << std::setfill('0') << std::setw(2) << std::hex
                  << static_cast<unsigned int>(static_cast<unsigned char>(ch)) << " ";
    }
    std::cout << std::endl;

    if (!context)
    {
        return;
    }

    const auto demoApp = reinterpret_cast<DemoApplication*>(context);
    std::cout << "Parsed data:" << std::endl;
    const auto characteristicType = bvp::uuidToCharacteristicType(demoApp->m_bleManager.characteristicUUID());
    const auto parsed = demoApp->m_bleValueParser.make_value(characteristicType, data.c_str(), data.size());
    std::cout << parsed->toString() << std::endl;
}

bool DemoApplication::adapterView()
{
    if (!m_bleManager.detectAdapters())
    {
        return false;
    }

    auto adapters = m_bleManager.availableAdapters();
    if (adapters.empty())
    {
        return false;
    }

    std::cout << std::endl << "\tAvailable adapters:" << std::endl;
    for (size_t i = 0; i < adapters.size(); ++i)
    {

        std::cout << "[" << i << "] "
                  << BLEManager::adapterName(adapters[i])
                  << " (" << BLEManager::adapterAddress(adapters[i]) << ") "
                  << std::endl;
    }

    if (1 == adapters.size())
    {
        return m_bleManager.selectAdapter(0);
    }

    const std::optional<size_t> selection = getUserSelectionInt("Select adapter", adapters.size() - 1);
    if (selection.has_value())
    {
        if (m_bleManager.selectAdapter(selection.value()))
        {
            return true;
        }
    }

    return false;
}

bool DemoApplication::deviceView()
{
    if (!m_bleManager.discoveryDevices(5000))
    {
        return false;
    }

    auto devices = m_bleManager.availableDevices();
    if (devices.empty())
    {
        return false;
    }

    std::cout << std::endl << "\tAvailable devices:" << std::endl;
    for (size_t i = 0; i < devices.size(); ++i)
    {
        std::cout << "[" << i << "] "
                  << BLEManager::deviceName(devices[i])
                  << " (" << BLEManager::deviceAddress(devices[i]) << ") "
                  << std::endl;
    }

    const std::optional<size_t> selection = getUserSelectionInt("Select device", devices.size() - 1);
    if (selection.has_value())
    {
        if (m_bleManager.selectDevice(selection.value()))
        {
            return true;
        }
    }

    return false;
}

bool DemoApplication::serviceView()
{
    if (!m_bleManager.connectToDevice())
    {
        return false;
    }

    auto services = m_bleManager.availableServices();
    if (services.empty())
    {
        return false;
    }

    std::cout << std::endl << "\tAvailable services:" << std::endl;
    for (size_t i = 0; i < services.size(); ++i)
    {
        std::cout << "[" << i << "] "
                  << BLEManager::serviceName(services[i])
                  << " (" << BLEManager::serviceUUID(services[i]) << ") "
                  << std::endl;
    }

    const std::optional<size_t> selection = getUserSelectionInt("Select service", services.size() - 1);
    if (selection.has_value())
    {
        if (m_bleManager.selectService(selection.value()))
        {
            return true;
        }
    }

    return false;
}

bool DemoApplication::characteristicView()
{
    if (!m_bleManager.connectToService())
    {
        return false;
    }

    auto characteristics = m_bleManager.availableCharacteristics();
    if (characteristics.empty())
    {
        return false;
    }

    std::cout << std::endl << "\tAvailable characteristics:" << std::endl;
    for (size_t i = 0; i < characteristics.size(); ++i)
    {
        std::cout << "[" << i << "] "
                  << BLEManager::characteristicName(characteristics[i])
                  << " (" << BLEManager::characteristicUUID(characteristics[i]) << ") "
                  << std::endl;
    }

    const std::optional<size_t> selection = getUserSelectionInt("Select service", characteristics.size() - 1);
    if (selection.has_value())
    {
        if (m_bleManager.selectCharacteristic(selection.value()))
        {
            return true;
        }
    }

    return false;
}

bool DemoApplication::valueView()
{
    std::cout << std::endl << "\tPress Ctrl+D to stop." << std::endl;

    if (!m_bleManager.connectToCharacteristic())
    {
        return false;
    }

    return true;
}

std::optional<size_t> DemoApplication::getUserSelectionInt(const std::string &msg, size_t max) const
{
    std::string str;

    std::cout << msg << " (0-" << max << "): ";
    std::getline(std::cin, str);

    try
    {
        const size_t result = std::stoull(str);

        if (result <= max)
        {
            return result;
        }
    }
    catch (...)
    {
        //
    }

    std::cout << "Invalid input" << std::endl;

    return {};
}

bool DemoApplication::getUserSelectionBool(const std::string &msg) const
{
    std::locale locale;
    std::string str;

    std::cout << msg << ": ";
    std::getline(std::cin, str);

    for(auto& ch : str)
    {
        ch = std::tolower(ch, locale);
    }

    if ("y" == str || "yes" == str)
    {
        return true;
    }

    return false;
}
