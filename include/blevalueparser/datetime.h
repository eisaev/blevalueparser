#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.70 Date Time
BVP_STRUCT(DateTime)
{
    uint16_t year{0};
    uint8_t month{0};
    uint8_t day{0};
    uint8_t hour{0};
    uint8_t minute{0};
    uint8_t seconds{0};
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.1 Date Time
class DateTime final : public BaseValueSpec<DateTime>
{
public:
    friend class DayDateTime;
    friend class BodyCompositionMeasurement;
    friend class BodyCompositionMeasurementMIBFS;

    BVP_GETTER(uint16_t, year, DateTime)
    {
        return btSpecObject.year;
    }

    BVP_GETTER(uint8_t, month, DateTime)
    {
        return btSpecObject.month;
    }

    BVP_GETTER(uint8_t, day, DateTime)
    {
        return btSpecObject.day;
    }

    BVP_GETTER(uint8_t, hour, DateTime)
    {
        return btSpecObject.hour;
    }

    BVP_GETTER(uint8_t, minute, DateTime)
    {
        return btSpecObject.minute;
    }

    BVP_GETTER(uint8_t, seconds, DateTime)
    {
        return btSpecObject.seconds;
    }

private:
    BVP_CTORS(BaseValueSpec, DateTime)

    BVP_PARSE(DateTime)
    {
        bool result{true};

        btSpecObject.year = parser.parseUInt16();
        btSpecObject.month = parser.parseUInt8();
        btSpecObject.day = parser.parseUInt8();
        btSpecObject.hour = parser.parseUInt8();
        btSpecObject.minute = parser.parseUInt8();
        btSpecObject.seconds = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(DateTime)
    {
        (void)configuration;
        return fmt::format(
            "{:02}.{:02}.{:04} {:02}:{:02}:{:02}",
            day(btSpecObject),
            month(btSpecObject),
            year(btSpecObject),
            hour(btSpecObject),
            minute(btSpecObject),
            seconds(btSpecObject)
        );
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }
};

}  // namespace bvp
