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

    BVP_GETTER(uint8_t, level, BatteryLevelStruct)
    {
        return btSpecObject.batteryLevel;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryLevel, BatteryLevelStruct)

    BVP_PARSE(BatteryLevelStruct)
    {
        bool result{true};

        btSpecObject.batteryLevel = parser.parseUInt8();
        if (btSpecObject.batteryLevel > 100)
        {
            return false;
        }

        return result;
    }

    BVP_TO_STRING(BatteryLevelStruct)
    {
        return fmt::format("{}%", btSpecObject.batteryLevel);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
