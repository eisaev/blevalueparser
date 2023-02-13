#pragma once

#include <cassert>

#include "basevalue.h"
#include "datetime.h"


namespace bvp
{

/*
 * Current Time Service
 * CTS_SPEC_V1.1.0.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.73 Day of Week (Table 3.130)
enum class DayOfWeekEnum
{
    Unknown = 0,
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
};

// GATT_Specification_Supplement_v8.pdf
// 3.73 Day of Week
struct DayOfWeekStruct
{
    DayOfWeekEnum dayOfWeek = DayOfWeekEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.72 Day Date Time
struct DayDateTimeStruct
{
    DateTimeStruct dateTime;
    DayOfWeekStruct dayOfWeek;
};

// GATT_Specification_Supplement_v8.pdf
// 3.90 Exact Time 256
struct ExactTime256Struct
{
    DayDateTimeStruct dayDateTime;
    uint8_t fractions256 = 0;
};

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

    static size_t expectedSize()
    {
        return 10;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == expectedSize();
    }

    virtual bool parse(Parser &parser) override
    {
        // Exact Time 256
        size_t dateTimeSize = DateTime::expectedSize();
        const char *data = parser.getRawData(dateTimeSize);
        assert(!parser.outOfData());
        auto dateTime = DateTime(data, dateTimeSize, configuration);
        m_currentTime.exactTime256.dayDateTime.dateTime = dateTime.getBtSpecObject();

        m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek = DayOfWeekEnum(parser.parseUInt8());
        switch (m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek)
        {
            case DayOfWeekEnum::Monday ... DayOfWeekEnum::Sunday:
            case DayOfWeekEnum::Unknown:
                break;
            default:
                m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek = DayOfWeekEnum::Unknown;
                break;
        }
        m_currentTime.exactTime256.fractions256 = parser.parseUInt8();

               // 3.1.2.1 Manual Time Update
               // 3.1.2.2 External Reference Time Update
               // 3.1.2.3 Change of Time Zone
               // 3.1.2.4 Change of DST Offset
        m_currentTime.adjustReason = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek)
        {
            case DayOfWeekEnum::Monday:
                ss << "Mon ";
                break;
            case DayOfWeekEnum::Tuesday:
                ss << "Tue ";
                break;
            case DayOfWeekEnum::Wednesday:
                ss << "Wed ";
                break;
            case DayOfWeekEnum::Thursday:
                ss << "Thu ";
                break;
            case DayOfWeekEnum::Friday:
                ss << "Fri ";
                break;
            case DayOfWeekEnum::Saturday:
                ss << "Sat ";
                break;
            case DayOfWeekEnum::Sunday:
                ss << "Sun ";
                break;
            case DayOfWeekEnum::Unknown:
                break;
        }

        ss << DateTime(m_currentTime.exactTime256.dayDateTime.dateTime, configuration);
        ss << "." <<  std::setfill('0') << std::setw(3) << static_cast<int>(milliseconds());

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
