#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.76 DST Offset

enum class DSTOffsetEnum
{
    StandardTime                = 0,
    HalfAnHourDaylightTime0_5h  = 2,
    DaylightTime1h              = 4,
    DoubleDaylightTime2h        = 8,
    Unknown                     = 255
};

struct DSTOffsetStruct
{
    DSTOffsetEnum dstOffset = DSTOffsetEnum::Unknown;
};


class DSTOffset final : public BaseValue
{
public:
    friend class LocalTimeInformation;

    DSTOffsetStruct getBtSpecObject() const
    {
        return m_dstOffset;
    }

    DSTOffsetEnum dstOffset() const
    {
        return m_dstOffset.dstOffset;
    }

private:
    friend class BLEValueParser;

    explicit DSTOffset(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit DSTOffset(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit DSTOffset(const DSTOffsetStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_dstOffset{btSpecObject}
    {
        m_isValid = true;
    }

    DSTOffsetStruct m_dstOffset;

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_dstOffset.dstOffset = DSTOffsetEnum(parser.parseUInt8());
        switch (m_dstOffset.dstOffset)
        {
            case DSTOffsetEnum::StandardTime:
            case DSTOffsetEnum::HalfAnHourDaylightTime0_5h:
            case DSTOffsetEnum::DaylightTime1h:
            case DSTOffsetEnum::DoubleDaylightTime2h:
            case DSTOffsetEnum::Unknown:
                break;
            default:
                m_dstOffset.dstOffset = DSTOffsetEnum::Unknown;
                break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_dstOffset.dstOffset)
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
