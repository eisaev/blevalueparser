#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.232 Time Zone

enum class TimeZoneEnum
{
    Unknown = -128,
    Minus48 = -48,
    Minus47 = -47,
    Minus46 = -46,
    Minus45 = -45,
    Minus44 = -44,
    Minus43 = -43,
    Minus42 = -42,
    Minus41 = -41,
    Minus40 = -40,
    Minus39 = -39,
    Minus38 = -38,
    Minus37 = -37,
    Minus36 = -36,
    Minus35 = -35,
    Minus34 = -34,
    Minus33 = -33,
    Minus32 = -32,
    Minus31 = -31,
    Minus30 = -30,
    Minus29 = -29,
    Minus28 = -28,
    Minus27 = -27,
    Minus26 = -26,
    Minus25 = -25,
    Minus24 = -24,
    Minus23 = -23,
    Minus22 = -22,
    Minus21 = -21,
    Minus20 = -20,
    Minus19 = -19,
    Minus18 = -18,
    Minus17 = -17,
    Minus16 = -16,
    Minus15 = -15,
    Minus14 = -14,
    Minus13 = -13,
    Minus12 = -12,
    Minus11 = -11,
    Minus10 = -10,
    Minus9 = -9,
    Minus8 = -8,
    Minus7 = -7,
    Minus6 = -6,
    Minus5 = -5,
    Minus4 = -4,
    Minus3 = -3,
    Minus2 = -2,
    Minus1 = -1,
    Plus0 = 0,
    Plus1 = 1,
    Plus2 = 2,
    Plus3 = 3,
    Plus4 = 4,
    Plus5 = 5,
    Plus6 = 6,
    Plus7 = 7,
    Plus8 = 8,
    Plus9 = 9,
    Plus10 = 10,
    Plus11 = 11,
    Plus12 = 12,
    Plus13 = 13,
    Plus14 = 14,
    Plus15 = 15,
    Plus16 = 16,
    Plus17 = 17,
    Plus18 = 18,
    Plus19 = 19,
    Plus20 = 20,
    Plus21 = 21,
    Plus22 = 22,
    Plus23 = 23,
    Plus24 = 24,
    Plus25 = 25,
    Plus26 = 26,
    Plus27 = 27,
    Plus28 = 28,
    Plus29 = 29,
    Plus30 = 30,
    Plus31 = 31,
    Plus32 = 32,
    Plus33 = 33,
    Plus34 = 34,
    Plus35 = 35,
    Plus36 = 36,
    Plus37 = 37,
    Plus38 = 38,
    Plus39 = 39,
    Plus40 = 40,
    Plus41 = 41,
    Plus42 = 42,
    Plus43 = 43,
    Plus44 = 44,
    Plus45 = 45,
    Plus46 = 46,
    Plus47 = 47,
    Plus48 = 48,
    Plus49 = 49,
    Plus50 = 50,
    Plus51 = 51,
    Plus52 = 52,
    Plus53 = 53,
    Plus54 = 54,
    Plus55 = 55,
    Plus56 = 56
};
inline std::ostream &operator<<(std::ostream &os, const TimeZoneEnum value)
{
    TimeZoneEnum::Unknown == value ? os << "<Unknown>" : os << static_cast<int>(value);
    return os;
}
inline TimeZoneEnum &operator%=(TimeZoneEnum &lhs, const TimeZoneEnum &rhs)
{
    lhs = TimeZoneEnum::Unknown;

    switch (rhs)
    {
        case TimeZoneEnum::Unknown:
        case TimeZoneEnum::Minus48:
        case TimeZoneEnum::Minus47:
        case TimeZoneEnum::Minus46:
        case TimeZoneEnum::Minus45:
        case TimeZoneEnum::Minus44:
        case TimeZoneEnum::Minus43:
        case TimeZoneEnum::Minus42:
        case TimeZoneEnum::Minus41:
        case TimeZoneEnum::Minus40:
        case TimeZoneEnum::Minus39:
        case TimeZoneEnum::Minus38:
        case TimeZoneEnum::Minus37:
        case TimeZoneEnum::Minus36:
        case TimeZoneEnum::Minus35:
        case TimeZoneEnum::Minus34:
        case TimeZoneEnum::Minus33:
        case TimeZoneEnum::Minus32:
        case TimeZoneEnum::Minus31:
        case TimeZoneEnum::Minus30:
        case TimeZoneEnum::Minus29:
        case TimeZoneEnum::Minus28:
        case TimeZoneEnum::Minus27:
        case TimeZoneEnum::Minus26:
        case TimeZoneEnum::Minus25:
        case TimeZoneEnum::Minus24:
        case TimeZoneEnum::Minus23:
        case TimeZoneEnum::Minus22:
        case TimeZoneEnum::Minus21:
        case TimeZoneEnum::Minus20:
        case TimeZoneEnum::Minus19:
        case TimeZoneEnum::Minus18:
        case TimeZoneEnum::Minus17:
        case TimeZoneEnum::Minus16:
        case TimeZoneEnum::Minus15:
        case TimeZoneEnum::Minus14:
        case TimeZoneEnum::Minus13:
        case TimeZoneEnum::Minus12:
        case TimeZoneEnum::Minus11:
        case TimeZoneEnum::Minus10:
        case TimeZoneEnum::Minus9:
        case TimeZoneEnum::Minus8:
        case TimeZoneEnum::Minus7:
        case TimeZoneEnum::Minus6:
        case TimeZoneEnum::Minus5:
        case TimeZoneEnum::Minus4:
        case TimeZoneEnum::Minus3:
        case TimeZoneEnum::Minus2:
        case TimeZoneEnum::Minus1:
        case TimeZoneEnum::Plus0:
        case TimeZoneEnum::Plus1:
        case TimeZoneEnum::Plus2:
        case TimeZoneEnum::Plus3:
        case TimeZoneEnum::Plus4:
        case TimeZoneEnum::Plus5:
        case TimeZoneEnum::Plus6:
        case TimeZoneEnum::Plus7:
        case TimeZoneEnum::Plus8:
        case TimeZoneEnum::Plus9:
        case TimeZoneEnum::Plus10:
        case TimeZoneEnum::Plus11:
        case TimeZoneEnum::Plus12:
        case TimeZoneEnum::Plus13:
        case TimeZoneEnum::Plus14:
        case TimeZoneEnum::Plus15:
        case TimeZoneEnum::Plus16:
        case TimeZoneEnum::Plus17:
        case TimeZoneEnum::Plus18:
        case TimeZoneEnum::Plus19:
        case TimeZoneEnum::Plus20:
        case TimeZoneEnum::Plus21:
        case TimeZoneEnum::Plus22:
        case TimeZoneEnum::Plus23:
        case TimeZoneEnum::Plus24:
        case TimeZoneEnum::Plus25:
        case TimeZoneEnum::Plus26:
        case TimeZoneEnum::Plus27:
        case TimeZoneEnum::Plus28:
        case TimeZoneEnum::Plus29:
        case TimeZoneEnum::Plus30:
        case TimeZoneEnum::Plus31:
        case TimeZoneEnum::Plus32:
        case TimeZoneEnum::Plus33:
        case TimeZoneEnum::Plus34:
        case TimeZoneEnum::Plus35:
        case TimeZoneEnum::Plus36:
        case TimeZoneEnum::Plus37:
        case TimeZoneEnum::Plus38:
        case TimeZoneEnum::Plus39:
        case TimeZoneEnum::Plus40:
        case TimeZoneEnum::Plus41:
        case TimeZoneEnum::Plus42:
        case TimeZoneEnum::Plus43:
        case TimeZoneEnum::Plus44:
        case TimeZoneEnum::Plus45:
        case TimeZoneEnum::Plus46:
        case TimeZoneEnum::Plus47:
        case TimeZoneEnum::Plus48:
        case TimeZoneEnum::Plus49:
        case TimeZoneEnum::Plus50:
        case TimeZoneEnum::Plus51:
        case TimeZoneEnum::Plus52:
        case TimeZoneEnum::Plus53:
        case TimeZoneEnum::Plus54:
        case TimeZoneEnum::Plus55:
        case TimeZoneEnum::Plus56:
            lhs = rhs;
            break;
    }

    return lhs;
}

struct TimeZoneStruct
{
    TimeZoneEnum timeZone{TimeZoneEnum::Unknown};
};

class TimeZone final : public BaseValueSpec<TimeZoneStruct>
{
public:
    friend class LocalTimeInformation;

    TimeZoneEnum timeZone() const
    {
        return m_btSpecObject.timeZone;
    }

private:
    BVP_CTORS(BaseValueSpec, TimeZone, TimeZoneStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.timeZone %= TimeZoneEnum(parser.parseInt8());

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.timeZone;
    }
};

}  // namespace bvp
