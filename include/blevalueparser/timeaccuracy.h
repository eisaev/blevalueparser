#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.220 Time Accuracy

struct TimeAccuracyStruct
{
    uint8_t accuracy = 0;
};

class TimeAccuracy final : public BaseValue
{
public:
    friend class ReferenceTimeInformation;

    TimeAccuracyStruct getBtSpecObject() const
    {
        return m_timeAccuracy;
    }

    bool isLarger() const
    {
        // A value of 254 means drift is larger than 31.625s.
        return m_timeAccuracy.accuracy == s_timeAccuracyLarge;
    }

    bool isUnknown() const
    {
        // A value of 255 means drift is unknown.
        return m_timeAccuracy.accuracy == s_timeAccuracyUnknown;
    }

    uint16_t accuracyMs() const
    {
        if (m_timeAccuracy.accuracy >= s_timeAccuracyLarge)
        {
            return UINT16_MAX;
        }

        // This field represents accuracy (drift) of time information
        // in steps of 1/8 of a second (125ms) compared to a reference time source.
        return m_timeAccuracy.accuracy * 125;
    }

private:
    friend class BLEValueParser;

    explicit TimeAccuracy(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit TimeAccuracy(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit TimeAccuracy(const TimeAccuracyStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_timeAccuracy{btSpecObject}
    {
        m_isValid = true;
    }

    static constexpr uint8_t s_timeAccuracyLarge   = 254;
    static constexpr uint8_t s_timeAccuracyUnknown = 255;

    TimeAccuracyStruct m_timeAccuracy;

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_timeAccuracy.accuracy = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        if (isUnknown())
        {
            ss << "<Unknown>";
            return;
        }

        if (isLarger())
        {
            ss << ">31625ms";
            return;
        }

        ss << accuracyMs() << "ms";
    }
};

}  // namespace bvp
