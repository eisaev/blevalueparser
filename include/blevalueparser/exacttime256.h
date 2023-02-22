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

class ExactTime256 final : public BaseValue
{
public:
    friend class CurrentTime;

    ExactTime256Struct getBtSpecObject() const
    {
        return m_exactTime256;
    }

    uint16_t year() const
    {
        return m_exactTime256.dayDateTime.dateTime.year;
    }

    uint8_t month() const
    {
        return m_exactTime256.dayDateTime.dateTime.month;
    }

    uint8_t day() const
    {
        return m_exactTime256.dayDateTime.dateTime.day;
    }

    uint8_t hour() const
    {
        return m_exactTime256.dayDateTime.dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_exactTime256.dayDateTime.dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_exactTime256.dayDateTime.dateTime.seconds;
    }

    DayOfWeekEnum dayOfWeek() const
    {
        return m_exactTime256.dayDateTime.dayOfWeek.dayOfWeek;
    }

    uint8_t fractionsOfSeconds() const
    {
        return m_exactTime256.fractions256;
    }

    uint16_t milliseconds() const
    {
        return m_exactTime256.fractions256 * 1000 / 256;
    }

private:
    friend class BLEValueParser;

    explicit ExactTime256(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit ExactTime256(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit ExactTime256(const ExactTime256Struct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_exactTime256{btSpecObject}
    {
        m_isValid = true;
    }

    ExactTime256Struct m_exactTime256;

    virtual bool checkSize(size_t size) override
    {
        return size == 9;
    }

    virtual bool parse(Parser &parser) override
    {
        m_exactTime256.dayDateTime = DayDateTime(parser, configuration).getBtSpecObject();
        m_exactTime256.fractions256 = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << DayDateTime(m_exactTime256.dayDateTime, configuration);
        ss << "." <<  std::setfill('0') << std::setw(3) << static_cast<int>(milliseconds());
    }
};

}  // namespace bvp
