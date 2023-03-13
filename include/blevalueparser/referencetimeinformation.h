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
    TimeSourceEnum timeSource() const
    {
        return m_btSpecObject.timeSource.timeSource;
    }

    bool isTimeAccuracyLarger() const
    {
        return TimeAccuracy(m_btSpecObject.timeAccuracy, configuration).isLarger();
    }

    bool isTimeAccuracyUnknown() const
    {
        return TimeAccuracy(m_btSpecObject.timeAccuracy, configuration).isUnknown();
    }

    uint16_t timeAccuracyMs() const
    {
        return TimeAccuracy(m_btSpecObject.timeAccuracy, configuration).accuracyMs();
    }

    uint8_t daysSinceUpdate() const
    {
        return m_btSpecObject.daysSinceUpdate;
    }

    uint8_t hoursSinceUpdate() const
    {
        return m_btSpecObject.hoursSinceUpdate;
    }

    bool isSinceUpdateGreater() const
    {
        return s_greater == (daysSinceUpdate() & hoursSinceUpdate());
    }

    uint32_t timeSinceUpdateH() const
    {
        if (isSinceUpdateGreater())
        {
            return UINT32_MAX;
        }

        return m_btSpecObject.daysSinceUpdate * s_hoursPerDay + m_btSpecObject.hoursSinceUpdate;
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

    virtual bool parse(Parser &parser) override
    {
        // GATT_Specification_Supplement_v8.pdf
        // 3.178 Reference Time Information
        m_btSpecObject.timeSource = TimeSource(parser, configuration).getBtSpecObject();
        m_btSpecObject.timeAccuracy = TimeAccuracy(parser, configuration).getBtSpecObject();
        m_btSpecObject.daysSinceUpdate = parser.parseUInt8();
        m_btSpecObject.hoursSinceUpdate = parser.parseUInt8();
        if (s_greater != m_btSpecObject.hoursSinceUpdate &&
            s_maxHours < m_btSpecObject.hoursSinceUpdate)
        {
            return false;
        }

        if ((s_greater == m_btSpecObject.daysSinceUpdate &&
             s_greater != m_btSpecObject.hoursSinceUpdate) ||
            (s_greater == m_btSpecObject.hoursSinceUpdate &&
             s_greater != m_btSpecObject.daysSinceUpdate))
        {
            return false;
        }

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "Src: "   << TimeSource(m_btSpecObject.timeSource, configuration);
        oss << ", Drift: " << TimeAccuracy(m_btSpecObject.timeAccuracy, configuration);

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
