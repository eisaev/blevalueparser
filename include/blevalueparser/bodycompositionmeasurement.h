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

    virtual bool parse(Parser &parser) override
    {
        // 3.2.1.1 Flags Field
        m_btSpecObject.flags = parser.parseUInt16();

        configuration.measurementUnits = measurementUnits();

        // 3.2.1.2 Body Fat Percentage Field
        // Unit is 1/10 of a percent
        m_btSpecObject.bodyFatPercentage = parser.parseUInt16();
        if (isMeasurementUnsuccessful())
        {
            return true;
        }

        // 3.2.1.3 Time Stamp Field
        if (isTimeStampPresent())
        {
            m_btSpecObject.timeStamp = DateTime(parser, configuration).getBtSpecObject();
        }

        // 3.2.1.4 User ID Field
        if (isUserIDPresent())
        {
            m_btSpecObject.userID = UserIndex(parser, configuration).getBtSpecObject();
        }

        // 3.2.1.5 Basal Metabolism
        // Unit is kilojoules
        if (isBasalMetabolismPresent())
        {
            m_btSpecObject.basalMetabolism = parser.parseUInt16();
        }

        // 3.2.1.6 Muscle Percentage
        // Unit is 1/10 of a percent
        if (isMusclePercentagePresent())
        {
            m_btSpecObject.musclePercentage = parser.parseUInt16();
        }

        // 3.2.1.7 Muscle Mass
        if (isMuscleMassPresent())
        {
            m_btSpecObject.muscleMass = parser.parseUInt16();
        }

        // 3.2.1.8 Fat Free Mass
        if (isFatFreeMassPresent())
        {
            m_btSpecObject.fatFreeMass = parser.parseUInt16();
        }

        // 3.2.1.9 Soft Lean Mass
        if (isSoftLeanMassPresent())
        {
            m_btSpecObject.softLeanMass = parser.parseUInt16();
        }

        // 3.2.1.10 Body Water Mass
        if (isBodyWaterMassPresent())
        {
            m_btSpecObject.bodyWaterMass = parser.parseUInt16();
        }

        // 3.2.1.11 Impedance
        // Unit is 1/10 of an Ohm
        if (isImpedancePresent())
        {
            m_btSpecObject.impedance = parser.parseUInt16();
        }

        // 3.2.1.12 Weight
        if (isWeightPresent())
        {
            m_btSpecObject.weight = parser.parseUInt16();
        }

        // 3.2.1.13 Height
        if (isHeightPresent())
        {
            m_btSpecObject.height = parser.parseUInt16();
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        if (isMeasurementUnsuccessful())
        {
            ss << "<MeasurementUnsuccessful>";
            return;
        }

        ss << "BodyFatPercentage: " << bodyFatPercentage() << "%";

        if (isTimeStampPresent())
        {
            ss << ", TimeStamp: " << DateTime(m_btSpecObject.timeStamp, configuration);
        }

        if (isUserIDPresent())
        {
            ss << ", UserID: " << UserIndex(m_btSpecObject.userID, configuration);
        }

        if (isBasalMetabolismPresent())
        {
            ss << ", BasalMetabolism: " << basalMetabolism() << "kJ";
        }

        if (isMusclePercentagePresent())
        {
            ss << ", MusclePercentage: " << musclePercentage() << "%";
        }

        if (isMuscleMassPresent())
        {
            ss << ", MuscleMass: " << muscleMass() << configuration.massUnits();
        }

        if (isFatFreeMassPresent())
        {
            ss << ", FatFreeMass: " << fatFreeMass() << configuration.massUnits();
        }

        if (isSoftLeanMassPresent())
        {
            ss << ", SoftLeanMass: " << softLeanMass() << configuration.massUnits();
        }

        if (isBodyWaterMassPresent())
        {
            ss << ", BodyWaterMass: " << bodyWaterMass() << configuration.massUnits();
        }

        if (isImpedancePresent())
        {
            ss << ", Impedance: " << impedance() << "Ω";
        }

        if (isWeightPresent())
        {
            ss << ", Weight: " << weight() << configuration.massUnits();
        }

        if (isHeightPresent())
        {
            ss << ", Height: " << height() << configuration.lenghtUnits();
        }
    }
};

}  // namespace bvp
