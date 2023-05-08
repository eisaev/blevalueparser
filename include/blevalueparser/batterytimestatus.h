#pragma once

#include "basevalue.h"


namespace bvp
{

namespace
{
constexpr uint32_t BTS_UNKNOWN = 0xFFFFFF;
constexpr uint32_t BTS_GREATER = 0xFFFFFE;
constexpr uint32_t BTS_MAX = BTS_GREATER - 1;
}

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
BVP_STRUCT(BatteryTimeStatus)
{
    uint8_t flags{0};
    uint32_t timeUntilDischarged{0};  // org.bluetooth.unit.time.minute
    uint32_t timeUntilDischargedOnStandby{0};  // org.bluetooth.unit.time.minute
    uint32_t timeUntilRecharged{0};  // org.bluetooth.unit.time.minute
};

class BatteryTimeStatus final : public BaseValueSpec<BatteryTimeStatus>
{
public:
    BVP_GETTER(bool, isTimeUntilDischargedOnStandbyPresent, BatteryTimeStatus)
    {
        return (btSpecObject.flags & BTS_FLAG_TIME_UNTIL_DISCHARGED_ON_STANDBY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isTimeUntilRechargedPresent, BatteryTimeStatus)
    {
        return (btSpecObject.flags & BTS_FLAG_TIME_UNTIL_RECHARGED_PRESENT) != 0;
    }

    BVP_GETTER(uint32_t, timeUntilDischarged, BatteryTimeStatus)
    {
        return btSpecObject.timeUntilDischarged;
    }

    BVP_GETTER(uint32_t, timeUntilDischargedOnStandby, BatteryTimeStatus)
    {
        return btSpecObject.timeUntilDischargedOnStandby;
    }

    BVP_GETTER(uint32_t, timeUntilRecharged, BatteryTimeStatus)
    {
        return btSpecObject.timeUntilRecharged;
    }

    BVP_GETTER(bool, isTimeUntilDischargedUnknown, BatteryTimeStatus)
    {
        return BTS_UNKNOWN == btSpecObject.timeUntilDischarged;
    }

    BVP_GETTER(bool, isTimeUntilDischargedOnStandbyUnknown, BatteryTimeStatus)
    {
        return BTS_UNKNOWN == btSpecObject.timeUntilDischargedOnStandby;
    }

    BVP_GETTER(bool, isTimeUntilRechargedUnknown, BatteryTimeStatus)
    {
        return BTS_UNKNOWN == btSpecObject.timeUntilRecharged;
    }

    BVP_GETTER(bool, isTimeUntilDischargedGreater, BatteryTimeStatus)
    {
        return BTS_GREATER == btSpecObject.timeUntilDischarged;
    }

    BVP_GETTER(bool, isTimeUntilDischargedOnStandbyGreater, BatteryTimeStatus)
    {
        return BTS_GREATER == btSpecObject.timeUntilDischargedOnStandby;
    }

    BVP_GETTER(bool, isTimeUntilRechargedGreater, BatteryTimeStatus)
    {
        return BTS_GREATER == btSpecObject.timeUntilRecharged;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryTimeStatus)

    BVP_PARSE(BatteryTimeStatus)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt8();
        btSpecObject.timeUntilDischarged = parser.parseUInt24();

        if (isTimeUntilDischargedOnStandbyPresent(btSpecObject))
        {
            btSpecObject.timeUntilDischargedOnStandby = parser.parseUInt24();
        }
        if (isTimeUntilRechargedPresent(btSpecObject))
        {
            btSpecObject.timeUntilRecharged = parser.parseUInt24();
        }

        return result;
    }

    BVP_TO_STRING(BatteryTimeStatus)
    {
        (void)configuration;
        std::string str;

        str.append("TimeUntilDischarged: ");
        if (isTimeUntilDischargedUnknown(btSpecObject))
        {
            str.append("<Unknown>");
        }
        else if (isTimeUntilDischargedGreater(btSpecObject))
        {
            // TODO: it should be possible to format this at compile time because BTS_MAX is constexpr
            fmt::format_to(std::back_inserter(str), ">{} minutes", BTS_MAX);
        }
        else
        {
            fmt::format_to(
                std::back_inserter(str),
                "{} minutes",
                btSpecObject.timeUntilDischarged
            );
        }

        if (isTimeUntilDischargedOnStandbyPresent(btSpecObject))
        {
            str.append(", TimeUntilDischargedOnStandby: ");
            if (isTimeUntilDischargedOnStandbyUnknown(btSpecObject))
            {
                str.append("<Unknown>");
            }
            else if (isTimeUntilDischargedOnStandbyGreater(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BTS_MAX is constexpr
                fmt::format_to(std::back_inserter(str), ">{} minutes", BTS_MAX);
            }
            else
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{} minutes",
                    btSpecObject.timeUntilDischargedOnStandby
                );
            }
        }

        if (isTimeUntilRechargedPresent(btSpecObject))
        {
            str.append(", TimeUntilRecharged: ");
            if (isTimeUntilRechargedUnknown(btSpecObject))
            {
                str.append("<Unknown>");
            }
            else if (isTimeUntilRechargedGreater(btSpecObject))
            {
                // TODO: it should be possible to format this at compile time because BTS_MAX is constexpr
                fmt::format_to(std::back_inserter(str), ">{} minutes", BTS_MAX);
            }
            else
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{} minutes",
                    btSpecObject.timeUntilRecharged
                );
            }
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size > 3 && size < 11;
    }
};

}  // namespace bvp
