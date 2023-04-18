#pragma once

#include <iomanip>

#include "basevalue.h"
#include "batterylevel.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.22.1 Battery Critical Status field
constexpr uint8_t BCS_FLAG_CRITICAL_POWER_STATE         = 1 << 0;
constexpr uint8_t BCS_FLAG_IMMEDIATE_SERVICE_REQUIRED   = 1 << 1;
constexpr uint8_t BCS_FLAG_RESERVED1                    = 1 << 2;
constexpr uint8_t BCS_FLAG_RESERVED2                    = 1 << 3;
constexpr uint8_t BCS_FLAG_RESERVED3                    = 1 << 4;
constexpr uint8_t BCS_FLAG_RESERVED4                    = 1 << 5;
constexpr uint8_t BCS_FLAG_RESERVED5                    = 1 << 6;
constexpr uint8_t BCS_FLAG_RESERVED6                    = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.22 Battery Critical Status
struct BatteryCriticalStatusStruct
{
    uint8_t batteryCriticalStatus{0};
};

class BatteryCriticalStatus final : public BaseValueSpec<BatteryCriticalStatusStruct>
{
public:
    BVP_GETTER(bool, isCriticalPowerState, BatteryCriticalStatusStruct)
    {
        return (btSpecObject.batteryCriticalStatus & BCS_FLAG_CRITICAL_POWER_STATE) != 0;
    }

    BVP_GETTER(bool, isImmediateServiceRequired, BatteryCriticalStatusStruct)
    {
        return (btSpecObject.batteryCriticalStatus & BCS_FLAG_IMMEDIATE_SERVICE_REQUIRED) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryCriticalStatus, BatteryCriticalStatusStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    BVP_PARSE(BatteryCriticalStatusStruct)
    {
        bool result{true};

        btSpecObject.batteryCriticalStatus = parser.parseUInt8();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << "{";
        if (isCriticalPowerState())
        {
            oss << " CriticalPowerState";
        }
        if (isImmediateServiceRequired())
        {
            oss << " ImmediateServiceRequired";
        }
        oss << " }";
    }
};

}  // namespace bvp
