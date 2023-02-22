#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

/*
 * Current Time Service
 * CTS_SPEC_V1.1.0.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.70 Date Time
struct DateTimeStruct
{
    uint16_t year = 0;
    uint8_t month = 0;
    uint8_t day = 0;
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t seconds = 0;
};

// 3.1 Date Time
class DateTime final : public BaseValue
{
public:
    friend class CurrentTime;
    friend class BodyCompositionMeasurement;
    friend class BodyCompositionMeasurementMIBFS;

    DateTimeStruct getBtSpecObject() const
    {
        return m_dateTime;
    }

    uint16_t year() const
    {
        return m_dateTime.year;
    }

    uint8_t month() const
    {
        return m_dateTime.month;
    }

    uint8_t day() const
    {
        return m_dateTime.day;
    }

    uint8_t hour() const
    {
        return m_dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_dateTime.seconds;
    }

private:
    friend class BLEValueParser;

    explicit DateTime(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit DateTime(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit DateTime(const DateTimeStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_dateTime{btSpecObject}
    {
        m_isValid = true;
    }

    DateTimeStruct m_dateTime;

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }

    virtual bool parse(Parser &parser) override
    {
        // GATT_Specification_Supplement_v8.pdf
        // 3.70 Date Time
        m_dateTime.year = parser.parseUInt16();
        m_dateTime.month = parser.parseUInt8();
        m_dateTime.day = parser.parseUInt8();
        m_dateTime.hour = parser.parseUInt8();
        m_dateTime.minute = parser.parseUInt8();
        m_dateTime.seconds = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(day()) << ".";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(month()) << ".";
        ss << std::setfill('0') << std::setw(4) << static_cast<int>(year()) << " ";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(hour()) << ":";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(minute()) << ":";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(seconds());
    }
};

}  // namespace bvp
