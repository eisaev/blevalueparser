#include "utils.hpp"

#include <iomanip>
#include <iostream>


void Utils::print_byte_array(const SimpleBLE::ByteArray& bytes) {
    for (auto b : bytes) {
        std::cout << std::hex << std::setfill('0') << std::setw(2) << (uint32_t)((uint8_t)b) << " ";
    }
    std::cout << std::endl;
}

std::optional<std::size_t> Utils::getUserInputInt(const std::string& line, std::size_t max) {
    std::size_t ret;

    while (!std::cin.eof()) {
        std::cout << line << " (0-" << max << "): ";
        std::cin >> ret;

        if (!std::cin) {
            return {};
        }

        if (ret <= max) {
            return ret;
        }
    }
    return {};
}

std::optional<SimpleBLE::Safe::Adapter> Utils::getAdapter() {
    if (!SimpleBLE::Safe::Adapter::bluetooth_enabled()) {
        std::cout << "Bluetooth is not enabled!" << std::endl;
        return {};
    }

    auto adapter_list_opt = SimpleBLE::Safe::Adapter::get_adapters();

    if (!adapter_list_opt.has_value()) {
        std::cout << "Failed to get adapters!" << std::endl;
        return {};
    }

    // no adapter found
    if (adapter_list_opt->empty()) {
        std::cerr << "No adapter was found." << std::endl;
        return {};
    }

    auto adapter_list = adapter_list_opt.value();

    // only one found, returning directly
    if (adapter_list.size() == 1) {
        auto adapter = adapter_list.at(0);
        std::cout << "Using adapter: "
                  << adapter.identifier().value_or("<NoName>")
                  << " (" << adapter.address().value_or("<NoAddress>") << ")"
                  << std::endl;
        return adapter;
    }

    // multiple adapters found, ask user to select one
    std::cout << "Available adapters:" << std::endl;
    int i = 0;
    for (auto& adapter : adapter_list) {
        std::cout << "[" << i++ << "] "
                  << adapter.identifier().value_or("<NoName>")
                  << " (" << adapter.address().value_or("<NoAddress>") << ")"
                  << std::endl;
    }

    auto adapter_selection = Utils::getUserInputInt("Select an adapter", adapter_list.size() - 1);

    if (!adapter_selection.has_value()) {
        return {};
    }

    return adapter_list[adapter_selection.value()];
}
