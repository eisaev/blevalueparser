#pragma once

#include "basevalue.h"
#include "timesource.h"
#include "timeaccuracy.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.178 Reference Time Information
struct ReferenceTimeInformationStruct
{
    TimeSourceStruct timeSource;
    TimeAccuracyStruct timeAccuracy;
    uint8_t daysSinceUpdate{0};
    uint8_t hoursSinceUpdate{0};
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.3 Reference Time Information
class ReferenceTimeInformation final : public BaseValueSpec<ReferenceTimeInformationStruct>
{
public:
    BVP_GETTER(TimeSourceEnum, timeSource, ReferenceTimeInformationStruct)
    {
        return btSpecObject.timeSource.timeSource;
    }

    BVP_GETTER(bool, isTimeAccuracyLarger, ReferenceTimeInformationStruct)
    {
        return TimeAccuracy::isLarger(btSpecObject.timeAccuracy);
    }

    BVP_GETTER(bool, isTimeAccuracyUnknown, ReferenceTimeInformationStruct)
    {
        return TimeAccuracy::isUnknown(btSpecObject.timeAccuracy);
    }

    BVP_GETTER(uint16_t, timeAccuracyMs, ReferenceTimeInformationStruct)
    {
        return TimeAccuracy::accuracyMs(btSpecObject.timeAccuracy);
    }

    BVP_GETTER(uint8_t, daysSinceUpdate, ReferenceTimeInformationStruct)
    {
        return btSpecObject.daysSinceUpdate;
    }

    BVP_GETTER(uint8_t, hoursSinceUpdate, ReferenceTimeInformationStruct)
    {
        return btSpecObject.hoursSinceUpdate;
    }

    BVP_GETTER(bool, isSinceUpdateGreater, ReferenceTimeInformationStruct)
    {
        return s_greater == (daysSinceUpdate(btSpecObject) & hoursSinceUpdate(btSpecObject));
    }

    BVP_GETTER(uint32_t, timeSinceUpdateH, ReferenceTimeInformationStruct)
    {
        if (isSinceUpdateGreater(btSpecObject))
        {
            return UINT32_MAX;
        }

        return btSpecObject.daysSinceUpdate * s_hoursPerDay + btSpecObject.hoursSinceUpdate;
    }

private:
    BVP_CTORS(BaseValueSpec, ReferenceTimeInformation, ReferenceTimeInformationStruct)

    static constexpr uint8_t s_greater = 255;
    static constexpr uint8_t s_max = s_greater - 1;
    static constexpr uint8_t s_hoursPerDay = 24;
    static constexpr uint8_t s_maxHours = s_hoursPerDay - 1;

    virtual bool checkSize(size_t size) override
    {
        return size == 4;
    }

    BVP_PARSE(ReferenceTimeInformationStruct)
    {
        bool result{true};

        // GATT_Specification_Supplement_v8.pdf
        // 3.178 Reference Time Information
        result &= TimeSource::parse(parser, btSpecObject.timeSource);
        result &= TimeAccuracy::parse(parser, btSpecObject.timeAccuracy);
        btSpecObject.daysSinceUpdate = parser.parseUInt8();
        btSpecObject.hoursSinceUpdate = parser.parseUInt8();
        if (s_greater != btSpecObject.hoursSinceUpdate &&
            s_maxHours < btSpecObject.hoursSinceUpdate)
        {
            return false;
        }

        if ((s_greater == btSpecObject.daysSinceUpdate &&
             s_greater != btSpecObject.hoursSinceUpdate) ||
            (s_greater == btSpecObject.hoursSinceUpdate &&
             s_greater != btSpecObject.daysSinceUpdate))
        {
            return false;
        }

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "Src: "   << TimeSource(m_btSpecObject.timeSource, configuration());
        oss << ", Drift: " << TimeAccuracy(m_btSpecObject.timeAccuracy, configuration());

        oss << ", Updated: ";
        if (isSinceUpdateGreater())
        {
            oss << ">" << static_cast<int>(s_max) << "days ago";
            return;
        }

        if (m_btSpecObject.daysSinceUpdate)
        {
            oss << static_cast<int>(m_btSpecObject.daysSinceUpdate) << "days ";
        }
        oss << static_cast<int>(m_btSpecObject.hoursSinceUpdate) << "hours ago";
    }
};

}  // namespace bvp
