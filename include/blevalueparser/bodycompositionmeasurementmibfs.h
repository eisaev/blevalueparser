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
// Non standard
// Xiaomi Mi Body Composition Scale 2 (XMTZC05HM)
class BodyCompositionMeasurementMIBFS final : public BodyCompositionMeasurementBase
{
public:
    bool isStabilized() const
    {
        return (m_bodyCompositionMeasurement.flags & BCS_FLAG_BCM_MIBFS_STABILIZED) != 0;
    }

    bool isUnknown1() const
    {
        return (m_bodyCompositionMeasurement.flags & BCS_FLAG_BCM_MIBFS_UNKNOWN1) != 0;
    }

    bool isUnloaded() const
    {
        return (m_bodyCompositionMeasurement.flags & BCS_FLAG_BCM_MIBFS_UNLOADED) != 0;
    }

private:
    friend class BLEValueParser;
    explicit BodyCompositionMeasurementMIBFS(const char *data, size_t size, const Configuration &configuration) :
        BodyCompositionMeasurementBase{configuration}
    {
        create(data, size);
    }

    explicit BodyCompositionMeasurementMIBFS(const BodyCompositionMeasurementStruct &btSpecObject, const Configuration &configuration) :
        BodyCompositionMeasurementBase{btSpecObject, configuration}
    {}

    virtual bool parse(Parser &parser) override
    {
        // 3.2.1.1 Flags Field
        m_bodyCompositionMeasurement.flags = parser.parseUInt16();

        configuration.measurementUnits = measurementUnits();

               // 3.2.1.3 Time Stamp Field
        if (isTimeStampPresent())
        {
            size_t dateTimeSize = DateTime::expectedSize();
            const char *data = parser.getRawData(dateTimeSize);
            assert(!parser.outOfData());
            auto dateTime = DateTime(data, dateTimeSize, configuration);
            m_bodyCompositionMeasurement.timeStamp = dateTime.getBtSpecObject();
        }

               // 3.2.1.11 Impedance
               // Unit is 1/10 of an Ohm
               // Always present in data on Xiaomi scales
        m_bodyCompositionMeasurement.impedance = parser.parseUInt16();

               // 3.2.1.12 Weight
        if (isWeightPresent())
        {
            m_bodyCompositionMeasurement.weight = parser.parseUInt16();
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << (isUnloaded() ? "Unloaded" : isStabilized() ? "Stabilized" : "Unstable");

        if (isTimeStampPresent())
        {
            ss << ", TimeStamp: " << DateTime(m_bodyCompositionMeasurement.timeStamp, configuration);
        }

        if (isImpedancePresent())
        {
            ss << ", Impedance: " << impedance() << "Ω";
        }

        if (isWeightPresent())
        {
            ss << ", Weight: " << weight() << configuration.massUnits();
        }
    }
};

}  // namespace bvp
