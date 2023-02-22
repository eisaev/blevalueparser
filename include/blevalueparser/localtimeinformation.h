#pragma once

#include "basevalue.h"
#include "timezone.h"
#include "dstoffset.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.135 Local Time Information
struct LocalTimeInformationStruct
{
    TimeZoneStruct timeZone;
    DSTOffsetStruct dstOffset;
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.2 Local Time Information
class LocalTimeInformation final : public BaseValue
{
public:
    LocalTimeInformationStruct getBtSpecObject() const
    {
        return m_localTimeInformation;
    }

    TimeZoneEnum timeZone() const
    {
        return m_localTimeInformation.timeZone.timeZone;
    }

    DSTOffsetEnum dstOffset() const
    {
        return m_localTimeInformation.dstOffset.dstOffset;
    }

private:
    friend class BLEValueParser;

    explicit LocalTimeInformation(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit LocalTimeInformation(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit LocalTimeInformation(const LocalTimeInformationStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_localTimeInformation{btSpecObject}
    {
        m_isValid = true;
    }

    LocalTimeInformationStruct m_localTimeInformation;

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    virtual bool parse(Parser &parser) override
    {
        m_localTimeInformation.timeZone = TimeZone(parser, configuration).getBtSpecObject();
        m_localTimeInformation.dstOffset = DSTOffset(parser, configuration).getBtSpecObject();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "TZ: " << TimeZone(m_localTimeInformation.timeZone, configuration);
        ss << ", DST: " << DSTOffset(m_localTimeInformation.dstOffset, configuration);
    }
};

}  // namespace bvp
