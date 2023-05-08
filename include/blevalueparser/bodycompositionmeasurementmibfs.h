#pragma once

#include "bodycompositionmeasurementbase.h"


namespace bvp
{

BVP_STRUCT_INHERITED(BodyCompositionMeasurementMIBFS, BodyCompositionMeasurementBaseStruct) {};

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
class BodyCompositionMeasurementMIBFS final : public BodyCompositionMeasurementBase<BodyCompositionMeasurementMIBFS>
{
public:
    BVP_GETTER(bool, isStabilized, BodyCompositionMeasurementMIBFS)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MIBFS_STABILIZED) != 0;
    }

    BVP_GETTER(bool, isUnknown, BodyCompositionMeasurementMIBFS)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MIBFS_UNKNOWN1) != 0;
    }

    BVP_GETTER(bool, isUnloaded, BodyCompositionMeasurementMIBFS)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MIBFS_UNLOADED) != 0;
    }

private:
    BVP_CTORS(BodyCompositionMeasurementBase<BodyCompositionMeasurementMIBFS>, BodyCompositionMeasurementMIBFS)

    BVP_PARSE(BodyCompositionMeasurementMIBFS)
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

    BVP_TO_STRING(BodyCompositionMeasurementMIBFS)
    {
        std::string str;

        if (isUnloaded(btSpecObject))
        {
            str.append("Unloaded");
        }
        else if (isStabilized(btSpecObject))
        {
            str.append("Stabilized");
        }
        else
        {
            str.append("Unstable");
        }

        if (isTimeStampPresent(btSpecObject))
        {
            str.append(", TimeStamp: ");
            str.append(DateTime::toStringInternal(btSpecObject.timeStamp, configuration));
        }

        if (isImpedancePresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", Impedance: {:g}Ω",
                impedance(btSpecObject)
            );
        }

        if (isWeightPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", Weight: {:g}{}",
                weight(btSpecObject, configuration),
                configuration.massUnits()
            );
        }

        return str;
    }
};

}  // namespace bvp
