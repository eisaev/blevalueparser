#pragma once

#include <iomanip>

#include "basevalue.h"


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

    static constexpr uint32_t secondsPerDay = 24 * 60 * 60;

    virtual bool checkSize(size_t size) override
    {
        return size == 3;
    }

    BVP_PARSE(DateUTCStruct)
    {
        bool result{true};

        btSpecObject.date = parser.parseUInt24();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<        std::setfill('0') << std::setw(2) << static_cast<int>(day());
        oss << "." << std::setfill('0') << std::setw(2) << static_cast<int>(month());
        oss << "." << std::setfill('0') << std::setw(4) << static_cast<int>(year());
        oss << " (" << date() << " seconds since 1 Jan 1970)";
    }
};

}  // namespace bvp
