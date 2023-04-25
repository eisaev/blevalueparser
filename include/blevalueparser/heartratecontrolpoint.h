#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.111.1 Heart Rate Control Point field (Table 3.191)
enum class HeartRateControlPointEnum : uint8_t
{
    Reserved            = 0,  // 0, 2–255 - Reserved for Future Use
    ResetEnergyExpended = 1
};
inline std::string enumToString(const HeartRateControlPointEnum value)
{
    std::string str;

    switch (value)
    {
        case HeartRateControlPointEnum::Reserved:               str = "<Reserved>";             break;
        case HeartRateControlPointEnum::ResetEnergyExpended:    str = "ResetEnergyExpended";    break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const HeartRateControlPointEnum value)
{
    os << enumToString(value);
    return os;
}
inline HeartRateControlPointEnum &operator%=(HeartRateControlPointEnum &lhs, const HeartRateControlPointEnum &rhs)
{
    lhs = HeartRateControlPointEnum::Reserved;

    switch (rhs)
    {
        case HeartRateControlPointEnum::Reserved:
        case HeartRateControlPointEnum::ResetEnergyExpended:
            lhs = rhs;
            break;
    }

    return lhs;
}

// GATT_Specification_Supplement_v8.pdf
// 3.111 Heart Rate Control Point
BVP_STRUCT(HeartRateControlPoint)
{
    HeartRateControlPointEnum heartRateControlPoint{HeartRateControlPointEnum::Reserved};
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.3 Heart Rate Control Point
class HeartRateControlPoint final : public BaseValueSpec<HeartRateControlPoint>
{
public:
    BVP_GETTER(HeartRateControlPointEnum, controlPointType, HeartRateControlPoint)
    {
        return btSpecObject.heartRateControlPoint;
    }

private:
    BVP_CTORS(BaseValueSpec, HeartRateControlPoint)

    BVP_PARSE(HeartRateControlPoint)
    {
        bool result{true};

        btSpecObject.heartRateControlPoint %= HeartRateControlPointEnum(parser.parseUInt8());

        return result;
    }

    BVP_TO_STRING(HeartRateControlPoint)
    {
        (void)configuration;
        return enumToString(btSpecObject.heartRateControlPoint);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
