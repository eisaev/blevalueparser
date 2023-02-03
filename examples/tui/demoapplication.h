#pragma once

#include "blemanager.h"


class DemoApplication
{
public:
    DemoApplication();

    static void onValueUpdated(void *context, const std::string& data);

private:
    bvp::BLEValueParser m_bleValueParser;
    BLEManager m_bleManager;

    bool adapterView();
    bool deviceView();
    bool serviceView();
    bool characteristicView();
    bool valueView();

    std::optional<size_t> getUserSelectionInt(const std::string &msg, size_t max) const;
    bool getUserSelectionBool(const std::string &msg) const;
};
