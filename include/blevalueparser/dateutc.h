#pragma once

#include "basevalue.h"


namespace
{
static constexpr uint32_t secondsPerDay = 24 * 60 * 60;
}

namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.71 Date UTC

struct DateUTCStruct
{
    uint32_t date{0};
};

class DateUTC final : public BaseValueSpec<DateUTCStruct>
{
public:
    friend class BatteryInformation;
    friend class EstimatedServiceDate;

    BVP_GETTER(uint64_t, days, DateUTCStruct)
    {
        return btSpecObject.date;
    }

    BVP_GETTER(time_t, date, DateUTCStruct)
    {
        return btSpecObject.date * secondsPerDay;
    }

    BVP_GETTER(uint16_t, year, DateUTCStruct)
    {
        time_t dt = date(btSpecObject);
        tm *tm = localtime(&dt);
        return 1900 + tm->tm_year;
    }

    BVP_GETTER(uint8_t, month, DateUTCStruct)
    {
        time_t dt = date(btSpecObject);
        tm *tm = localtime(&dt);
        return 1 + tm->tm_mon;
    }

    BVP_GETTER(uint8_t, day, DateUTCStruct)
    {
        time_t dt = date(btSpecObject);
        tm *tm = localtime(&dt);
        return tm->tm_mday;
    }

private:
    BVP_CTORS(BaseValueSpec, DateUTC, DateUTCStruct)

    BVP_PARSE(DateUTCStruct)
    {
        bool result{true};

        btSpecObject.date = parser.parseUInt24();

        return result;
    }

    BVP_TO_STRING(DateUTCStruct)
    {
        return fmt::format(
            "{:02}.{:02}.{:04} ({} seconds since 1 Jan 1970)",
            day(btSpecObject),
            month(btSpecObject),
            year(btSpecObject),
            date(btSpecObject)
        );
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 3;
    }
};

}  // namespace bvp
