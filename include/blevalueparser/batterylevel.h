#pragma once

#include "basevalue.h"


namespace bvp
{

/*
 * Battery Service
 * BAS_V1.1.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.27 Battery Level
struct BatteryLevelStruct
{
    uint8_t batteryLevel = 0;
};

// 3.1 Battery Level
class BatteryLevel final : public BaseValue
{
public:
    BatteryLevelStruct getBtSpecObject() const
    {
        return m_batteryLevel;
    }

    uint8_t level() const
    {
        return m_batteryLevel.batteryLevel;
    }

private:
    friend class BLEValueParser;
    explicit BatteryLevel(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit BatteryLevel(const BatteryLevelStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_batteryLevel{btSpecObject}
    {
        m_isValid = true;
    }

    BatteryLevelStruct m_batteryLevel;

    static size_t expectedSize()
    {
        return 1;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == expectedSize();
    }

    virtual bool parse(Parser &parser) override
    {
        m_batteryLevel.batteryLevel = parser.parseUInt8();
        if (m_batteryLevel.batteryLevel > 100)
        {
            return false;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << static_cast<int>(m_batteryLevel.batteryLevel) << "%";
    }
};

}  // namespace bvp
