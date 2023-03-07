#pragma once

#include "basevalue.h"


namespace bvp
{

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
struct BatteryHealthStatusStruct
{
    uint8_t flags{0};
    uint8_t batteryHealthSummary{0};  // org.bluetooth.unit.percentage
    uint16_t cycleCount{0};
    int8_t currentTemperature{0};  // org.bluetooth.unit.thermodynamic_temperature.degree_celsius
    uint16_t deepDischargeCount{0};
};

class BatteryHealthStatus final : public BaseValueSpec<BatteryHealthStatusStruct>
{
public:
    bool isBatteryHealthSummaryPresent() const
    {
        return (m_btSpecObject.flags & BHS_FLAG_BATTERY_HEALTH_SUMMARY_PRESENT) != 0;
    }

    bool isCycleCountPresent() const
    {
        return (m_btSpecObject.flags & BHS_FLAG_CYCLE_COUNT_PRESENT) != 0;
    }

    bool isCurrentTemperaturePresent() const
    {
        return (m_btSpecObject.flags & BHS_FLAG_CURRENT_TEMPERATURE_PRESENT) != 0;
    }

    bool isDeepDischargeCountPresent() const
    {
        return (m_btSpecObject.flags & BHS_FLAG_DEEP_DISCHARGE_COUNT_PRESENT) != 0;
    }

    uint8_t batteryHealthSummary() const
    {
        return m_btSpecObject.batteryHealthSummary;
    }

    uint16_t cycleCount() const
    {
        return m_btSpecObject.cycleCount;
    }

    int8_t currentTemperature() const
    {
        return m_btSpecObject.currentTemperature;
    }

    uint16_t deepDischargeCount() const
    {
        return m_btSpecObject.deepDischargeCount;
    }

    bool isCurrentTemperatureGreater() const
    {
        return s_greater == m_btSpecObject.currentTemperature;
    }

    bool isCurrentTemperatureLess() const
    {
        return s_less == m_btSpecObject.currentTemperature;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryHealthStatus, BatteryHealthStatusStruct)

    static constexpr int8_t s_greater = 127;  // 0x7F
    static constexpr int8_t s_less = -128;  // 0x80
    static constexpr int8_t s_max = s_greater - 1;
    static constexpr int8_t s_min = s_less + 1;

    virtual bool checkSize(size_t size) override
    {
        return size > 0 && size < 8;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.flags = parser.parseUInt8();

        if (isBatteryHealthSummaryPresent())
        {
            m_btSpecObject.batteryHealthSummary = parser.parseUInt8();
            if (m_btSpecObject.batteryHealthSummary > 100)
            {
                return false;
            }
        }
        if (isCycleCountPresent())
        {
            m_btSpecObject.cycleCount = parser.parseUInt16();
        }
        if (isCurrentTemperaturePresent())
        {
            m_btSpecObject.currentTemperature = parser.parseInt8();
        }
        if (isDeepDischargeCountPresent())
        {
            m_btSpecObject.deepDischargeCount = parser.parseUInt16();
        }

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        std::ostringstream ossInfo;
        if (isBatteryHealthSummaryPresent())
        {
            ossInfo << "BatteryHealthSummary: " << static_cast<int>(m_btSpecObject.batteryHealthSummary) << "%, ";
        }
        if (isCycleCountPresent())
        {
            ossInfo << "CycleCount: " << m_btSpecObject.cycleCount << ", ";
        }
        if (isCurrentTemperaturePresent())
        {
            ossInfo << "CurrentTemperature: ";
            if (isCurrentTemperatureGreater())
            {
                ossInfo << ">" << static_cast<int>(s_max) << "°C, ";
            }
            else if (isCurrentTemperatureLess())
            {
                ossInfo << "<" << static_cast<int>(s_min) << "°C, ";
            }
            else
            {
                ossInfo << static_cast<int>(m_btSpecObject.currentTemperature) << "°C, ";
            }
        }
        if (isDeepDischargeCountPresent())
        {
            ossInfo << "DeepDischargeCount: " << m_btSpecObject.deepDischargeCount << ", ";
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
