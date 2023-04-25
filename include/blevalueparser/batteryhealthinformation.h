#pragma once

#include "basevalue.h"


namespace bvp
{

constexpr int8_t BHI_GREATER = 127;  // 0x7F
constexpr int8_t BHI_LESS = -128;  // 0x80
constexpr int8_t BHI_MAX = BHI_GREATER - 1;
constexpr int8_t BHI_MIN = BHI_LESS + 1;

// GATT_Specification_Supplement_v8.pdf
// 3.24.1 Flags field
constexpr uint8_t BHI_FLAG_CYCLE_COUNT_DESIGNED_LIFETIME_PRESENT                = 1 << 0;
constexpr uint8_t BHI_FLAG_MIN_AND_MAX_DESIGNED_OPERATING_TEMPERATURE_PRESENT   = 1 << 1;
constexpr uint8_t BHI_FLAG_RESERVED1                                            = 1 << 2;
constexpr uint8_t BHI_FLAG_RESERVED2                                            = 1 << 3;
constexpr uint8_t BHI_FLAG_RESERVED3                                            = 1 << 4;
constexpr uint8_t BHI_FLAG_RESERVED4                                            = 1 << 5;
constexpr uint8_t BHI_FLAG_RESERVED5                                            = 1 << 6;
constexpr uint8_t BHI_FLAG_RESERVED6                                            = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.24 Battery Health Information
BVP_STRUCT(BatteryHealthInformation)
{
    uint8_t flags{0};
    uint16_t cycleCountDesignedLifetime{0};
    int8_t minDesignedOperatingTemperature{0};  // org.bluetooth.unit.thermodynamic_temperature.degree_celsius
    int8_t maxDesignedOperatingTemperature{0};  // org.bluetooth.unit.thermodynamic_temperature.degree_celsius
};

class BatteryHealthInformation final : public BaseValueSpec<BatteryHealthInformation>
{
public:
    BVP_GETTER(bool, isCycleCountDesignedLifetimePresent, BatteryHealthInformation)
    {
        return (btSpecObject.flags & BHI_FLAG_CYCLE_COUNT_DESIGNED_LIFETIME_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMinAndMaxDesignedOperatingTemperaturePresent, BatteryHealthInformation)
    {
        return (btSpecObject.flags & BHI_FLAG_MIN_AND_MAX_DESIGNED_OPERATING_TEMPERATURE_PRESENT) != 0;
    }

    BVP_GETTER(uint16_t, cycleCountDesignedLifetime, BatteryHealthInformation)
    {
        return btSpecObject.cycleCountDesignedLifetime;
    }

    BVP_GETTER(int8_t, minDesignedOperatingTemperature, BatteryHealthInformation)
    {
        return btSpecObject.minDesignedOperatingTemperature;
    }

    BVP_GETTER(int8_t, maxDesignedOperatingTemperature, BatteryHealthInformation)
    {
        return btSpecObject.maxDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMinDesignedOperatingTemperatureGreater, BatteryHealthInformation)
    {
        return BHI_GREATER == btSpecObject.minDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMinDesignedOperatingTemperatureLess, BatteryHealthInformation)
    {
        return BHI_LESS == btSpecObject.minDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMaxDesignedOperatingTemperatureGreater, BatteryHealthInformation)
    {
        return BHI_GREATER == btSpecObject.maxDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMaxDesignedOperatingTemperatureLess, BatteryHealthInformation)
    {
        return BHI_LESS == btSpecObject.maxDesignedOperatingTemperature;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryHealthInformation)

    BVP_PARSE(BatteryHealthInformation)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt8();

        if (isCycleCountDesignedLifetimePresent(btSpecObject))
        {
            btSpecObject.cycleCountDesignedLifetime = parser.parseUInt16();
        }
        if (isMinAndMaxDesignedOperatingTemperaturePresent(btSpecObject))
        {
            btSpecObject.minDesignedOperatingTemperature = parser.parseInt8();
            btSpecObject.maxDesignedOperatingTemperature = parser.parseInt8();
            if (btSpecObject.minDesignedOperatingTemperature > btSpecObject.maxDesignedOperatingTemperature)
            {
                return false;
            }
        }

        return result;
    }

    BVP_TO_STRING(BatteryHealthInformation)
    {
        (void)configuration;
        std::string str;

        if (isCycleCountDesignedLifetimePresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                "CycleCountDesignedLifetime: {}, ",
                btSpecObject.cycleCountDesignedLifetime
            );
        }
        if (isMinAndMaxDesignedOperatingTemperaturePresent(btSpecObject))
        {
            str.append("MinDesignedOperatingTemperature: ");
            if (isMinDesignedOperatingTemperatureGreater(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BHI_MAX is constexpr
                fmt::format_to(std::back_inserter(str), ">{}°C, ", BHI_MAX);
            }
            else if (isMinDesignedOperatingTemperatureLess(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BHI_MIN is constexpr
                fmt::format_to(std::back_inserter(str), "<{}°C, ", BHI_MIN);
            }
            else
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{}°C, ",
                    btSpecObject.minDesignedOperatingTemperature
                );
            }

            str.append("MaxDesignedOperatingTemperature: ");
            if (isMaxDesignedOperatingTemperatureGreater(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BHI_MAX is constexpr
                fmt::format_to(std::back_inserter(str), ">{}°C, ", BHI_MAX);
            }
            else if (isMaxDesignedOperatingTemperatureLess(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BHI_MIN is constexpr
                fmt::format_to(std::back_inserter(str), "<{}°C, ", BHI_MIN);
            }
            else
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{}°C, ",
                    btSpecObject.maxDesignedOperatingTemperature
                );
            }
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
        return size > 0 && size < 6;
    }
};

}  // namespace bvp
