#pragma once

#include "bodycompositionmeasurementbase.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.34.1 Flags field
// Non standard - Xiaomi Mi Body Composition Scale 2 (XMTZC05HM)
constexpr uint16_t BCS_FLAG_BCM_MIBFS_STABILIZED = BCS_FLAG_BCM_RESERVED1;
constexpr uint16_t BCS_FLAG_BCM_MIBFS_UNKNOWN1   = BCS_FLAG_BCM_RESERVED2;
constexpr uint16_t BCS_FLAG_BCM_MIBFS_UNLOADED   = BCS_FLAG_BCM_RESERVED3;

// BCS_V1.0.0.pdf
// Body Composition Service v1.0.0
// 3.2 BodyCompositionMeasurement
// Non standard - Xiaomi Mi Body Composition Scale 2 (XMTZC05HM)
class BodyCompositionMeasurementMIBFS final : public BodyCompositionMeasurementBase
{
public:
    BVP_GETTER(bool, isStabilized, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MIBFS_STABILIZED) != 0;
    }

    BVP_GETTER(bool, isUnknown, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MIBFS_UNKNOWN1) != 0;
    }

    BVP_GETTER(bool, isUnloaded, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MIBFS_UNLOADED) != 0;
    }

private:
    BVP_CTORS(BodyCompositionMeasurementBase, BodyCompositionMeasurementMIBFS, BodyCompositionMeasurementStruct)

    BVP_PARSE(BodyCompositionMeasurementStruct)
    {
        bool result{true};

        // 3.2.1.1 Flags Field
        btSpecObject.flags = parser.parseUInt16();

        // 3.2.1.3 Time Stamp Field
        if (isTimeStampPresent(btSpecObject))
        {
            result &= DateTime::parse(parser, btSpecObject.timeStamp);
        }

        // 3.2.1.11 Impedance
        // Unit is 1/10 of an Ohm
        // Always present in data on Xiaomi scales
        btSpecObject.impedance = parser.parseUInt16();

        // 3.2.1.12 Weight
        if (isWeightPresent(btSpecObject))
        {
            btSpecObject.weight = parser.parseUInt16();
        }

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << (isUnloaded() ? "Unloaded" : isStabilized() ? "Stabilized" : "Unstable");

        if (isTimeStampPresent())
        {
            oss << ", TimeStamp: " << DateTime(m_btSpecObject.timeStamp, configuration());
        }

        if (isImpedancePresent())
        {
            oss << ", Impedance: " << impedance() << "Ω";
        }

        if (isWeightPresent())
        {
            oss << ", Weight: " << weight() << configuration().massUnits();
        }
    }
};

}  // namespace bvp
