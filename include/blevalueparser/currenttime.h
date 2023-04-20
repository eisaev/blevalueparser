#pragma once

#include <cassert>

#include "basevalue.h"
#include "exacttime256.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.62 Current Time
// Table 3.106: Structure of the Current Time characteristic
// Adjust Reason
constexpr uint8_t CTS_FLAG_MANUAL      = 1 << 0;
constexpr uint8_t CTS_FLAG_EXTERNAL    = 1 << 1;
constexpr uint8_t CTS_FLAG_TZ_CHANGED  = 1 << 2;
constexpr uint8_t CTS_FLAG_DST_CHANGED = 1 << 3;
constexpr uint8_t CTS_FLAG_RESERVED1   = 1 << 4;
constexpr uint8_t CTS_FLAG_RESERVED2   = 1 << 5;
constexpr uint8_t CTS_FLAG_RESERVED3   = 1 << 6;
constexpr uint8_t CTS_FLAG_RESERVED4   = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.62 Current Time
struct CurrentTimeStruct
{
    ExactTime256Struct exactTime256;
    // See CTS_FLAG_*
    uint8_t adjustReason{0};
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.1 Current Time
class CurrentTime final : public BaseValueSpec<CurrentTimeStruct>
{
public:
    BVP_GETTER(uint16_t, year, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dateTime.year;
    }

    BVP_GETTER(uint8_t, month, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dateTime.month;
    }

    BVP_GETTER(uint8_t, day, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dateTime.day;
    }

    BVP_GETTER(uint8_t, hour, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dateTime.hour;
    }

    BVP_GETTER(uint8_t, minute, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dateTime.minute;
    }

    BVP_GETTER(uint8_t, seconds, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dateTime.seconds;
    }

    BVP_GETTER(DayOfWeekEnum, dayOfWeek, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.dayDateTime.dayOfWeek.dayOfWeek;
    }

    BVP_GETTER(uint8_t, fractionsOfSeconds, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.fractions256;
    }

    BVP_GETTER(uint16_t, milliseconds, CurrentTimeStruct)
    {
        return btSpecObject.exactTime256.fractions256 * 1000 / 256;
    }

    BVP_GETTER(bool, isManuallyAdjusted, CurrentTimeStruct)
    {
        return (btSpecObject.adjustReason & CTS_FLAG_MANUAL) != 0;
    }

    BVP_GETTER(bool, isExternalReference, CurrentTimeStruct)
    {
        return (btSpecObject.adjustReason & CTS_FLAG_EXTERNAL) != 0;
    }

    BVP_GETTER(bool, isTZChanged, CurrentTimeStruct)
    {
        return (btSpecObject.adjustReason & CTS_FLAG_TZ_CHANGED) != 0;
    }

    BVP_GETTER(bool, isDSTChanged, CurrentTimeStruct)
    {
        return (btSpecObject.adjustReason & CTS_FLAG_DST_CHANGED) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, CurrentTime, CurrentTimeStruct)

    BVP_PARSE(CurrentTimeStruct)
    {
        bool result{true};

        result &= ExactTime256::parse(parser, btSpecObject.exactTime256);

        // 3.1.2.1 Manual Time Update
        // 3.1.2.2 External Reference Time Update
        // 3.1.2.3 Change of Time Zone
        // 3.1.2.4 Change of DST Offset
        btSpecObject.adjustReason = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(CurrentTimeStruct)
    {
        std::string str;

        str.append(ExactTime256::toStringInternal(btSpecObject.exactTime256));

        std::string adjustReason;
        if (isManuallyAdjusted(btSpecObject))
        {
            adjustReason.append(" ManuallyAdjusted");
        }
        if (isExternalReference(btSpecObject))
        {
            adjustReason.append(" ExternalReference");
        }
        if (isTZChanged(btSpecObject))
        {
            adjustReason.append(" TZChanged");
        }
        if (isDSTChanged(btSpecObject))
        {
            adjustReason.append(" DSTChanged");
        }

        if (!adjustReason.empty())
        {
            str.append(" (adjust reason: {");
            str.append(adjustReason);
            str.append(" })");
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 10;
    }
};

}  // namespace bvp
