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
    BVP_GETTER(TimeZoneEnum, timeZone, LocalTimeInformationStruct)
    {
        return btSpecObject.timeZone.timeZone;
    }

    BVP_GETTER(DSTOffsetEnum, dstOffset, LocalTimeInformationStruct)
    {
        return btSpecObject.dstOffset.dstOffset;
    }

private:
    BVP_CTORS(BaseValueSpec, LocalTimeInformation, LocalTimeInformationStruct)

    BVP_PARSE(LocalTimeInformationStruct)
    {
        bool result{true};

        result &= TimeZone::parse(parser, btSpecObject.timeZone);
        result &= DSTOffset::parse(parser, btSpecObject.dstOffset);

        return result;
    }

    BVP_TO_STRING(LocalTimeInformationStruct)
    {
        std::string str;

        str.append("TZ: ");
        str.append(TimeZone::toStringInternal(btSpecObject.timeZone));

        str.append(", DST: ");
        str.append(DSTOffset::toStringInternal(btSpecObject.dstOffset));

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }
};

}  // namespace bvp
