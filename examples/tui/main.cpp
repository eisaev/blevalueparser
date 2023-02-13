#include <iostream>
#include <iomanip>
#include <vector>
#include <chrono>
#include <thread>

#include <simpleble/SimpleBLE.h>
#include <blevalueparser/bvp.h>

#include "utils.hpp"
#include "demoapplication.h"

using namespace std::chrono_literals;


bool testSimpleBLE()
{
    auto adapter_optional = Utils::getAdapter();

    if (!adapter_optional.has_value()) {
        return false;
    }

    auto adapter = adapter_optional.value();

    std::vector<SimpleBLE::Safe::Peripheral> peripherals;

    adapter.set_callback_on_scan_found([&](SimpleBLE::Safe::Peripheral peripheral) {
        std::cout << "Found device: "
                  << peripheral.identifier().value_or("<NoName>")
                  << " (" << peripheral.address().value_or("<NoAddress>") << ") "
                  << peripheral.rssi().value_or(INT16_MIN) << "dBm"
                  << std::endl;
        peripherals.push_back(peripheral);
    });

    adapter.set_callback_on_scan_start([]() { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([]() { std::cout << "Scan stopped." << std::endl; });
    // Scan for 5 seconds and return.
    adapter.scan_for(5000);

    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++) {
        std::cout << "[" << i << "] "
                  << peripherals[i].identifier().value_or("<NoName>")
                  << " (" << peripherals[i].address().value_or("<NoAddress>") << ") "
                  << peripherals[i].rssi().value_or(INT16_MIN) << "dBm"
                  << std::endl;
    }

    auto selection = Utils::getUserInputInt("Please select a device to connect to", peripherals.size() - 1);
    if (!selection.has_value()) {
        return false;
    }

    auto peripheral = peripherals[selection.value()];
    std::cout << "Connecting to "
              << peripheral.identifier().value_or("<NoName>")
              << " (" << peripheral.address().value_or("<NoAddress>") << ") "
              << std::endl;
    if (peripheral.manufacturer_data().has_value()) {
        const std::map<uint16_t, SimpleBLE::ByteArray> manufacturer_data = peripheral.manufacturer_data().value();
        for (auto const &data : manufacturer_data) {
            std::cout << data.first << ": " << data.second << std::endl;
        }
    }

    peripheral.connect();

    std::cout << "Successfully connected, printing services and characteristics.." << std::endl;

    // Store all service and characteristic uuids in a vector.
    auto services_opt = peripheral.services();
    if (!services_opt.has_value()) {
        std::cout << "No services found." << std::endl;
        return false;
    }
    auto services = services_opt.value();

    std::cout << "The following services were found:" << std::endl;
    for (size_t i = 0; i < services.size(); i++) {
        std::cout << "[" << i << "] " << services[i].uuid() << std::endl;
    }

    selection = Utils::getUserInputInt("Please select a service", services.size() - 1);

    if (!selection.has_value()) {
        return false;
    }

    auto service = services[selection.value()];
    auto characteristics = service.characteristics();
    std::cout << "The following characteristics were found:" << std::endl;
    for (size_t i = 0; i < characteristics.size(); i++) {
        std::cout << "[" << i << "] " << characteristics[i].uuid() << " { ";
        for (const auto &capability : characteristics[i].capabilities()) {
            std::cout << capability << ", ";
        }
        std::cout << "}" << std::endl;
    }

    selection = Utils::getUserInputInt("Please select a characteristic", characteristics.size() - 1);

    if (!selection.has_value()) {
        return false;
    }

    auto characteristic = characteristics[selection.value()];

    bvp::BLEValueParser bleValueParser;

    if (characteristic.can_read()) {
        std::cout << "Trying to read data..." << std::endl;
        auto bytes_opt = peripheral.read(service.uuid(), characteristic.uuid());
        if (bytes_opt.has_value()) {
            auto bytes = bytes_opt.value();
            std::cout << "Raw data: ";
            Utils::print_byte_array(bytes);
            auto characteristicType = bvp::CharacteristicType(std::stoi(characteristic.uuid(), nullptr, 16));
            auto result = bleValueParser.make_value(characteristicType, bytes.c_str(), bytes.size());
            std::cout << "Parsed data: " << result->toString() << std::endl;
        }
    }

    if (characteristic.can_notify() || characteristic.can_indicate()) {
        std::cout << "Trying to subscribe for notifications..." << std::endl;
        peripheral.notify(service.uuid(), characteristic.uuid(), [&](SimpleBLE::ByteArray bytes) {
            std::cout << "Raw data: ";
            Utils::print_byte_array(bytes);
            auto characteristicType = bvp::CharacteristicType(std::stoi(characteristic.uuid(), nullptr, 16));
            auto result = bleValueParser.make_value(characteristicType, bytes.c_str(), bytes.size());
            std::cout << "Parsed data: " << result->toString() << std::endl;
        });

        std::this_thread::sleep_for(60s);

        peripheral.unsubscribe(service.uuid(), characteristic.uuid());
    }

    peripheral.disconnect();

    return true;
}

int main(int argc, char *argv[])
{
//    testSimpleBLE();
    DemoApplication app{};

    return 0;
}
