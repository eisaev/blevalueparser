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
inline std::ostream &operator<<(std::ostream &os, const HeartRateControlPointEnum value)
{
    switch (value)
    {
        case HeartRateControlPointEnum::Reserved:               os << "<Reserved>";             break;
        case HeartRateControlPointEnum::ResetEnergyExpended:    os << "ResetEnergyExpended";    break;
    }

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
struct HeartRateControlPointStruct
{
    HeartRateControlPointEnum heartRateControlPoint{HeartRateControlPointEnum::Reserved};
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.3 Heart Rate Control Point
class HeartRateControlPoint final : public BaseValueSpec<HeartRateControlPointStruct>
{
public:
    HeartRateControlPointEnum controlPointType() const
    {
        return m_btSpecObject.heartRateControlPoint;
    }

private:
    BVP_CTORS(BaseValueSpec, HeartRateControlPoint, HeartRateControlPointStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.heartRateControlPoint %= HeartRateControlPointEnum(parser.parseUInt8());

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.heartRateControlPoint;
    }
};

}  // namespace bvp
