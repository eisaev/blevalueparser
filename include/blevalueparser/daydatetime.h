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

    uint16_t year() const
    {
        return m_btSpecObject.dateTime.year;
    }

    uint8_t month() const
    {
        return m_btSpecObject.dateTime.month;
    }

    uint8_t day() const
    {
        return m_btSpecObject.dateTime.day;
    }

    uint8_t hour() const
    {
        return m_btSpecObject.dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_btSpecObject.dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_btSpecObject.dateTime.seconds;
    }

    DayOfWeekEnum dayOfWeek() const
    {
        return m_btSpecObject.dayOfWeek.dayOfWeek;
    }

private:
    BVP_CTORS(BaseValueSpec, DayDateTime, DayDateTimeStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 8;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.dateTime = DateTime(parser, configuration).getBtSpecObject();
        m_btSpecObject.dayOfWeek = DayOfWeek(parser, configuration).getBtSpecObject();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << DayOfWeek(m_btSpecObject.dayOfWeek, configuration);
        ss << " " << DateTime(m_btSpecObject.dateTime, configuration);
    }
};

}  // namespace bvp
