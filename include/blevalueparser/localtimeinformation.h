#pragma once

#include "basevalue.h"
#include "timezone.h"
#include "dstoffset.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.135 Local Time Information
BVP_STRUCT(LocalTimeInformation)
{
    Struct<TimeZone> timeZone;
    Struct<DSTOffset> dstOffset;
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.2 Local Time Information
class LocalTimeInformation final : public BaseValueSpec<LocalTimeInformation>
{
public:
    BVP_GETTER(TimeZoneEnum, timeZone, LocalTimeInformation)
    {
        return btSpecObject.timeZone.timeZone;
    }

    BVP_GETTER(DSTOffsetEnum, dstOffset, LocalTimeInformation)
    {
        return btSpecObject.dstOffset.dstOffset;
    }

private:
    BVP_CTORS(BaseValueSpec, LocalTimeInformation)

    BVP_PARSE(LocalTimeInformation)
    {
        bool result{true};

        result &= TimeZone::parse(parser, btSpecObject.timeZone);
        result &= DSTOffset::parse(parser, btSpecObject.dstOffset);

        return result;
    }

    BVP_TO_STRING(LocalTimeInformation)
    {
        std::string str;

        str.append("TZ: ");
        str.append(TimeZone::toStringInternal(btSpecObject.timeZone, configuration));

        str.append(", DST: ");
        str.append(DSTOffset::toStringInternal(btSpecObject.dstOffset, configuration));

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }
};

}  // namespace bvp
