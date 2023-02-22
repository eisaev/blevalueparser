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
        m_btSpecObject.dayOfWeek = DayOfWeekEnum(parser.parseUInt8());
        switch (m_btSpecObject.dayOfWeek)
        {
            case DayOfWeekEnum::Unknown:
            case DayOfWeekEnum::Monday:
            case DayOfWeekEnum::Tuesday:
            case DayOfWeekEnum::Wednesday:
            case DayOfWeekEnum::Thursday:
            case DayOfWeekEnum::Friday:
            case DayOfWeekEnum::Saturday:
            case DayOfWeekEnum::Sunday:
                break;
            default:
                m_btSpecObject.dayOfWeek = DayOfWeekEnum::Unknown;
                break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_btSpecObject.dayOfWeek)
        {
            case DayOfWeekEnum::Unknown:
                ss << "<Unknown>";
                break;
            case DayOfWeekEnum::Monday:
                ss << "Mon";
                break;
            case DayOfWeekEnum::Tuesday:
                ss << "Tue";
                break;
            case DayOfWeekEnum::Wednesday:
                ss << "Wed";
                break;
            case DayOfWeekEnum::Thursday:
                ss << "Thu";
                break;
            case DayOfWeekEnum::Friday:
                ss << "Fri";
                break;
            case DayOfWeekEnum::Saturday:
                ss << "Sat";
                break;
            case DayOfWeekEnum::Sunday:
                ss << "Sun";
                break;
        }
    }
};

}  // namespace bvp