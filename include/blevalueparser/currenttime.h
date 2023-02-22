#pragma once

#include <cassert>

#include "basevalue.h"
#include "exacttime256.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.62 Current Time
// Table 3.106: Structure of the Current Time characteristic
// Adjust Reason
constexpr uint8_t CTS_FLAG_MANUAL      = 1 << 0;
constexpr uint8_t CTS_FLAG_EXTERNAL    = 1 << 1;
constexpr uint8_t CTS_FLAG_TZ_CHANGED  = 1 << 2;
constexpr uint8_t CTS_FLAG_DST_CHANGED = 1 << 3;
constexpr uint8_t CTS_FLAG_RESERVED1   = 1 << 4;
constexpr uint8_t CTS_FLAG_RESERVED2   = 1 << 5;
constexpr uint8_t CTS_FLAG_RESERVED3   = 1 << 6;
constexpr uint8_t CTS_FLAG_RESERVED4   = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.62 Current Time
struct CurrentTimeStruct
{
    ExactTime256Struct exactTime256;
    // See CTS_FLAG_*
    uint8_t adjustReason = 0;
};

// CTS_SPEC_V1.1.0.pdf
// Current Time Service v1.1.0
// 3.1 Current Time
class CurrentTime final : public BaseValue
{
public:
    CurrentTimeStruct getBtSpecObject() const
    {
        return m_currentTime;
    }

    uint16_t year() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.year;
    }

    uint8_t month() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.month;
    }

    uint8_t day() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.day;
    }

    uint8_t hour() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.seconds;
    }

    DayOfWeekEnum dayOfWeek() const
    {
        return m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek;
    }

    uint8_t fractionsOfSeconds() const
    {
        return m_currentTime.exactTime256.fractions256;
    }

    uint16_t milliseconds() const
    {
        return m_currentTime.exactTime256.fractions256 * 1000 / 256;
    }

    bool isManuallyAdjusted() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_MANUAL) != 0;
    }

    bool isExternalReference() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_EXTERNAL) != 0;
    }

    bool isTZChanged() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_TZ_CHANGED) != 0;
    }

    bool isDSTChanged() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_DST_CHANGED) != 0;
    }

private:
    friend class BLEValueParser;

    explicit CurrentTime(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit CurrentTime(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit CurrentTime(const CurrentTimeStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_currentTime{btSpecObject}
    {
        m_isValid = true;
    }

    CurrentTimeStruct m_currentTime;

    virtual bool checkSize(size_t size) override
    {
        return size == 10;
    }

    virtual bool parse(Parser &parser) override
    {
        m_currentTime.exactTime256 = ExactTime256(parser, configuration).getBtSpecObject();

        // 3.1.2.1 Manual Time Update
        // 3.1.2.2 External Reference Time Update
        // 3.1.2.3 Change of Time Zone
        // 3.1.2.4 Change of DST Offset
        m_currentTime.adjustReason = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << ExactTime256(m_currentTime.exactTime256, configuration);

        std::stringstream ssAdjustReasons;
        if (isManuallyAdjusted())
        {
            ssAdjustReasons << " ManuallyAdjusted";
        }
        if (isExternalReference())
        {
            ssAdjustReasons << " ExternalReference";
        }
        if (isTZChanged())
        {
            ssAdjustReasons << " TZChanged";
        }
        if (isDSTChanged())
        {
            ssAdjustReasons << " DSTChanged";
        }
        const std::string adjustReason = ssAdjustReasons.str();

        if (!adjustReason.empty())
        {
            ss << " (adjust reason: {" << adjustReason << " })";
        }
    }
};

}  // namespace bvp
