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
    uint8_t fractions256 = 0;
};

class ExactTime256 final : public BaseValueSpec<ExactTime256Struct>
{
public:
    friend class CurrentTime;

    uint16_t year() const
    {
        return m_btSpecObject.dayDateTime.dateTime.year;
    }

    uint8_t month() const
    {
        return m_btSpecObject.dayDateTime.dateTime.month;
    }

    uint8_t day() const
    {
        return m_btSpecObject.dayDateTime.dateTime.day;
    }

    uint8_t hour() const
    {
        return m_btSpecObject.dayDateTime.dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_btSpecObject.dayDateTime.dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_btSpecObject.dayDateTime.dateTime.seconds;
    }

    DayOfWeekEnum dayOfWeek() const
    {
        return m_btSpecObject.dayDateTime.dayOfWeek.dayOfWeek;
    }

    uint8_t fractionsOfSeconds() const
    {
        return m_btSpecObject.fractions256;
    }

    uint16_t milliseconds() const
    {
        return m_btSpecObject.fractions256 * 1000 / 256;
    }

private:
    BVP_CTORS(BaseValueSpec, ExactTime256, ExactTime256Struct)

    virtual bool checkSize(size_t size) override
    {
        return size == 9;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.dayDateTime = DayDateTime(parser, configuration).getBtSpecObject();
        m_btSpecObject.fractions256 = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << DayDateTime(m_btSpecObject.dayDateTime, configuration);
        ss << "." <<  std::setfill('0') << std::setw(3) << static_cast<int>(milliseconds());
    }
};

}  // namespace bvp
