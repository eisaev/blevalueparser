#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.76 DST Offset

enum class DSTOffsetEnum
{
    StandardTime                = 0,
    HalfAnHourDaylightTime0_5h  = 2,
    DaylightTime1h              = 4,
    DoubleDaylightTime2h        = 8,
    Unknown                     = 255
};
inline std::string enumToString(const DSTOffsetEnum value)
{
    std::string str;

    switch (value)
    {
        case DSTOffsetEnum::StandardTime:               str = "Standard Time";                      break;
        case DSTOffsetEnum::HalfAnHourDaylightTime0_5h: str = "Half an Hour Daylight Time (+0.5h)"; break;
        case DSTOffsetEnum::DaylightTime1h:             str = "Daylight Time (+1h)";                break;
        case DSTOffsetEnum::DoubleDaylightTime2h:       str = "Double Daylight Time (+2h)";         break;
        case DSTOffsetEnum::Unknown:                    str = "<Unknown>";                          break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const DSTOffsetEnum value)
{
    os << enumToString(value);
    return os;
}
inline DSTOffsetEnum &operator%=(DSTOffsetEnum &lhs, const DSTOffsetEnum &rhs)
{
    lhs = DSTOffsetEnum::Unknown;

    switch (rhs)
    {
        case DSTOffsetEnum::StandardTime:
        case DSTOffsetEnum::HalfAnHourDaylightTime0_5h:
        case DSTOffsetEnum::DaylightTime1h:
        case DSTOffsetEnum::DoubleDaylightTime2h:
        case DSTOffsetEnum::Unknown:
            lhs = rhs;
            break;
    }

    return lhs;
}

BVP_STRUCT(DSTOffset)
{
    DSTOffsetEnum dstOffset{DSTOffsetEnum::Unknown};
};

class DSTOffset final : public BaseValueSpec<DSTOffset>
{
public:
    friend class LocalTimeInformation;

    BVP_GETTER(DSTOffsetEnum, dstOffset, DSTOffset)
    {
        return btSpecObject.dstOffset;
    }

private:
    BVP_CTORS(BaseValueSpec, DSTOffset)

    BVP_PARSE(DSTOffset)
    {
        bool result{true};

        btSpecObject.dstOffset %= DSTOffsetEnum(parser.parseUInt8());

        return result;
    }

    BVP_TO_STRING(DSTOffset)
    {
        (void)configuration;
        return enumToString(btSpecObject.dstOffset);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
