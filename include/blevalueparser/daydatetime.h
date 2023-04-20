#pragma once

#include "basevalue.h"
#include "datetime.h"
#include "dayofweek.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.72 Day Date Time

struct DayDateTimeStruct
{
    DateTimeStruct dateTime;
    DayOfWeekStruct dayOfWeek;
};

class DayDateTime final : public BaseValueSpec<DayDateTimeStruct>
{
public:
    friend class ExactTime256;

    BVP_GETTER(uint16_t, year, DayDateTimeStruct)
    {
        return btSpecObject.dateTime.year;
    }

    BVP_GETTER(uint8_t, month, DayDateTimeStruct)
    {
        return btSpecObject.dateTime.month;
    }

    BVP_GETTER(uint8_t, day, DayDateTimeStruct)
    {
        return btSpecObject.dateTime.day;
    }

    BVP_GETTER(uint8_t, hour, DayDateTimeStruct)
    {
        return btSpecObject.dateTime.hour;
    }

    BVP_GETTER(uint8_t, minute, DayDateTimeStruct)
    {
        return btSpecObject.dateTime.minute;
    }

    BVP_GETTER(uint8_t, seconds, DayDateTimeStruct)
    {
        return btSpecObject.dateTime.seconds;
    }

    BVP_GETTER(DayOfWeekEnum, dayOfWeek, DayDateTimeStruct)
    {
        return btSpecObject.dayOfWeek.dayOfWeek;
    }

private:
    BVP_CTORS(BaseValueSpec, DayDateTime, DayDateTimeStruct)

    BVP_PARSE(DayDateTimeStruct)
    {
        bool result{true};

        result &= DateTime::parse(parser, btSpecObject.dateTime);
        result &= DayOfWeek::parse(parser, btSpecObject.dayOfWeek);

        return result;
    }

    BVP_TO_STRING(DayDateTimeStruct)
    {
        std::string str;

        str.append(DayOfWeek::toStringInternal(btSpecObject.dayOfWeek));
        str.append(" ");
        str.append(DateTime::toStringInternal(btSpecObject.dateTime));

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 8;
    }
};

}  // namespace bvp
