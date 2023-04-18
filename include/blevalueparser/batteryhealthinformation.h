#pragma once

#include "basevalue.h"


namespace bvp
{

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
struct BatteryHealthInformationStruct
{
    uint8_t flags{0};
    uint16_t cycleCountDesignedLifetime{0};
    int8_t minDesignedOperatingTemperature{0};  // org.bluetooth.unit.thermodynamic_temperature.degree_celsius
    int8_t maxDesignedOperatingTemperature{0};  // org.bluetooth.unit.thermodynamic_temperature.degree_celsius
};

class BatteryHealthInformation final : public BaseValueSpec<BatteryHealthInformationStruct>
{
public:
    BVP_GETTER(bool, isCycleCountDesignedLifetimePresent, BatteryHealthInformationStruct)
    {
        return (btSpecObject.flags & BHI_FLAG_CYCLE_COUNT_DESIGNED_LIFETIME_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMinAndMaxDesignedOperatingTemperaturePresent, BatteryHealthInformationStruct)
    {
        return (btSpecObject.flags & BHI_FLAG_MIN_AND_MAX_DESIGNED_OPERATING_TEMPERATURE_PRESENT) != 0;
    }

    BVP_GETTER(uint16_t, cycleCountDesignedLifetime, BatteryHealthInformationStruct)
    {
        return btSpecObject.cycleCountDesignedLifetime;
    }

    BVP_GETTER(int8_t, minDesignedOperatingTemperature, BatteryHealthInformationStruct)
    {
        return btSpecObject.minDesignedOperatingTemperature;
    }

    BVP_GETTER(int8_t, maxDesignedOperatingTemperature, BatteryHealthInformationStruct)
    {
        return btSpecObject.maxDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMinDesignedOperatingTemperatureGreater, BatteryHealthInformationStruct)
    {
        return s_greater == btSpecObject.minDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMinDesignedOperatingTemperatureLess, BatteryHealthInformationStruct)
    {
        return s_less == btSpecObject.minDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMaxDesignedOperatingTemperatureGreater, BatteryHealthInformationStruct)
    {
        return s_greater == btSpecObject.maxDesignedOperatingTemperature;
    }

    BVP_GETTER(bool, isMaxDesignedOperatingTemperatureLess, BatteryHealthInformationStruct)
    {
        return s_less == btSpecObject.maxDesignedOperatingTemperature;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryHealthInformation, BatteryHealthInformationStruct)

    static constexpr int8_t s_greater = 127;  // 0x7F
    static constexpr int8_t s_less = -128;  // 0x80
    static constexpr int8_t s_max = s_greater - 1;
    static constexpr int8_t s_min = s_less + 1;

    virtual bool checkSize(size_t size) override
    {
        return size > 0 && size < 6;
    }

    BVP_PARSE(BatteryHealthInformationStruct)
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

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        std::ostringstream ossInfo;
        if (isCycleCountDesignedLifetimePresent())
        {
            ossInfo << "CycleCountDesignedLifetime: " << m_btSpecObject.cycleCountDesignedLifetime << ", ";
        }
        if (isMinAndMaxDesignedOperatingTemperaturePresent())
        {
            ossInfo << "MinDesignedOperatingTemperature: ";
            if (isMinDesignedOperatingTemperatureGreater())
            {
                ossInfo << ">" << static_cast<int>(s_max) << "°C, ";
            }
            else if (isMinDesignedOperatingTemperatureLess())
            {
                ossInfo << "<" << static_cast<int>(s_min) << "°C, ";
            }
            else
            {
                ossInfo << static_cast<int>(m_btSpecObject.minDesignedOperatingTemperature) << "°C, ";
            }
            ossInfo << "MaxDesignedOperatingTemperature: ";
            if (isMaxDesignedOperatingTemperatureGreater())
            {
                ossInfo << ">" << static_cast<int>(s_max) << "°C, ";
            }
            else if (isMaxDesignedOperatingTemperatureLess())
            {
                ossInfo << "<" << static_cast<int>(s_min) << "°C, ";
            }
            else
            {
                ossInfo << static_cast<int>(m_btSpecObject.maxDesignedOperatingTemperature) << "°C, ";
            }
        }
        std::string info = ossInfo.str();

        if (info.empty())
        {
            oss << "<NoData>";
        }
        else
        {
            oss << info.substr(0, info.length() - 2);
        }
    }
};

}  // namespace bvp
