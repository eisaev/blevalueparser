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

    virtual bool checkSize(size_t size) override
    {
        return size == 8;
    }

    BVP_PARSE(DayDateTimeStruct)
    {
        bool result{true};

        result &= DateTime::parse(parser, btSpecObject.dateTime);
        result &= DayOfWeek::parse(parser, btSpecObject.dayOfWeek);

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<        DayOfWeek(m_btSpecObject.dayOfWeek, configuration());
        oss << " " << DateTime(m_btSpecObject.dateTime, configuration());
    }
};

}  // namespace bvp
