#pragma once

#include <iomanip>

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.70 Date Time
struct DateTimeStruct
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
class DateTime final : public BaseValueSpec<DateTimeStruct>
{
public:
    friend class DayDateTime;
    friend class BodyCompositionMeasurement;
    friend class BodyCompositionMeasurementMIBFS;

    uint16_t year() const
    {
        return m_btSpecObject.year;
    }

    uint8_t month() const
    {
        return m_btSpecObject.month;
    }

    uint8_t day() const
    {
        return m_btSpecObject.day;
    }

    uint8_t hour() const
    {
        return m_btSpecObject.hour;
    }

    uint8_t minute() const
    {
        return m_btSpecObject.minute;
    }

    uint8_t seconds() const
    {
        return m_btSpecObject.seconds;
    }

private:
    BVP_CTORS(BaseValueSpec, DateTime, DateTimeStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.year = parser.parseUInt16();
        m_btSpecObject.month = parser.parseUInt8();
        m_btSpecObject.day = parser.parseUInt8();
        m_btSpecObject.hour = parser.parseUInt8();
        m_btSpecObject.minute = parser.parseUInt8();
        m_btSpecObject.seconds = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<        std::setfill('0') << std::setw(2) << static_cast<int>(day());
        oss << "." << std::setfill('0') << std::setw(2) << static_cast<int>(month());
        oss << "." << std::setfill('0') << std::setw(4) << static_cast<int>(year());
        oss << " " << std::setfill('0') << std::setw(2) << static_cast<int>(hour());
        oss << ":" << std::setfill('0') << std::setw(2) << static_cast<int>(minute());
        oss << ":" << std::setfill('0') << std::setw(2) << static_cast<int>(seconds());
    }
};

}  // namespace bvp
