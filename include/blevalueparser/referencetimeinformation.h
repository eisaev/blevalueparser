#pragma once

#include "basevalue.h"
#include "timesource.h"
#include "timeaccuracy.h"


namespace bvp
{

constexpr uint8_t RTI_GREATER = 255;
constexpr uint8_t RTI_MAX = RTI_GREATER - 1;
constexpr uint8_t RTI_HOURS_PER_DAY = 24;
constexpr uint8_t RTI_MAX_HOURS = RTI_HOURS_PER_DAY - 1;

// GATT_Specification_Supplement_v8.pdf
// 3.178 Reference Time Information
BVP_STRUCT(ReferenceTimeInformation)
{
    Struct<TimeSource> timeSource;
    Struct<TimeAccuracy> timeAccuracy;
    uint8_t daysSinceUpdate{0};
    uint8_t hoursSinceUpdate{0};
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.3 Reference Time Information
class ReferenceTimeInformation final : public BaseValueSpec<ReferenceTimeInformation>
{
public:
    BVP_GETTER(TimeSourceEnum, timeSource, ReferenceTimeInformation)
    {
        return btSpecObject.timeSource.timeSource;
    }

    BVP_GETTER(bool, isTimeAccuracyLarger, ReferenceTimeInformation)
    {
        return TimeAccuracy::isLarger(btSpecObject.timeAccuracy);
    }

    BVP_GETTER(bool, isTimeAccuracyUnknown, ReferenceTimeInformation)
    {
        return TimeAccuracy::isUnknown(btSpecObject.timeAccuracy);
    }

    BVP_GETTER(uint16_t, timeAccuracyMs, ReferenceTimeInformation)
    {
        return TimeAccuracy::accuracyMs(btSpecObject.timeAccuracy);
    }

    BVP_GETTER(uint8_t, daysSinceUpdate, ReferenceTimeInformation)
    {
        return btSpecObject.daysSinceUpdate;
    }

    BVP_GETTER(uint8_t, hoursSinceUpdate, ReferenceTimeInformation)
    {
        return btSpecObject.hoursSinceUpdate;
    }

    BVP_GETTER(bool, isSinceUpdateGreater, ReferenceTimeInformation)
    {
        return RTI_GREATER == (daysSinceUpdate(btSpecObject) & hoursSinceUpdate(btSpecObject));
    }

    BVP_GETTER(uint32_t, timeSinceUpdateH, ReferenceTimeInformation)
    {
        if (isSinceUpdateGreater(btSpecObject))
        {
            return UINT32_MAX;
        }

        return btSpecObject.daysSinceUpdate * RTI_HOURS_PER_DAY + btSpecObject.hoursSinceUpdate;
    }

private:
    BVP_CTORS(BaseValueSpec, ReferenceTimeInformation)

    BVP_PARSE(ReferenceTimeInformation)
    {
        bool result{true};

        // GATT_Specification_Supplement_v8.pdf
        // 3.178 Reference Time Information
        result &= TimeSource::parse(parser, btSpecObject.timeSource);
        result &= TimeAccuracy::parse(parser, btSpecObject.timeAccuracy);
        btSpecObject.daysSinceUpdate = parser.parseUInt8();
        btSpecObject.hoursSinceUpdate = parser.parseUInt8();
        if (RTI_GREATER != btSpecObject.hoursSinceUpdate &&
            RTI_MAX_HOURS < btSpecObject.hoursSinceUpdate)
        {
            return false;
        }

        if ((RTI_GREATER == btSpecObject.daysSinceUpdate &&
             RTI_GREATER != btSpecObject.hoursSinceUpdate) ||
            (RTI_GREATER == btSpecObject.hoursSinceUpdate &&
             RTI_GREATER != btSpecObject.daysSinceUpdate))
        {
            return false;
        }

        return result;
    }

    BVP_TO_STRING(ReferenceTimeInformation)
    {
        std::string str;

        str.append("Src: ");
        str.append(TimeSource::toStringInternal(btSpecObject.timeSource, configuration));

        str.append(", Drift: ");
        str.append(TimeAccuracy::toStringInternal(btSpecObject.timeAccuracy, configuration));

        str.append(", Updated: ");
        if (isSinceUpdateGreater(btSpecObject))
        {
            // TODO: it should be possible to format this at compile time because RTI_MAX is constexpr
            fmt::format_to(std::back_inserter(str), ">{} days ago", RTI_MAX);
            return str;
        }

        if (btSpecObject.daysSinceUpdate)
        {
            fmt::format_to(
                std::back_inserter(str),
                "{} days ",
                btSpecObject.daysSinceUpdate
            );
        }
        fmt::format_to(
            std::back_inserter(str),
            "{} hours ago",
            btSpecObject.hoursSinceUpdate
        );

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 4;
    }
};

}  // namespace bvp
