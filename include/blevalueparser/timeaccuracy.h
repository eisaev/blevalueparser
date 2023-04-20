#pragma once

#include "basevalue.h"


namespace bvp
{

constexpr uint8_t TMA_LARGER = 254;
constexpr uint8_t TMA_UNKNOWN = 255;
constexpr uint8_t TMA_MULTIPLIER = 125;
constexpr uint32_t TMA_MAX = (TMA_LARGER - 1) * TMA_MULTIPLIER;

// GATT_Specification_Supplement_v8.pdf
// 3.220 Time Accuracy

struct TimeAccuracyStruct
{
    uint8_t accuracy{0};
};

class TimeAccuracy final : public BaseValueSpec<TimeAccuracyStruct>
{
public:
    friend class ReferenceTimeInformation;

    BVP_GETTER(bool, isLarger, TimeAccuracyStruct)
    {
        // A value of 254 means drift is larger than 31.625s.
        return btSpecObject.accuracy == TMA_LARGER;
    }

    BVP_GETTER(bool, isUnknown, TimeAccuracyStruct)
    {
        // A value of 255 means drift is unknown.
        return btSpecObject.accuracy == TMA_UNKNOWN;
    }

    BVP_GETTER(uint16_t, accuracyMs, TimeAccuracyStruct)
    {
        if (btSpecObject.accuracy >= TMA_LARGER)
        {
            return UINT16_MAX;
        }

        // This field represents accuracy (drift) of time information
        // in steps of 1/8 of a second (125ms) compared to a reference time source.
        return btSpecObject.accuracy * TMA_MULTIPLIER;
    }

private:
    BVP_CTORS(BaseValueSpec, TimeAccuracy, TimeAccuracyStruct)

    BVP_PARSE(TimeAccuracyStruct)
    {
        bool result{true};

        btSpecObject.accuracy = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(TimeAccuracyStruct)
    {
        if (isUnknown(btSpecObject))
        {
            return "<Unknown>";
        }

        if (isLarger(btSpecObject))
        {
            // TODO: it should be possible to format this at compile time because TMA_MAX is constexpr
            return fmt::format(">{}ms", TMA_MAX);
        }

        return fmt::format("{}ms", accuracyMs(btSpecObject));
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
