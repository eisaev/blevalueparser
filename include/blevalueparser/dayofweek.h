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
inline std::ostream &operator<<(std::ostream &os, const DayOfWeekEnum value)
{
    switch (value)
    {
        case DayOfWeekEnum::Unknown:    os << "<Unknown>";  break;
        case DayOfWeekEnum::Monday:     os << "Mon";        break;
        case DayOfWeekEnum::Tuesday:    os << "Tue";        break;
        case DayOfWeekEnum::Wednesday:  os << "Wed";        break;
        case DayOfWeekEnum::Thursday:   os << "Thu";        break;
        case DayOfWeekEnum::Friday:     os << "Fri";        break;
        case DayOfWeekEnum::Saturday:   os << "Sat";        break;
        case DayOfWeekEnum::Sunday:     os << "Sun";        break;
    }

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

struct DayOfWeekStruct
{
    DayOfWeekEnum dayOfWeek = DayOfWeekEnum::Unknown;
};

class DayOfWeek final : public BaseValueSpec<DayOfWeekStruct>
{
public:
    friend class DayDateTime;

    DayOfWeekEnum dayOfWeek() const
    {
        return m_btSpecObject.dayOfWeek;
    }

private:
    BVP_CTORS(BaseValueSpec, DayOfWeek, DayOfWeekStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.dayOfWeek %= DayOfWeekEnum(parser.parseUInt8());

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_btSpecObject.dayOfWeek;
    }
};

}  // namespace bvp
