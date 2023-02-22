#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.27 Battery Level
struct BatteryLevelStruct
{
    uint8_t batteryLevel = 0;
};

// BAS_V1.1.pdf
// Battery Service v1.1
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

    explicit BatteryLevel(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

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

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
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
