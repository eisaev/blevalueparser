#pragma once

#include "bodycompositionmeasurementbase.h"


namespace bvp
{

// BCS_V1.0.0.pdf
// Body Composition Service v1.0.0
// 3.2 BodyCompositionMeasurement
// Standard
class BodyCompositionMeasurement final : public BodyCompositionMeasurementBase
{
private:
    BVP_CTORS(BodyCompositionMeasurementBase, BodyCompositionMeasurement, BodyCompositionMeasurementStruct)

    BVP_PARSE(BodyCompositionMeasurementStruct)
    {
        bool result{true};

        // 3.2.1.1 Flags Field
        btSpecObject.flags = parser.parseUInt16();

        // 3.2.1.2 Body Fat Percentage Field
        // Unit is 1/10 of a percent
        btSpecObject.bodyFatPercentage = parser.parseUInt16();
        if (isMeasurementUnsuccessful(btSpecObject))
        {
            return true;
        }

        // 3.2.1.3 Time Stamp Field
        if (isTimeStampPresent(btSpecObject))
        {
            result &= DateTime::parse(parser, btSpecObject.timeStamp);
        }

        // 3.2.1.4 User ID Field
        if (isUserIDPresent(btSpecObject))
        {
            result &= UserIndex::parse(parser, btSpecObject.userID);
        }

        // 3.2.1.5 Basal Metabolism
        // Unit is kilojoules
        if (isBasalMetabolismPresent(btSpecObject))
        {
            btSpecObject.basalMetabolism = parser.parseUInt16();
        }

        // 3.2.1.6 Muscle Percentage
        // Unit is 1/10 of a percent
        if (isMusclePercentagePresent(btSpecObject))
        {
            btSpecObject.musclePercentage = parser.parseUInt16();
        }

        // 3.2.1.7 Muscle Mass
        if (isMuscleMassPresent(btSpecObject))
        {
            btSpecObject.muscleMass = parser.parseUInt16();
        }

        // 3.2.1.8 Fat Free Mass
        if (isFatFreeMassPresent(btSpecObject))
        {
            btSpecObject.fatFreeMass = parser.parseUInt16();
        }

        // 3.2.1.9 Soft Lean Mass
        if (isSoftLeanMassPresent(btSpecObject))
        {
            btSpecObject.softLeanMass = parser.parseUInt16();
        }

        // 3.2.1.10 Body Water Mass
        if (isBodyWaterMassPresent(btSpecObject))
        {
            btSpecObject.bodyWaterMass = parser.parseUInt16();
        }

        // 3.2.1.11 Impedance
        // Unit is 1/10 of an Ohm
        if (isImpedancePresent(btSpecObject))
        {
            btSpecObject.impedance = parser.parseUInt16();
        }

        // 3.2.1.12 Weight
        if (isWeightPresent(btSpecObject))
        {
            btSpecObject.weight = parser.parseUInt16();
        }

        // 3.2.1.13 Height
        if (isHeightPresent(btSpecObject))
        {
            btSpecObject.height = parser.parseUInt16();
        }

        return result;
    }

    BVP_TO_STRING_CONF(BodyCompositionMeasurementStruct)
    {
        std::string str;

        if (isMeasurementUnsuccessful(btSpecObject))
        {
            return "<MeasurementUnsuccessful>";
        }

        fmt::format_to(
            std::back_inserter(str),
            "BodyFatPercentage: {:g}%",
            bodyFatPercentage(btSpecObject)
        );

        if (isTimeStampPresent(btSpecObject))
        {
            str.append(", TimeStamp: ");
            str.append(DateTime::toStringInternal(btSpecObject.timeStamp));
        }

        if (isUserIDPresent(btSpecObject))
        {
            str.append(", UserID: ");
            str.append(UserIndex::toStringInternal(btSpecObject.userID));
        }

        if (isBasalMetabolismPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", BasalMetabolism: {}kJ",
                basalMetabolism(btSpecObject)
            );
        }

        if (isMusclePercentagePresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", MusclePercentage: {:g}%",
                musclePercentage(btSpecObject)
            );
        }

        if (isMuscleMassPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", MuscleMass: {:g}{}",
                muscleMass(btSpecObject, configuration),
                configuration.massUnits()
            );
        }

        if (isFatFreeMassPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", FatFreeMass: {:g}{}",
                fatFreeMass(btSpecObject, configuration),
                configuration.massUnits()
            );
        }

        if (isSoftLeanMassPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", SoftLeanMass: {:g}{}",
                softLeanMass(btSpecObject, configuration),
                configuration.massUnits()
            );
        }

        if (isBodyWaterMassPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", BodyWaterMass: {:g}{}",
                bodyWaterMass(btSpecObject, configuration),
                configuration.massUnits()
            );
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

        if (isHeightPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", Height: {:g}{}",
                height(btSpecObject, configuration),
                configuration.lenghtUnits()
            );
        }

        return str;
    }
};

}  // namespace bvp
