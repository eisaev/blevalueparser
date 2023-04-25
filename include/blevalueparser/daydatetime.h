#pragma once

#include "basevalue.h"
#include "datetime.h"
#include "dayofweek.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.72 Day Date Time

BVP_STRUCT(DayDateTime)
{
    Struct<DateTime> dateTime;
    Struct<DayOfWeek> dayOfWeek;
};

class DayDateTime final : public BaseValueSpec<DayDateTime>
{
public:
    friend class ExactTime256;

    BVP_GETTER(uint16_t, year, DayDateTime)
    {
        return btSpecObject.dateTime.year;
    }

    BVP_GETTER(uint8_t, month, DayDateTime)
    {
        return btSpecObject.dateTime.month;
    }

    BVP_GETTER(uint8_t, day, DayDateTime)
    {
        return btSpecObject.dateTime.day;
    }

    BVP_GETTER(uint8_t, hour, DayDateTime)
    {
        return btSpecObject.dateTime.hour;
    }

    BVP_GETTER(uint8_t, minute, DayDateTime)
    {
        return btSpecObject.dateTime.minute;
    }

    BVP_GETTER(uint8_t, seconds, DayDateTime)
    {
        return btSpecObject.dateTime.seconds;
    }

    BVP_GETTER(DayOfWeekEnum, dayOfWeek, DayDateTime)
    {
        return btSpecObject.dayOfWeek.dayOfWeek;
    }

private:
    BVP_CTORS(BaseValueSpec, DayDateTime)

    BVP_PARSE(DayDateTime)
    {
        bool result{true};

        result &= DateTime::parse(parser, btSpecObject.dateTime);
        result &= DayOfWeek::parse(parser, btSpecObject.dayOfWeek);

        return result;
    }

    BVP_TO_STRING(DayDateTime)
    {
        std::string str;

        str.append(DayOfWeek::toStringInternal(btSpecObject.dayOfWeek, configuration));
        str.append(" ");
        str.append(DateTime::toStringInternal(btSpecObject.dateTime, configuration));

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 8;
    }
};

}  // namespace bvp
