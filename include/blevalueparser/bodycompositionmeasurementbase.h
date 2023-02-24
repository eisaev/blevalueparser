#pragma once

#include "basevalue.h"
#include "datetime.h"
#include "userindex.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.34.1 Flags field
constexpr uint16_t BCS_FLAG_BCM_MEASUREMENT_UNITS           = 1 <<  0;
constexpr uint16_t BCS_FLAG_BCM_TIME_STAMP_PRESENT          = 1 <<  1;
constexpr uint16_t BCS_FLAG_BCM_USER_ID_PRESENT             = 1 <<  2;
constexpr uint16_t BCS_FLAG_BCM_BASAL_METABOLISM_PRESENT    = 1 <<  3;
constexpr uint16_t BCS_FLAG_BCM_MUSCLE_PERCENTAGE_PRESENT   = 1 <<  4;
constexpr uint16_t BCS_FLAG_BCM_MUSCLE_MASS_PRESENT         = 1 <<  5;
constexpr uint16_t BCS_FLAG_BCM_FAT_FREE_MASS_PRESENT       = 1 <<  6;
constexpr uint16_t BCS_FLAG_BCM_SOFT_LEAN_MASS_PRESENT      = 1 <<  7;
constexpr uint16_t BCS_FLAG_BCM_BODY_WATER_MASS_PRESENT     = 1 <<  8;
constexpr uint16_t BCS_FLAG_BCM_IMPEDANCE_PRESENT           = 1 <<  9;
constexpr uint16_t BCS_FLAG_BCM_WEIGHT_PRESENT              = 1 << 10;
constexpr uint16_t BCS_FLAG_BCM_HEIGHT_PRESENT              = 1 << 11;
constexpr uint16_t BCS_FLAG_BCM_MULTIPLE_PACKET_MEASUREMENT = 1 << 12;
constexpr uint16_t BCS_FLAG_BCM_RESERVED1                   = 1 << 13;
constexpr uint16_t BCS_FLAG_BCM_RESERVED2                   = 1 << 14;
constexpr uint16_t BCS_FLAG_BCM_RESERVED3                   = 1 << 15;

// GATT_Specification_Supplement_v8.pdf
// 3.34 Body Composition Measurement
struct BodyCompositionMeasurementStruct
{
    uint16_t flags = 0;
    uint16_t bodyFatPercentage = 0;
    DateTimeStruct timeStamp;
    UserIndexStruct userID;
    uint16_t basalMetabolism = 0;
    uint16_t musclePercentage = 0;
    uint16_t muscleMass = 0;
    uint16_t fatFreeMass = 0;
    uint16_t softLeanMass = 0;
    uint16_t bodyWaterMass = 0;
    uint16_t impedance = 0;
    uint16_t weight = 0;
    uint16_t height = 0;
};

// BCS_V1.0.0.pdf
// Body Composition Service v1.0.0
// 3.2 BodyCompositionMeasurement
class BodyCompositionMeasurementBase : public BaseValueSpec<BodyCompositionMeasurementStruct>
{
public:
    virtual ~BodyCompositionMeasurementBase() = default;

    bool isMeasurementUnsuccessful() const
    {
        return 0xFFFF == m_btSpecObject.bodyFatPercentage;
    }

    MeasurementUnitsEnum measurementUnits() const
    {
        return MeasurementUnitsEnum(m_btSpecObject.flags & BCS_FLAG_BCM_MEASUREMENT_UNITS);
    }

    bool isTimeStampPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_TIME_STAMP_PRESENT) != 0;
    }

    bool isUserIDPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_USER_ID_PRESENT) != 0;
    }

    bool isBasalMetabolismPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_BASAL_METABOLISM_PRESENT) != 0;
    }

    bool isMusclePercentagePresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_MUSCLE_PERCENTAGE_PRESENT) != 0;
    }

    bool isMuscleMassPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_MUSCLE_MASS_PRESENT) != 0;
    }

    bool isFatFreeMassPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_FAT_FREE_MASS_PRESENT) != 0;
    }

    bool isSoftLeanMassPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_SOFT_LEAN_MASS_PRESENT) != 0;
    }

    bool isBodyWaterMassPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_BODY_WATER_MASS_PRESENT) != 0;
    }

    bool isImpedancePresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_IMPEDANCE_PRESENT) != 0;
    }

    bool isWeightPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_WEIGHT_PRESENT) != 0;
    }

    bool isHeightPresent() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_HEIGHT_PRESENT) != 0;
    }

    bool isMultiplePacketMeasurement() const
    {
        return (m_btSpecObject.flags & BCS_FLAG_BCM_MULTIPLE_PACKET_MEASUREMENT) != 0;
    }

    float bodyFatPercentage() const
    {
        return m_btSpecObject.bodyFatPercentage / 10.0;
    }

    uint16_t year() const
    {
        return m_btSpecObject.timeStamp.year;
    }

    uint8_t month() const
    {
        return m_btSpecObject.timeStamp.month;
    }

    uint8_t day() const
    {
        return m_btSpecObject.timeStamp.day;
    }

    uint8_t hour() const
    {
        return m_btSpecObject.timeStamp.hour;
    }

    uint8_t minute() const
    {
        return m_btSpecObject.timeStamp.minute;
    }

    uint8_t seconds() const
    {
        return m_btSpecObject.timeStamp.seconds;
    }

    uint8_t userID() const
    {
        return m_btSpecObject.userID.userIndex;
    }

    uint16_t basalMetabolism() const
    {
        return m_btSpecObject.basalMetabolism;
    }

    float musclePercentage() const
    {
        return m_btSpecObject.musclePercentage / 10.0;
    }

    float muscleMass() const
    {
        return configuration.massToUnits(m_btSpecObject.muscleMass);
    }

    float fatFreeMass() const
    {
        return configuration.massToUnits(m_btSpecObject.fatFreeMass);
    }

    float softLeanMass() const
    {
        return configuration.massToUnits(m_btSpecObject.softLeanMass);
    }

    float bodyWaterMass() const
    {
        return configuration.massToUnits(m_btSpecObject.bodyWaterMass);
    }

    float impedance() const
    {
        return m_btSpecObject.impedance / 10.0;
    }

    float weight() const
    {
        return configuration.massToUnits(m_btSpecObject.weight);
    }

    float height() const
    {
        return configuration.lenghtToUnits(m_btSpecObject.height);
    }

protected:
    explicit BodyCompositionMeasurementBase(const Configuration &configuration) :
        BaseValueSpec{configuration}
    {}

    explicit BodyCompositionMeasurementBase(const BodyCompositionMeasurementStruct &btSpecObject, const Configuration &configuration) :
        BaseValueSpec{btSpecObject, configuration}
    {}

    virtual bool checkSize(size_t size) override
    {
        return size >= 4 && size <= 30;
    }
};

}  // namespace bvp
