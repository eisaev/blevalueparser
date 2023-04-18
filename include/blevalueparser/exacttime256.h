#pragma once

#include "basevalue.h"
#include "daydatetime.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.90 Exact Time 256

struct ExactTime256Struct
{
    DayDateTimeStruct dayDateTime;
    uint8_t fractions256{0};
};

class ExactTime256 final : public BaseValueSpec<ExactTime256Struct>
{
public:
    friend class CurrentTime;

    BVP_GETTER(uint16_t, year, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dateTime.year;
    }

    BVP_GETTER(uint8_t, month, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dateTime.month;
    }

    BVP_GETTER(uint8_t, day, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dateTime.day;
    }

    BVP_GETTER(uint8_t, hour, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dateTime.hour;
    }

    BVP_GETTER(uint8_t, minute, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dateTime.minute;
    }

    BVP_GETTER(uint8_t, seconds, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dateTime.seconds;
    }

    BVP_GETTER(DayOfWeekEnum, dayOfWeek, ExactTime256Struct)
    {
        return btSpecObject.dayDateTime.dayOfWeek.dayOfWeek;
    }

    BVP_GETTER(uint8_t, fractionsOfSeconds, ExactTime256Struct)
    {
        return btSpecObject.fractions256;
    }

    BVP_GETTER(uint16_t, milliseconds, ExactTime256Struct)
    {
        return btSpecObject.fractions256 * 1000 / 256;
    }

private:
    BVP_CTORS(BaseValueSpec, ExactTime256, ExactTime256Struct)

    virtual bool checkSize(size_t size) override
    {
        return size == 9;
    }

    BVP_PARSE(ExactTime256Struct)
    {
        bool result{true};

        result &= DayDateTime::parse(parser, btSpecObject.dayDateTime);
        btSpecObject.fractions256 = parser.parseUInt8();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<        DayDateTime(m_btSpecObject.dayDateTime, configuration());
        oss << "." << std::setfill('0') << std::setw(3) << static_cast<int>(milliseconds());
    }
};

}  // namespace bvp
