#pragma once

#include "basevalue.h"


namespace bvp
{

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
        return btSpecObject.accuracy == s_timeAccuracyLarge;
    }

    BVP_GETTER(bool, isUnknown, TimeAccuracyStruct)
    {
        // A value of 255 means drift is unknown.
        return btSpecObject.accuracy == s_timeAccuracyUnknown;
    }

    BVP_GETTER(uint16_t, accuracyMs, TimeAccuracyStruct)
    {
        if (btSpecObject.accuracy >= s_timeAccuracyLarge)
        {
            return UINT16_MAX;
        }

        // This field represents accuracy (drift) of time information
        // in steps of 1/8 of a second (125ms) compared to a reference time source.
        return btSpecObject.accuracy * 125;
    }

private:
    BVP_CTORS(BaseValueSpec, TimeAccuracy, TimeAccuracyStruct)

    static constexpr uint8_t s_timeAccuracyLarge   = 254;
    static constexpr uint8_t s_timeAccuracyUnknown = 255;

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    BVP_PARSE(TimeAccuracyStruct)
    {
        bool result{true};

        btSpecObject.accuracy = parser.parseUInt8();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        if (isUnknown())
        {
            oss << "<Unknown>";
            return;
        }

        if (isLarger())
        {
            oss << ">31625ms";
            return;
        }

        oss << accuracyMs() << "ms";
    }
};

}  // namespace bvp
