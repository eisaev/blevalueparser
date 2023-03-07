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
inline std::ostream &operator<<(std::ostream &os, const DSTOffsetEnum value)
{
    switch (value)
    {
        case DSTOffsetEnum::StandardTime:               os << "Standard Time";                      break;
        case DSTOffsetEnum::HalfAnHourDaylightTime0_5h: os << "Half an Hour Daylight Time (+0.5h)"; break;
        case DSTOffsetEnum::DaylightTime1h:             os << "Daylight Time (+1h)";                break;
        case DSTOffsetEnum::DoubleDaylightTime2h:       os << "Double Daylight Time (+2h)";         break;
        case DSTOffsetEnum::Unknown:                    os << "<Unknown>";                          break;
    }

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

struct DSTOffsetStruct
{
    DSTOffsetEnum dstOffset{DSTOffsetEnum::Unknown};
};


class DSTOffset final : public BaseValueSpec<DSTOffsetStruct>
{
public:
    friend class LocalTimeInformation;

    DSTOffsetEnum dstOffset() const
    {
        return m_btSpecObject.dstOffset;
    }

private:
    BVP_CTORS(BaseValueSpec, DSTOffset, DSTOffsetStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.dstOffset %= DSTOffsetEnum(parser.parseUInt8());

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.dstOffset;
    }
};

}  // namespace bvp
