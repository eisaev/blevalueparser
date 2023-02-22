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
    uint8_t daysSinceUpdate = 0;
    uint8_t hoursSinceUpdate = 0;
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.3 Reference Time Information
class ReferenceTimeInformation final : public BaseValue
{
public:
    ReferenceTimeInformationStruct getBtSpecObject() const
    {
        return m_referenceTimeInformation;
    }

    TimeSourceEnum timeSource() const
    {
        return m_referenceTimeInformation.timeSource.timeSource;
    }

    bool isTimeAccuracyLarger() const
    {
        return TimeAccuracy(m_referenceTimeInformation.timeAccuracy, configuration).isLarger();
    }

    bool isTimeAccuracyUnknown() const
    {
        return TimeAccuracy(m_referenceTimeInformation.timeAccuracy, configuration).isUnknown();
    }

    uint16_t timeAccuracyMs() const
    {
        return TimeAccuracy(m_referenceTimeInformation.timeAccuracy, configuration).accuracyMs();
    }

    uint8_t daysSinceUpdate() const
    {
        return m_referenceTimeInformation.daysSinceUpdate;
    }

    uint8_t hoursSinceUpdate() const
    {
        return m_referenceTimeInformation.hoursSinceUpdate;
    }

    bool isSinceUpdateGreater() const
    {
        return 255 == (daysSinceUpdate() & hoursSinceUpdate());
    }

    uint32_t timeSinceUpdateH() const
    {
        if (isSinceUpdateGreater())
        {
            return UINT32_MAX;
        }

        return m_referenceTimeInformation.daysSinceUpdate * 24 + m_referenceTimeInformation.hoursSinceUpdate;
    }

private:
    friend class BLEValueParser;

    explicit ReferenceTimeInformation(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit ReferenceTimeInformation(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit ReferenceTimeInformation(const ReferenceTimeInformationStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_referenceTimeInformation{btSpecObject}
    {
        m_isValid = true;
    }

    ReferenceTimeInformationStruct m_referenceTimeInformation;

    virtual bool checkSize(size_t size) override
    {
        return size == 4;
    }

    virtual bool parse(Parser &parser) override
    {
        // GATT_Specification_Supplement_v8.pdf
        // 3.178 Reference Time Information
        m_referenceTimeInformation.timeSource = TimeSource(parser, configuration).getBtSpecObject();
        m_referenceTimeInformation.timeAccuracy = TimeAccuracy(parser, configuration).getBtSpecObject();
        m_referenceTimeInformation.daysSinceUpdate = parser.parseUInt8();
        m_referenceTimeInformation.hoursSinceUpdate = parser.parseUInt8();
        if (255 != m_referenceTimeInformation.hoursSinceUpdate &&
            23 < m_referenceTimeInformation.hoursSinceUpdate)
        {
            return false;
        }

        if ((255 == m_referenceTimeInformation.daysSinceUpdate &&
             255 != m_referenceTimeInformation.hoursSinceUpdate) ||
            (255 == m_referenceTimeInformation.hoursSinceUpdate &&
             255 != m_referenceTimeInformation.daysSinceUpdate))
        {
            return false;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "Src: " << TimeSource(m_referenceTimeInformation.timeSource, configuration);
        ss << ", Drift: " << TimeAccuracy(m_referenceTimeInformation.timeAccuracy, configuration);

        ss << ", Updated: ";
        if (isSinceUpdateGreater())
        {
            ss << ">254days ago";
            return;
        }

        if (m_referenceTimeInformation.daysSinceUpdate)
        {
            ss << static_cast<int>(m_referenceTimeInformation.daysSinceUpdate) << "days ";
        }
        ss << static_cast<int>(m_referenceTimeInformation.hoursSinceUpdate) << "hours ago";
    }
};

}  // namespace bvp
