#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.73 Day of Week

enum class DayOfWeekEnum
{
    Unknown     = 0,
    Monday      = 1,
    Tuesday     = 2,
    Wednesday   = 3,
    Thursday    = 4,
    Friday      = 5,
    Saturday    = 6,
    Sunday      = 7
    // 8–255 - Reserved for Future Use
};
inline std::string enumToString(const DayOfWeekEnum value)
{
    std::string str;

    switch (value)
    {
        case DayOfWeekEnum::Unknown:    str = "<Unknown>";  break;
        case DayOfWeekEnum::Monday:     str = "Mon";        break;
        case DayOfWeekEnum::Tuesday:    str = "Tue";        break;
        case DayOfWeekEnum::Wednesday:  str = "Wed";        break;
        case DayOfWeekEnum::Thursday:   str = "Thu";        break;
        case DayOfWeekEnum::Friday:     str = "Fri";        break;
        case DayOfWeekEnum::Saturday:   str = "Sat";        break;
        case DayOfWeekEnum::Sunday:     str = "Sun";        break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const DayOfWeekEnum value)
{
    os << enumToString(value);
    return os;
}
inline DayOfWeekEnum &operator%=(DayOfWeekEnum &lhs, const DayOfWeekEnum &rhs)
{
    lhs = DayOfWeekEnum::Unknown;

    switch (rhs)
    {
        case DayOfWeekEnum::Unknown:
        case DayOfWeekEnum::Monday:
        case DayOfWeekEnum::Tuesday:
        case DayOfWeekEnum::Wednesday:
        case DayOfWeekEnum::Thursday:
        case DayOfWeekEnum::Friday:
        case DayOfWeekEnum::Saturday:
        case DayOfWeekEnum::Sunday:
            lhs = rhs;
            break;
    }

    return lhs;
}

BVP_STRUCT(DayOfWeek)
{
    DayOfWeekEnum dayOfWeek{DayOfWeekEnum::Unknown};
};

class DayOfWeek final : public BaseValueSpec<DayOfWeek>
{
public:
    friend class DayDateTime;

    BVP_GETTER(DayOfWeekEnum, dayOfWeek, DayOfWeek)
    {
        return btSpecObject.dayOfWeek;
    }

private:
    BVP_CTORS(BaseValueSpec, DayOfWeek)

    BVP_PARSE(DayOfWeek)
    {
        bool result{true};

        btSpecObject.dayOfWeek %= DayOfWeekEnum(parser.parseUInt8());

        return result;
    }

    BVP_TO_STRING(DayOfWeek)
    {
        (void)configuration;
        return enumToString(btSpecObject.dayOfWeek);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
