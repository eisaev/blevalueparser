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

class DayDateTime final : public BaseValue
{
public:
    friend class ExactTime256;

    DayDateTimeStruct getBtSpecObject() const
    {
        return m_dayDateTime;
    }

    uint16_t year() const
    {
        return m_dayDateTime.dateTime.year;
    }

    uint8_t month() const
    {
        return m_dayDateTime.dateTime.month;
    }

    uint8_t day() const
    {
        return m_dayDateTime.dateTime.day;
    }

    uint8_t hour() const
    {
        return m_dayDateTime.dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_dayDateTime.dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_dayDateTime.dateTime.seconds;
    }

    DayOfWeekEnum dayOfWeek() const
    {
        return m_dayDateTime.dayOfWeek.dayOfWeek;
    }

private:
    friend class BLEValueParser;

    explicit DayDateTime(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit DayDateTime(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit DayDateTime(const DayDateTimeStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_dayDateTime{btSpecObject}
    {
        m_isValid = true;
    }

    DayDateTimeStruct m_dayDateTime;

    virtual bool checkSize(size_t size) override
    {
        return size == 8;
    }

    virtual bool parse(Parser &parser) override
    {
        m_dayDateTime.dateTime = DateTime(parser, configuration).getBtSpecObject();
        m_dayDateTime.dayOfWeek = DayOfWeek(parser, configuration).getBtSpecObject();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << DayOfWeek(m_dayDateTime.dayOfWeek, configuration);
        ss << " " << DateTime(m_dayDateTime.dateTime, configuration);
    }
};

}  // namespace bvp
