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
    uint16_t flags{0};
    uint16_t bodyFatPercentage{0};  // org.bluetooth.unit.percentage * 0.1
    DateTimeStruct timeStamp;
    UserIndexStruct userID;
    uint16_t basalMetabolism{0};  // org.bluetooth.unit.energy.joule * 1000
    uint16_t musclePercentage{0};  // org.bluetooth.unit.percentage * 0.1
    uint16_t muscleMass{0};
    uint16_t fatFreeMass{0};
    uint16_t softLeanMass{0};
    uint16_t bodyWaterMass{0};
    uint16_t impedance{0};  // org.bluetooth.unit.electric_resistance.ohm * 0.1
    uint16_t weight{0};
    uint16_t height{0};
};

// BCS_V1.0.0.pdf
// Body Composition Service v1.0.0
// 3.2 BodyCompositionMeasurement
class BodyCompositionMeasurementBase : public BaseValueSpec<BodyCompositionMeasurementStruct>
{
public:
    virtual ~BodyCompositionMeasurementBase() = default;

    BVP_GETTER(bool, isMeasurementUnsuccessful, BodyCompositionMeasurementStruct)
    {
        return 0xFFFF == btSpecObject.bodyFatPercentage;
    }

    BVP_GETTER(MeasurementUnitsEnum, measurementUnits, BodyCompositionMeasurementStruct)
    {
        return MeasurementUnitsEnum(btSpecObject.flags & BCS_FLAG_BCM_MEASUREMENT_UNITS);
    }

    BVP_GETTER(bool, isTimeStampPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_TIME_STAMP_PRESENT) != 0;
    }

    BVP_GETTER(bool, isUserIDPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_USER_ID_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBasalMetabolismPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_BASAL_METABOLISM_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMusclePercentagePresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MUSCLE_PERCENTAGE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMuscleMassPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MUSCLE_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isFatFreeMassPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_FAT_FREE_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isSoftLeanMassPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_SOFT_LEAN_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBodyWaterMassPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_BODY_WATER_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isImpedancePresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_IMPEDANCE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isWeightPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_WEIGHT_PRESENT) != 0;
    }

    BVP_GETTER(bool, isHeightPresent, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_HEIGHT_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMultiplePacketMeasurement, BodyCompositionMeasurementStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MULTIPLE_PACKET_MEASUREMENT) != 0;
    }

    BVP_GETTER(float, bodyFatPercentage, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.bodyFatPercentage / 10.0;
    }

    BVP_GETTER(uint16_t, year, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.timeStamp.year;
    }

    BVP_GETTER(uint8_t, month, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.timeStamp.month;
    }

    BVP_GETTER(uint8_t, day, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.timeStamp.day;
    }

    BVP_GETTER(uint8_t, hour, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.timeStamp.hour;
    }

    BVP_GETTER(uint8_t, minute, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.timeStamp.minute;
    }

    BVP_GETTER(uint8_t, seconds, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.timeStamp.seconds;
    }

    BVP_GETTER(uint8_t, userID, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.userID.userIndex;
    }

    BVP_GETTER(uint16_t, basalMetabolism, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.basalMetabolism;
    }

    BVP_GETTER(float, musclePercentage, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.musclePercentage / 10.0;
    }

    BVP_GETTER_CONF(float, muscleMass, BodyCompositionMeasurementStruct)
    {
        return configuration.massToUnits(btSpecObject.muscleMass);
    }

    BVP_GETTER_CONF(float, fatFreeMass, BodyCompositionMeasurementStruct)
    {
        return configuration.massToUnits(btSpecObject.fatFreeMass);
    }

    BVP_GETTER_CONF(float, softLeanMass, BodyCompositionMeasurementStruct)
    {
        return configuration.massToUnits(btSpecObject.softLeanMass);
    }

    BVP_GETTER_CONF(float, bodyWaterMass, BodyCompositionMeasurementStruct)
    {
        return configuration.massToUnits(btSpecObject.bodyWaterMass);
    }

    BVP_GETTER(float, impedance, BodyCompositionMeasurementStruct)
    {
        return btSpecObject.impedance / 10.0;
    }

    BVP_GETTER_CONF(float, weight, BodyCompositionMeasurementStruct)
    {
        return configuration.massToUnits(btSpecObject.weight);
    }

    BVP_GETTER_CONF(float, height, BodyCompositionMeasurementStruct)
    {
        return configuration.lenghtToUnits(btSpecObject.height);
    }

    virtual Configuration configuration() const override
    {
        m_configuration.measurementUnits = measurementUnits();
        return m_configuration;
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
