#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.71 Date UTC

struct DateUTCStruct
{
    uint32_t date = 0;
};

class DateUTC final : public BaseValueSpec<DateUTCStruct>
{
public:
    uint64_t days() const
    {
        return m_btSpecObject.date;
    }

    time_t date() const
    {
        return m_btSpecObject.date * secondsPerDay;
    }

    uint16_t year() const
    {
        time_t dt = date();
        tm *tm = localtime(&dt);
        return 1900 + tm->tm_year;
    }

    uint8_t month() const
    {
        time_t dt = date();
        tm *tm = localtime(&dt);
        return 1 + tm->tm_mon;
    }

    uint8_t day() const
    {
        time_t dt = date();
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

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.date = parser.parseUInt24();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss        << std::setfill('0') << std::setw(2) << static_cast<int>(day());
        ss << "." << std::setfill('0') << std::setw(2) << static_cast<int>(month());
        ss << "." << std::setfill('0') << std::setw(4) << static_cast<int>(year());
        ss << " (" << date() << " seconds since 1 Jan 1970)";
    }
};

}  // namespace bvp
