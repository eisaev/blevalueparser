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
inline std::string enumToString(const TimeSourceEnum value)
{
    std::string str;

    switch (value)
    {
        case TimeSourceEnum::Unknown:               str = "<Unknown>";              break;
        case TimeSourceEnum::NetworkTimeProtocol:   str = "NetworkTimeProtocol";    break;
        case TimeSourceEnum::GPS:                   str = "GPS";                    break;
        case TimeSourceEnum::RadioTimeSignal:       str = "RadioTimeSignal";        break;
        case TimeSourceEnum::Manual:                str = "Manual";                 break;
        case TimeSourceEnum::AtomicClock:           str = "AtomicClock";            break;
        case TimeSourceEnum::CellularNetwork:       str = "CellularNetwork";        break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const TimeSourceEnum value)
{
    os << enumToString(value);
    return os;
}
inline TimeSourceEnum &operator%=(TimeSourceEnum &lhs, const TimeSourceEnum &rhs)
{
    lhs = TimeSourceEnum::Unknown;

    switch (rhs)
    {
        case TimeSourceEnum::Unknown:
        case TimeSourceEnum::NetworkTimeProtocol:
        case TimeSourceEnum::GPS:
        case TimeSourceEnum::RadioTimeSignal:
        case TimeSourceEnum::Manual:
        case TimeSourceEnum::AtomicClock:
        case TimeSourceEnum::CellularNetwork:
            lhs = rhs;
            break;
    }

    return lhs;
}

struct TimeSourceStruct
{
    TimeSourceEnum timeSource{TimeSourceEnum::Unknown};
};

class TimeSource final : public BaseValueSpec<TimeSourceStruct>
{
public:
    friend class ReferenceTimeInformation;

    BVP_GETTER(TimeSourceEnum, timeSource, TimeSourceStruct)
    {
        return btSpecObject.timeSource;
    }

private:
    BVP_CTORS(BaseValueSpec, TimeSource, TimeSourceStruct)

    BVP_PARSE(TimeSourceStruct)
    {
        bool result{true};

        btSpecObject.timeSource %= TimeSourceEnum(parser.parseUInt8());

        return result;
    }

    BVP_TO_STRING(TimeSourceStruct)
    {
        return enumToString(btSpecObject.timeSource);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
