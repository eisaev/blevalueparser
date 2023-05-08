#pragma once

#include "basevalue.h"


namespace bvp
{

constexpr int8_t BHS_GREATER = 127;  // 0x7F
constexpr int8_t BHS_LESS = -128;  // 0x80
constexpr int8_t BHS_MAX = BHS_GREATER - 1;
constexpr int8_t BHS_MIN = BHS_LESS + 1;

// GATT_Specification_Supplement_v8.pdf
// 3.25.1 Flags field
constexpr uint8_t BHS_FLAG_BATTERY_HEALTH_SUMMARY_PRESENT   = 1 << 0;
constexpr uint8_t BHS_FLAG_CYCLE_COUNT_PRESENT              = 1 << 1;
constexpr uint8_t BHS_FLAG_CURRENT_TEMPERATURE_PRESENT      = 1 << 2;
constexpr uint8_t BHS_FLAG_DEEP_DISCHARGE_COUNT_PRESENT     = 1 << 3;
constexpr uint8_t BHS_FLAG_RESERVED1                        = 1 << 4;
constexpr uint8_t BHS_FLAG_RESERVED2                        = 1 << 5;
constexpr uint8_t BHS_FLAG_RESERVED3                        = 1 << 6;
constexpr uint8_t BHS_FLAG_RESERVED4                        = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.25 Battery Health Status
BVP_STRUCT(BatteryHealthStatus)
{
    uint8_t flags{0};
    uint8_t batteryHealthSummary{0};  // org.bluetooth.unit.percentage
    uint16_t cycleCount{0};
    int8_t currentTemperature{0};  // org.bluetooth.unit.thermodynamic_temperature.degree_celsius
    uint16_t deepDischargeCount{0};
};

class BatteryHealthStatus final : public BaseValueSpec<BatteryHealthStatus>
{
public:
    BVP_GETTER(bool, isBatteryHealthSummaryPresent, BatteryHealthStatus)
    {
        return (btSpecObject.flags & BHS_FLAG_BATTERY_HEALTH_SUMMARY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isCycleCountPresent, BatteryHealthStatus)
    {
        return (btSpecObject.flags & BHS_FLAG_CYCLE_COUNT_PRESENT) != 0;
    }

    BVP_GETTER(bool, isCurrentTemperaturePresent, BatteryHealthStatus)
    {
        return (btSpecObject.flags & BHS_FLAG_CURRENT_TEMPERATURE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isDeepDischargeCountPresent, BatteryHealthStatus)
    {
        return (btSpecObject.flags & BHS_FLAG_DEEP_DISCHARGE_COUNT_PRESENT) != 0;
    }

    BVP_GETTER(uint8_t, batteryHealthSummary, BatteryHealthStatus)
    {
        return btSpecObject.batteryHealthSummary;
    }

    BVP_GETTER(uint16_t, cycleCount, BatteryHealthStatus)
    {
        return btSpecObject.cycleCount;
    }

    BVP_GETTER(int8_t, currentTemperature, BatteryHealthStatus)
    {
        return btSpecObject.currentTemperature;
    }

    BVP_GETTER(uint16_t, deepDischargeCount, BatteryHealthStatus)
    {
        return btSpecObject.deepDischargeCount;
    }

    BVP_GETTER(bool, isCurrentTemperatureGreater, BatteryHealthStatus)
    {
        return BHS_GREATER == btSpecObject.currentTemperature;
    }

    BVP_GETTER(bool, isCurrentTemperatureLess, BatteryHealthStatus)
    {
        return BHS_LESS == btSpecObject.currentTemperature;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryHealthStatus)

    BVP_PARSE(BatteryHealthStatus)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt8();

        if (isBatteryHealthSummaryPresent(btSpecObject))
        {
            btSpecObject.batteryHealthSummary = parser.parseUInt8();
            if (btSpecObject.batteryHealthSummary > 100)
            {
                return false;
            }
        }
        if (isCycleCountPresent(btSpecObject))
        {
            btSpecObject.cycleCount = parser.parseUInt16();
        }
        if (isCurrentTemperaturePresent(btSpecObject))
        {
            btSpecObject.currentTemperature = parser.parseInt8();
        }
        if (isDeepDischargeCountPresent(btSpecObject))
        {
            btSpecObject.deepDischargeCount = parser.parseUInt16();
        }

        return result;
    }

    BVP_TO_STRING(BatteryHealthStatus)
    {
        (void)configuration;
        std::string str;

        if (isBatteryHealthSummaryPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                "BatteryHealthSummary: {}%, ",
                btSpecObject.batteryHealthSummary
            );
        }
        if (isCycleCountPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                "CycleCount: {}, ",
                btSpecObject.cycleCount
            );
        }
        if (isCurrentTemperaturePresent(btSpecObject))
        {
            str.append("CurrentTemperature: ");
            if (isCurrentTemperatureGreater(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BHS_MAX is constexpr
                fmt::format_to(std::back_inserter(str), ">{}°C, ", BHS_MAX);
            }
            else if (isCurrentTemperatureLess(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BHS_MIN is constexpr
                fmt::format_to(std::back_inserter(str), "<{}°C, ", BHS_MIN);
            }
            else
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{}°C, ",
                    btSpecObject.currentTemperature
                );
            }
        }
        if (isDeepDischargeCountPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                "DeepDischargeCount: {}, ",
                btSpecObject.deepDischargeCount
            );
        }

        if (str.empty())
        {
            return "<NoData>";
        }

        str.pop_back();
        str.pop_back();

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size > 0 && size < 8;
    }
};

}  // namespace bvp
