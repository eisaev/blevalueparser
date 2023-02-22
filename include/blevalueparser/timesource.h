#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.228 Time Source

enum class TimeSourceEnum : uint8_t
{
    Unknown             = 0,  // 7–255 - Reserved for Future Use
    NetworkTimeProtocol = 1,
    GPS                 = 2,
    RadioTimeSignal     = 3,
    Manual              = 4,
    AtomicClock         = 5,
    CellularNetwork     = 6,
};

struct TimeSourceStruct
{
    TimeSourceEnum timeSource = TimeSourceEnum::Unknown;
};

class TimeSource final : public BaseValue
{
public:
    friend class ReferenceTimeInformation;

    TimeSourceStruct getBtSpecObject() const
    {
        return m_timeSource;
    }

    TimeSourceEnum timeSource() const
    {
        return m_timeSource.timeSource;
    }

private:
    friend class BLEValueParser;

    explicit TimeSource(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit TimeSource(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit TimeSource(const TimeSourceStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_timeSource{btSpecObject}
    {
        m_isValid = true;
    }

    TimeSourceStruct m_timeSource;

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_timeSource.timeSource = TimeSourceEnum(parser.parseUInt8());
        switch (m_timeSource.timeSource)
        {
            case TimeSourceEnum::Unknown:
            case TimeSourceEnum::NetworkTimeProtocol:
            case TimeSourceEnum::GPS:
            case TimeSourceEnum::RadioTimeSignal:
            case TimeSourceEnum::Manual:
            case TimeSourceEnum::AtomicClock:
            case TimeSourceEnum::CellularNetwork:
                break;
            default:
                m_timeSource.timeSource = TimeSourceEnum::Unknown;
                break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_timeSource.timeSource)
        {
            case TimeSourceEnum::Unknown:
                ss << "<Unknown>";
                break;
            case TimeSourceEnum::NetworkTimeProtocol:
                ss << "NetworkTimeProtocol";
                break;
            case TimeSourceEnum::GPS:
                ss << "GPS";
                break;
            case TimeSourceEnum::RadioTimeSignal:
                ss << "RadioTimeSignal";
                break;
            case TimeSourceEnum::Manual:
                ss << "Manual";
                break;
            case TimeSourceEnum::AtomicClock:
                ss << "AtomicClock";
                break;
            case TimeSourceEnum::CellularNetwork:
                ss << "CellularNetwork";
                break;
        }
    }
};

}  // namespace bvp
