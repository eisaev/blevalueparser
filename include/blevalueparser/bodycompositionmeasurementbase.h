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
struct BodyCompositionMeasurementBaseStruct
{
    uint16_t flags{0};
    uint16_t bodyFatPercentage{0};  // org.bluetooth.unit.percentage * 0.1
    Struct<DateTime> timeStamp;
    Struct<UserIndex> userID;
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
template<class T>
class BodyCompositionMeasurementBase : public BaseValueSpec<T>
{
public:
    virtual ~BodyCompositionMeasurementBase() = default;

    BVP_GETTER(bool, isMeasurementUnsuccessful, T)
    {
        return 0xFFFF == btSpecObject.bodyFatPercentage;
    }

    BVP_GETTER(MeasurementUnitsEnum, measurementUnits, T)
    {
        return MeasurementUnitsEnum(btSpecObject.flags & BCS_FLAG_BCM_MEASUREMENT_UNITS);
    }

    BVP_GETTER(bool, isTimeStampPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_TIME_STAMP_PRESENT) != 0;
    }

    BVP_GETTER(bool, isUserIDPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_USER_ID_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBasalMetabolismPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_BASAL_METABOLISM_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMusclePercentagePresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MUSCLE_PERCENTAGE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMuscleMassPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MUSCLE_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isFatFreeMassPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_FAT_FREE_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isSoftLeanMassPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_SOFT_LEAN_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBodyWaterMassPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_BODY_WATER_MASS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isImpedancePresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_IMPEDANCE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isWeightPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_WEIGHT_PRESENT) != 0;
    }

    BVP_GETTER(bool, isHeightPresent, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_HEIGHT_PRESENT) != 0;
    }

    BVP_GETTER(bool, isMultiplePacketMeasurement, T)
    {
        return (btSpecObject.flags & BCS_FLAG_BCM_MULTIPLE_PACKET_MEASUREMENT) != 0;
    }

    BVP_GETTER(float, bodyFatPercentage, T)
    {
        return btSpecObject.bodyFatPercentage / 10.0;
    }

    BVP_GETTER(uint16_t, year, T)
    {
        return btSpecObject.timeStamp.year;
    }

    BVP_GETTER(uint8_t, month, T)
    {
        return btSpecObject.timeStamp.month;
    }

    BVP_GETTER(uint8_t, day, T)
    {
        return btSpecObject.timeStamp.day;
    }

    BVP_GETTER(uint8_t, hour, T)
    {
        return btSpecObject.timeStamp.hour;
    }

    BVP_GETTER(uint8_t, minute, T)
    {
        return btSpecObject.timeStamp.minute;
    }

    BVP_GETTER(uint8_t, seconds, T)
    {
        return btSpecObject.timeStamp.seconds;
    }

    BVP_GETTER(uint8_t, userID, T)
    {
        return btSpecObject.userID.userIndex;
    }

    BVP_GETTER(uint16_t, basalMetabolism, T)
    {
        return btSpecObject.basalMetabolism;
    }

    BVP_GETTER(float, musclePercentage, T)
    {
        return btSpecObject.musclePercentage / 10.0;
    }

    BVP_GETTER_CONF(float, muscleMass, T)
    {
        return configuration.massToUnits(btSpecObject.muscleMass);
    }

    BVP_GETTER_CONF(float, fatFreeMass, T)
    {
        return configuration.massToUnits(btSpecObject.fatFreeMass);
    }

    BVP_GETTER_CONF(float, softLeanMass, T)
    {
        return configuration.massToUnits(btSpecObject.softLeanMass);
    }

    BVP_GETTER_CONF(float, bodyWaterMass, T)
    {
        return configuration.massToUnits(btSpecObject.bodyWaterMass);
    }

    BVP_GETTER(float, impedance, T)
    {
        return btSpecObject.impedance / 10.0;
    }

    BVP_GETTER_CONF(float, weight, T)
    {
        return configuration.massToUnits(btSpecObject.weight);
    }

    BVP_GETTER_CONF(float, height, T)
    {
        return configuration.lenghtToUnits(btSpecObject.height);
    }

    virtual Configuration configuration() const override
    {
        const auto& thisRef = static_cast<const T &>(*this);\
        thisRef.m_configuration.measurementUnits = measurementUnits();
        return thisRef.m_configuration;
    }

protected:
    explicit BodyCompositionMeasurementBase(const Configuration &configuration) :
        BaseValueSpec<T>{configuration}
    {}

    explicit BodyCompositionMeasurementBase(const Struct<T> &btSpecObject, const Configuration &configuration) :
        BaseValueSpec<T>{btSpecObject, configuration}
    {}

    virtual bool checkSize(size_t size) override
    {
        return size >= 4 && size <= 30;
    }
};

}  // namespace bvp
