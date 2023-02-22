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

class TimeSource final : public BaseValueSpec<TimeSourceStruct>
{
public:
    friend class ReferenceTimeInformation;

    TimeSourceEnum timeSource() const
    {
        return m_btSpecObject.timeSource;
    }

private:
    BVP_CTORS(BaseValueSpec, TimeSource, TimeSourceStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.timeSource = TimeSourceEnum(parser.parseUInt8());
        switch (m_btSpecObject.timeSource)
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
                m_btSpecObject.timeSource = TimeSourceEnum::Unknown;
                break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_btSpecObject.timeSource)
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
