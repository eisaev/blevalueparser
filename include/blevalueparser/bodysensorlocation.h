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
inline std::ostream &operator<<(std::ostream &os, const BodySensorLocationEnum value)
{
    switch (value)
    {
        case BodySensorLocationEnum::Unknown: os << "<Unknown>";    break;
        case BodySensorLocationEnum::Other:   os << "Other";        break;
        case BodySensorLocationEnum::Chest:   os << "Chest";        break;
        case BodySensorLocationEnum::Wrist:   os << "Wrist";        break;
        case BodySensorLocationEnum::Finger:  os << "Finger";       break;
        case BodySensorLocationEnum::Hand:    os << "Hand";         break;
        case BodySensorLocationEnum::EarLobe: os << "Ear Lobe";     break;
        case BodySensorLocationEnum::Foot:    os << "Foot";         break;
    }

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
struct BodySensorLocationStruct
{
    BodySensorLocationEnum bodySensorLocation{BodySensorLocationEnum::Unknown};
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.2 BodySensorLocation
class BodySensorLocation final : public BaseValueSpec<BodySensorLocationStruct>
{
public:
    BodySensorLocationEnum location() const
    {
        return m_btSpecObject.bodySensorLocation;
    }

private:
    BVP_CTORS(BaseValueSpec, BodySensorLocation, BodySensorLocationStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.bodySensorLocation %= BodySensorLocationEnum(parser.parseUInt8());

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.bodySensorLocation;
    }
};

}  // namespace bvp
