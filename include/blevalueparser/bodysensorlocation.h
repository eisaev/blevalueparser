#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.35.1 Body Sensor Location field
enum class BodySensorLocationEnum
{
    Unknown     = 0xFF,  // 0x07–0xFF - Reserved for Future Use
    Other       = 0,
    Chest       = 1,
    Wrist       = 2,
    Finger      = 3,
    Hand        = 4,
    EarLobe     = 5,
    Foot        = 6
};
inline std::string enumToString(const BodySensorLocationEnum value)
{
    std::string str;

    switch (value)
    {
        case BodySensorLocationEnum::Unknown: str = "<Unknown>";    break;
        case BodySensorLocationEnum::Other:   str = "Other";        break;
        case BodySensorLocationEnum::Chest:   str = "Chest";        break;
        case BodySensorLocationEnum::Wrist:   str = "Wrist";        break;
        case BodySensorLocationEnum::Finger:  str = "Finger";       break;
        case BodySensorLocationEnum::Hand:    str = "Hand";         break;
        case BodySensorLocationEnum::EarLobe: str = "Ear Lobe";     break;
        case BodySensorLocationEnum::Foot:    str = "Foot";         break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const BodySensorLocationEnum value)
{
    os << enumToString(value);
    return os;
}
inline BodySensorLocationEnum &operator%=(BodySensorLocationEnum &lhs, const BodySensorLocationEnum &rhs)
{
    lhs = BodySensorLocationEnum::Unknown;

    switch (rhs)
    {
        case BodySensorLocationEnum::Unknown:
        case BodySensorLocationEnum::Other:
        case BodySensorLocationEnum::Chest:
        case BodySensorLocationEnum::Wrist:
        case BodySensorLocationEnum::Finger:
        case BodySensorLocationEnum::Hand:
        case BodySensorLocationEnum::EarLobe:
        case BodySensorLocationEnum::Foot:
            lhs = rhs;
            break;
    }

    return lhs;
}

// GATT_Specification_Supplement_v8.pdf
// 3.35 Body Sensor Location
BVP_STRUCT(BodySensorLocation)
{
    BodySensorLocationEnum bodySensorLocation{BodySensorLocationEnum::Unknown};
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.2 BodySensorLocation
class BodySensorLocation final : public BaseValueSpec<BodySensorLocation>
{
public:
    BVP_GETTER(BodySensorLocationEnum, location, BodySensorLocation)
    {
        return btSpecObject.bodySensorLocation;
    }

private:
    BVP_CTORS(BaseValueSpec, BodySensorLocation)

    BVP_PARSE(BodySensorLocation)
    {
        bool result{true};

        btSpecObject.bodySensorLocation %= BodySensorLocationEnum(parser.parseUInt8());

        return result;
    }

    BVP_TO_STRING(BodySensorLocation)
    {
        (void)configuration;
        return enumToString(btSpecObject.bodySensorLocation);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
