#pragma once

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
BVP_STRUCT(BatteryCriticalStatus)
{
    uint8_t batteryCriticalStatus{0};
};

class BatteryCriticalStatus final : public BaseValueSpec<BatteryCriticalStatus>
{
public:
    BVP_GETTER(bool, isCriticalPowerState, BatteryCriticalStatus)
    {
        return (btSpecObject.batteryCriticalStatus & BCS_FLAG_CRITICAL_POWER_STATE) != 0;
    }

    BVP_GETTER(bool, isImmediateServiceRequired, BatteryCriticalStatus)
    {
        return (btSpecObject.batteryCriticalStatus & BCS_FLAG_IMMEDIATE_SERVICE_REQUIRED) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryCriticalStatus)

    BVP_PARSE(BatteryCriticalStatus)
    {
        bool result{true};

        btSpecObject.batteryCriticalStatus = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(BatteryCriticalStatus)
    {
        (void)configuration;
        std::string str;

        str.append("{");
        if (isCriticalPowerState(btSpecObject))
        {
            str.append(" CriticalPowerState");
        }
        if (isImmediateServiceRequired(btSpecObject))
        {
            str.append(" ImmediateServiceRequired");
        }
        str.append(" }");

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
