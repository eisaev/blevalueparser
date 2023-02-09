#pragma once

#include "basevalue.h"


namespace bvp
{

/*
 * Current Time Service
 * CTS_SPEC_V1.1.0.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.232 Time Zone (Table 3.345)
enum class TimeZoneEnum
{
    Unknown = -128,
    Minus48 = -48,
    Minus47 = -47,
    Minus46 = -46,
    Minus45 = -45,
    Minus44 = -44,
    Minus43 = -43,
    Minus42 = -42,
    Minus41 = -41,
    Minus40 = -40,
    Minus39 = -39,
    Minus38 = -38,
    Minus37 = -37,
    Minus36 = -36,
    Minus35 = -35,
    Minus34 = -34,
    Minus33 = -33,
    Minus32 = -32,
    Minus31 = -31,
    Minus30 = -30,
    Minus29 = -29,
    Minus28 = -28,
    Minus27 = -27,
    Minus26 = -26,
    Minus25 = -25,
    Minus24 = -24,
    Minus23 = -23,
    Minus22 = -22,
    Minus21 = -21,
    Minus20 = -20,
    Minus19 = -19,
    Minus18 = -18,
    Minus17 = -17,
    Minus16 = -16,
    Minus15 = -15,
    Minus14 = -14,
    Minus13 = -13,
    Minus12 = -12,
    Minus11 = -11,
    Minus10 = -10,
    Minus9 = -9,
    Minus8 = -8,
    Minus7 = -7,
    Minus6 = -6,
    Minus5 = -5,
    Minus4 = -4,
    Minus3 = -3,
    Minus2 = -2,
    Minus1 = -1,
    Plus0 = 0,
    Plus1 = 1,
    Plus2 = 2,
    Plus3 = 3,
    Plus4 = 4,
    Plus5 = 5,
    Plus6 = 6,
    Plus7 = 7,
    Plus8 = 8,
    Plus9 = 9,
    Plus10 = 10,
    Plus11 = 11,
    Plus12 = 12,
    Plus13 = 13,
    Plus14 = 14,
    Plus15 = 15,
    Plus16 = 16,
    Plus17 = 17,
    Plus18 = 18,
    Plus19 = 19,
    Plus20 = 20,
    Plus21 = 21,
    Plus22 = 22,
    Plus23 = 23,
    Plus24 = 24,
    Plus25 = 25,
    Plus26 = 26,
    Plus27 = 27,
    Plus28 = 28,
    Plus29 = 29,
    Plus30 = 30,
    Plus31 = 31,
    Plus32 = 32,
    Plus33 = 33,
    Plus34 = 34,
    Plus35 = 35,
    Plus36 = 36,
    Plus37 = 37,
    Plus38 = 38,
    Plus39 = 39,
    Plus40 = 40,
    Plus41 = 41,
    Plus42 = 42,
    Plus43 = 43,
    Plus44 = 44,
    Plus45 = 45,
    Plus46 = 46,
    Plus47 = 47,
    Plus48 = 48,
    Plus49 = 49,
    Plus50 = 50,
    Plus51 = 51,
    Plus52 = 52,
    Plus53 = 53,
    Plus54 = 54,
    Plus55 = 55,
    Plus56 = 56
};

// GATT_Specification_Supplement_v8.pdf
// 3.232 Time Zone (Table 3.345)
struct TimeZoneStruct
{
    TimeZoneEnum timeZone = TimeZoneEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.76 DST Offset (Table 3.134)
enum class DSTOffsetEnum
{
    StandardTime = 0,
    HalfAnHourDaylightTime0_5h = 2,
    DaylightTime1h = 4,
    DoubleDaylightTime2h = 8,
    Unknown = 255
};

// GATT_Specification_Supplement_v8.pdf
// 3.76 DST Offset
struct DSTOffsetStruct
{
    DSTOffsetEnum dstOffset = DSTOffsetEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.135 Local Time Information
struct LocalTimeInformationStruct
{
    TimeZoneStruct timeZone;
    DSTOffsetStruct dstOffset;
};


// 3.2 Local Time Information
class LocalTimeInformation final : public BaseValue
{
public:
    LocalTimeInformationStruct getBtSpecObject() const
    {
        return m_localTimeInformation;
    }

    TimeZoneEnum timeZone() const
    {
        return m_localTimeInformation.timeZone.timeZone;
    }

    DSTOffsetEnum dstOffset() const
    {
        return m_localTimeInformation.dstOffset.dstOffset;
    }

private:
    friend class BLEValueParser;
    explicit LocalTimeInformation(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit LocalTimeInformation(const LocalTimeInformationStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_localTimeInformation{btSpecObject}
    {
        m_isValid = true;
    }

    LocalTimeInformationStruct m_localTimeInformation;

    static size_t expectedSize()
    {
        return 2;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == expectedSize();
    }

    virtual bool parse(Parser &parser) override
    {
        m_localTimeInformation.timeZone.timeZone = TimeZoneEnum(parser.parseInt8());
        switch (m_localTimeInformation.timeZone.timeZone)
        {
        case TimeZoneEnum::Minus48 ... TimeZoneEnum::Plus56:
        case TimeZoneEnum::Unknown:
            break;
        default:
            m_localTimeInformation.timeZone.timeZone = TimeZoneEnum::Unknown;
            break;
        }

        m_localTimeInformation.dstOffset.dstOffset = DSTOffsetEnum(parser.parseUInt8());
        switch (m_localTimeInformation.dstOffset.dstOffset)
        {
        case DSTOffsetEnum::StandardTime:
        case DSTOffsetEnum::HalfAnHourDaylightTime0_5h:
        case DSTOffsetEnum::DaylightTime1h:
        case DSTOffsetEnum::DoubleDaylightTime2h:
        case DSTOffsetEnum::Unknown:
            break;
        default:
            m_localTimeInformation.dstOffset.dstOffset = DSTOffsetEnum::Unknown;
            break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "TZ: ";
        if (TimeZoneEnum::Unknown == m_localTimeInformation.timeZone.timeZone)
        {
            ss << "<Unknown>";
        }
        else
        {
            ss << static_cast<int>(m_localTimeInformation.timeZone.timeZone);
        }

        ss << ", DST: ";
        switch (m_localTimeInformation.dstOffset.dstOffset)
        {
        case DSTOffsetEnum::StandardTime:
            ss << "Standard Time";
            break;
        case DSTOffsetEnum::HalfAnHourDaylightTime0_5h:
            ss << "Half an Hour Daylight Time (+0.5h)";
            break;
        case DSTOffsetEnum::DaylightTime1h:
            ss << "Daylight Time (+1h)";
            break;
        case DSTOffsetEnum::DoubleDaylightTime2h:
            ss << "Double Daylight Time (+2h)";
            break;
        case DSTOffsetEnum::Unknown:
            ss << "<Unknown>";
            break;
        }
    }
};

}  // namespace bvp
