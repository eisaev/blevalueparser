#pragma once

#include <cassert>

#include "bodycompositionmeasurementbase.h"


namespace bvp
{

/*
 * Body Composition Service
 * BCS_V1.0.0.pdf
 */

// 3.2 BodyCompositionMeasurement
// Standard
class BodyCompositionMeasurement final : public BodyCompositionMeasurementBase
{
private:
    friend class BLEValueParser;
    explicit BodyCompositionMeasurement(const char *data, size_t size, const Configuration &configuration) :
        BodyCompositionMeasurementBase{configuration}
    {
        create(data, size);
    }

    explicit BodyCompositionMeasurement(const BodyCompositionMeasurementStruct &btSpecObject, const Configuration &configuration) :
        BodyCompositionMeasurementBase{btSpecObject, configuration}
    {}

    virtual bool parse(Parser &parser) override
    {
        // 3.2.1.1 Flags Field
        m_bodyCompositionMeasurement.flags = parser.parseUInt16();

        configuration.measurementUnits = measurementUnits();

        // 3.2.1.2 Body Fat Percentage Field
        // Unit is 1/10 of a percent
        m_bodyCompositionMeasurement.bodyFatPercentage = parser.parseUInt16();
        if (isMeasurementUnsuccessful())
        {
            return true;
        }

        // 3.2.1.3 Time Stamp Field
        if (isTimeStampPresent())
        {
            size_t dateTimeSize = DateTime::expectedSize();
            const char *data = parser.getRawData(dateTimeSize);
            assert(!parser.outOfData());
            auto dateTime = DateTime(data, dateTimeSize, configuration);
            m_bodyCompositionMeasurement.timeStamp = dateTime.getBtSpecObject();
        }

        // 3.2.1.4 User ID Field
        if (isUserIDPresent())
        {
            size_t userIDSize = UserIndex::expectedSize();
            const char *data = parser.getRawData(userIDSize);
            assert(!parser.outOfData());
            auto userIndex = UserIndex(data, userIDSize, configuration);
            m_bodyCompositionMeasurement.userID = userIndex.getBtSpecObject();
        }

        // 3.2.1.5 Basal Metabolism
        // Unit is kilojoules
        if (isBasalMetabolismPresent())
        {
            m_bodyCompositionMeasurement.basalMetabolism = parser.parseUInt16();
        }

        // 3.2.1.6 Muscle Percentage
        // Unit is 1/10 of a percent
        if (isMusclePercentagePresent())
        {
            m_bodyCompositionMeasurement.musclePercentage = parser.parseUInt16();
        }

        // 3.2.1.7 Muscle Mass
        if (isMuscleMassPresent())
        {
            m_bodyCompositionMeasurement.muscleMass = parser.parseUInt16();
        }

        // 3.2.1.8 Fat Free Mass
        if (isFatFreeMassPresent())
        {
            m_bodyCompositionMeasurement.fatFreeMass = parser.parseUInt16();
        }

        // 3.2.1.9 Soft Lean Mass
        if (isSoftLeanMassPresent())
        {
            m_bodyCompositionMeasurement.softLeanMass = parser.parseUInt16();
        }

        // 3.2.1.10 Body Water Mass
        if (isBodyWaterMassPresent())
        {
            m_bodyCompositionMeasurement.bodyWaterMass = parser.parseUInt16();
        }

        // 3.2.1.11 Impedance
        // Unit is 1/10 of an Ohm
        if (isImpedancePresent())
        {
            m_bodyCompositionMeasurement.impedance = parser.parseUInt16();
        }

        // 3.2.1.12 Weight
        if (isWeightPresent())
        {
            m_bodyCompositionMeasurement.weight = parser.parseUInt16();
        }

        // 3.2.1.13 Height
        if (isHeightPresent())
        {
            m_bodyCompositionMeasurement.height = parser.parseUInt16();
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
            ss << ", TimeStamp: " << DateTime(m_bodyCompositionMeasurement.timeStamp, configuration);
        }

        if (isUserIDPresent())
        {
            ss << ", UserID: " << UserIndex(m_bodyCompositionMeasurement.userID, configuration);
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
