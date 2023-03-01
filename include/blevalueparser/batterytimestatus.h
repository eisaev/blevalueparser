#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.29.1 Flags field
constexpr uint8_t BTS_FLAG_TIME_UNTIL_DISCHARGED_ON_STANDBY_PRESENT = 1 << 0;
constexpr uint8_t BTS_FLAG_TIME_UNTIL_RECHARGED_PRESENT             = 1 << 1;
constexpr uint8_t BTS_FLAG_RESERVED1                                = 1 << 2;
constexpr uint8_t BTS_FLAG_RESERVED2                                = 1 << 3;
constexpr uint8_t BTS_FLAG_RESERVED3                                = 1 << 4;
constexpr uint8_t BTS_FLAG_RESERVED4                                = 1 << 5;
constexpr uint8_t BTS_FLAG_RESERVED5                                = 1 << 6;
constexpr uint8_t BTS_FLAG_RESERVED6                                = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.29 Battery Time Status
struct BatteryTimeStatusStruct
{
    uint8_t flags{0};
    uint32_t timeUntilDischarged{0};  // org.bluetooth.unit.time.minute
    uint32_t timeUntilDischargedOnStandby{0};  // org.bluetooth.unit.time.minute
    uint32_t timeUntilRecharged{0};  // org.bluetooth.unit.time.minute
};

class BatteryTimeStatus final : public BaseValueSpec<BatteryTimeStatusStruct>
{
public:
    bool isTimeUntilDischargedOnStandbyPresent() const
    {
        return (m_btSpecObject.flags & BTS_FLAG_TIME_UNTIL_DISCHARGED_ON_STANDBY_PRESENT) != 0;
    }

    bool isTimeUntilRechargedPresent() const
    {
        return (m_btSpecObject.flags & BTS_FLAG_TIME_UNTIL_RECHARGED_PRESENT) != 0;
    }

    uint32_t timeUntilDischarged() const
    {
        return m_btSpecObject.timeUntilDischarged;
    }

    uint32_t timeUntilDischargedOnStandby() const
    {
        return m_btSpecObject.timeUntilDischargedOnStandby;
    }

    uint32_t timeUntilRecharged() const
    {
        return m_btSpecObject.timeUntilRecharged;
    }

    bool isTimeUntilDischargedUnknown() const
    {
        return s_unknown == m_btSpecObject.timeUntilDischarged;
    }

    bool isTimeUntilDischargedOnStandbyUnknown() const
    {
        return s_unknown == m_btSpecObject.timeUntilDischargedOnStandby;
    }

    bool isTimeUntilRechargedUnknown() const
    {
        return s_unknown == m_btSpecObject.timeUntilRecharged;
    }

    bool isTimeUntilDischargedGreater() const
    {
        return s_greater == m_btSpecObject.timeUntilDischarged;
    }

    bool isTimeUntilDischargedOnStandbyGreater() const
    {
        return s_greater == m_btSpecObject.timeUntilDischargedOnStandby;
    }

    bool isTimeUntilRechargedGreater() const
    {
        return s_greater == m_btSpecObject.timeUntilRecharged;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryTimeStatus, BatteryTimeStatusStruct)

    static constexpr uint32_t s_unknown = 0xFFFFFF;
    static constexpr uint32_t s_greater = 0xFFFFFE;
    static constexpr uint32_t s_max = s_greater - 1;

    virtual bool checkSize(size_t size) override
    {
        return size > 3 && size < 11;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.flags = parser.parseUInt8();
        m_btSpecObject.timeUntilDischarged = parser.parseUInt24();

        if (isTimeUntilDischargedOnStandbyPresent())
        {
            m_btSpecObject.timeUntilDischargedOnStandby = parser.parseUInt24();
        }
        if (isTimeUntilRechargedPresent())
        {
            m_btSpecObject.timeUntilRecharged = parser.parseUInt24();
        }

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << "TimeUntilDischarged: ";
        if (isTimeUntilDischargedUnknown())
        {
            oss << "<Unknown>";
        }
        else if (isTimeUntilDischargedGreater())
        {
            oss << ">" << s_max << " minutes";
        }
        else
        {
            oss << m_btSpecObject.timeUntilDischarged << " minutes";
        }

        if (isTimeUntilDischargedOnStandbyPresent())
        {
            oss << ", TimeUntilDischargedOnStandby: ";
            if (isTimeUntilDischargedOnStandbyUnknown())
            {
                oss << "<Unknown>";
            }
            else if (isTimeUntilDischargedOnStandbyGreater())
            {
                oss << ">" << s_max << " minutes";
            }
            else
            {
                oss << m_btSpecObject.timeUntilDischargedOnStandby << " minutes";
            }
        }
        if (isTimeUntilRechargedPresent())
        {
            oss << ", TimeUntilRecharged: ";
            if (isTimeUntilRechargedUnknown())
            {
                oss << "<Unknown>";
            }
            else if (isTimeUntilRechargedGreater())
            {
                oss << ">" << s_max << " minutes";
            }
            else
            {
                oss << m_btSpecObject.timeUntilRecharged << " minutes";
            }
        }
    }
};

}  // namespace bvp
