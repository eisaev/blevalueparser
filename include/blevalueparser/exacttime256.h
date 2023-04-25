#pragma once

#include "basevalue.h"
#include "daydatetime.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.90 Exact Time 256

BVP_STRUCT(ExactTime256)
{
    Struct<DayDateTime> dayDateTime;
    uint8_t fractions256{0};
};

class ExactTime256 final : public BaseValueSpec<ExactTime256>
{
public:
    friend class CurrentTime;

    BVP_GETTER(uint16_t, year, ExactTime256)
    {
        return btSpecObject.dayDateTime.dateTime.year;
    }

    BVP_GETTER(uint8_t, month, ExactTime256)
    {
        return btSpecObject.dayDateTime.dateTime.month;
    }

    BVP_GETTER(uint8_t, day, ExactTime256)
    {
        return btSpecObject.dayDateTime.dateTime.day;
    }

    BVP_GETTER(uint8_t, hour, ExactTime256)
    {
        return btSpecObject.dayDateTime.dateTime.hour;
    }

    BVP_GETTER(uint8_t, minute, ExactTime256)
    {
        return btSpecObject.dayDateTime.dateTime.minute;
    }

    BVP_GETTER(uint8_t, seconds, ExactTime256)
    {
        return btSpecObject.dayDateTime.dateTime.seconds;
    }

    BVP_GETTER(DayOfWeekEnum, dayOfWeek, ExactTime256)
    {
        return btSpecObject.dayDateTime.dayOfWeek.dayOfWeek;
    }

    BVP_GETTER(uint8_t, fractionsOfSeconds, ExactTime256)
    {
        return btSpecObject.fractions256;
    }

    BVP_GETTER(uint16_t, milliseconds, ExactTime256)
    {
        return btSpecObject.fractions256 * 1000 / 256;
    }

private:
    BVP_CTORS(BaseValueSpec, ExactTime256)

    BVP_PARSE(ExactTime256)
    {
        bool result{true};

        result &= DayDateTime::parse(parser, btSpecObject.dayDateTime);
        btSpecObject.fractions256 = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(ExactTime256)
    {
        return fmt::format(
            "{}.{:03}",
            DayDateTime::toStringInternal(btSpecObject.dayDateTime, configuration),
            milliseconds(btSpecObject)
        );
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 9;
    }
};

}  // namespace bvp
