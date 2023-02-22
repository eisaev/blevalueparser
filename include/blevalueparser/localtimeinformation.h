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
class LocalTimeInformation final : public BaseValueSpec<LocalTimeInformationStruct>
{
public:
    TimeZoneEnum timeZone() const
    {
        return m_btSpecObject.timeZone.timeZone;
    }

    DSTOffsetEnum dstOffset() const
    {
        return m_btSpecObject.dstOffset.dstOffset;
    }

private:
    BVP_CTORS(BaseValueSpec, LocalTimeInformation, LocalTimeInformationStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.timeZone = TimeZone(parser, configuration).getBtSpecObject();
        m_btSpecObject.dstOffset = DSTOffset(parser, configuration).getBtSpecObject();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "TZ: " << TimeZone(m_btSpecObject.timeZone, configuration);
        ss << ", DST: " << DSTOffset(m_btSpecObject.dstOffset, configuration);
    }
};

}  // namespace bvp
