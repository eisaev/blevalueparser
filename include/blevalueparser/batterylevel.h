#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.27 Battery Level
struct BatteryLevelStruct
{
    uint8_t batteryLevel{0};
};

// BAS_V1.1.pdf
// Battery Service v1.1
// 3.1 Battery Level
class BatteryLevel final : public BaseValueSpec<BatteryLevelStruct>
{
public:
    friend class BatteryLevelStatus;

    uint8_t level() const
    {
        return m_btSpecObject.batteryLevel;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryLevel, BatteryLevelStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.batteryLevel = parser.parseUInt8();
        if (m_btSpecObject.batteryLevel > 100)
        {
            return false;
        }

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << static_cast<int>(m_btSpecObject.batteryLevel) << "%";
    }
};

}  // namespace bvp
