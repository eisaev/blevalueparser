#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.33.1 Body Composition Feature field
constexpr uint8_t BCS_FLAG_BCF_WEIGHT_RESOLUTION_SHIFT = 11;
constexpr uint8_t BCS_FLAG_BCF_HEIGHT_RESOLUTION_SHIFT = 15;

constexpr uint32_t BCS_FLAG_BCF_TIME_STAMP_SUPPORTED        = 1 <<  0;
constexpr uint32_t BCS_FLAG_BCF_MULTIPLE_USERS_SUPPORTED    = 1 <<  1;
constexpr uint32_t BCS_FLAG_BCF_BASAL_METABOLISM_SUPPORTED  = 1 <<  2;
constexpr uint32_t BCS_FLAG_BCF_MUSCLE_PERCENTAGE_SUPPORTED = 1 <<  3;
constexpr uint32_t BCS_FLAG_BCF_MUSCLE_MASS_SUPPORTED       = 1 <<  4;
constexpr uint32_t BCS_FLAG_BCF_FAT_FREE_MASS_SUPPORTED     = 1 <<  5;
constexpr uint32_t BCS_FLAG_BCF_SOFT_LEAN_MASS_SUPPORTED    = 1 <<  6;
constexpr uint32_t BCS_FLAG_BCF_BODY_WATER_MASS_SUPPORTED   = 1 <<  7;
constexpr uint32_t BCS_FLAG_BCF_IMPEDANCE_SUPPORTED         = 1 <<  8;
constexpr uint32_t BCS_FLAG_BCF_WEIGHT_SUPPORTED            = 1 <<  9;
constexpr uint32_t BCS_FLAG_BCF_HEIGHT_SUPPORTED            = 1 << 10;
constexpr uint32_t BCS_FLAG_BCF_WEIGHT_RESOLUTION0          = 1 << BCS_FLAG_BCF_WEIGHT_RESOLUTION_SHIFT;
constexpr uint32_t BCS_FLAG_BCF_WEIGHT_RESOLUTION1          = 1 << 12;
constexpr uint32_t BCS_FLAG_BCF_WEIGHT_RESOLUTION2          = 1 << 13;
constexpr uint32_t BCS_FLAG_BCF_WEIGHT_RESOLUTION3          = 1 << 14;
constexpr uint32_t BCS_FLAG_BCF_HEIGHT_RESOLUTION0          = 1 << BCS_FLAG_BCF_HEIGHT_RESOLUTION_SHIFT;
constexpr uint32_t BCS_FLAG_BCF_HEIGHT_RESOLUTION1          = 1 << 16;
constexpr uint32_t BCS_FLAG_BCF_HEIGHT_RESOLUTION2          = 1 << 17;
constexpr uint32_t BCS_FLAG_BCF_RESERVER1                   = 1 << 18;
constexpr uint32_t BCS_FLAG_BCF_RESERVER2                   = 1 << 19;
constexpr uint32_t BCS_FLAG_BCF_RESERVER3                   = 1 << 20;
constexpr uint32_t BCS_FLAG_BCF_RESERVER4                   = 1 << 21;
constexpr uint32_t BCS_FLAG_BCF_RESERVER5                   = 1 << 22;
constexpr uint32_t BCS_FLAG_BCF_RESERVER6                   = 1 << 23;
constexpr uint32_t BCS_FLAG_BCF_RESERVER7                   = 1 << 24;
constexpr uint32_t BCS_FLAG_BCF_RESERVER8                   = 1 << 25;
constexpr uint32_t BCS_FLAG_BCF_RESERVER9                   = 1 << 26;
constexpr uint32_t BCS_FLAG_BCF_RESERVER10                  = 1 << 27;
constexpr uint32_t BCS_FLAG_BCF_RESERVER11                  = 1 << 28;
constexpr uint32_t BCS_FLAG_BCF_RESERVER12                  = 1 << 29;
constexpr uint32_t BCS_FLAG_BCF_RESERVER13                  = 1 << 30;
constexpr uint32_t BCS_FLAG_BCF_RESERVER14                  = 1 << 31;

// GATT_Specification_Supplement_v8.pdf
// 3.33 Body Composition Feature
struct BodyCompositionFeatureStruct
{
    uint32_t flags{0};
};

// BCS_V1.0.0.pdf
// Body Composition Service v1.0.0
// 3.1 BodyCompositionFeature
class BodyCompositionFeature final : public BaseValueSpec<BodyCompositionFeatureStruct>
{
public:
    BVP_GETTER(bool, isTimeStampSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_TIME_STAMP_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isMultipleUsersSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_MULTIPLE_USERS_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isBasalMetabolismSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_BASAL_METABOLISM_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isMusclePercentageSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_MUSCLE_PERCENTAGE_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isMuscleMassSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_MUSCLE_MASS_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isFatFreeMassSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_FAT_FREE_MASS_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isSoftLeanMassSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_SOFT_LEAN_MASS_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isBodyWaterMassSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_BODY_WATER_MASS_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isImpedanceSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_IMPEDANCE_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isWeightSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_WEIGHT_SUPPORTED) != 0;
    }

    BVP_GETTER(bool, isHeightSupported, BodyCompositionFeatureStruct)
    {
        return (btSpecObject.flags & BCS_FLAG_BCF_HEIGHT_SUPPORTED) != 0;
    }

    BVP_GETTER_CONF(uint16_t, weightResolution, BodyCompositionFeatureStruct)
    {
        uint32_t resolution =
            (btSpecObject.flags & BCS_FLAG_BCF_WEIGHT_RESOLUTION0) +
            (btSpecObject.flags & BCS_FLAG_BCF_WEIGHT_RESOLUTION1) +
            (btSpecObject.flags & BCS_FLAG_BCF_WEIGHT_RESOLUTION2) +
            (btSpecObject.flags & BCS_FLAG_BCF_WEIGHT_RESOLUTION3);
        resolution = resolution >> BCS_FLAG_BCF_WEIGHT_RESOLUTION_SHIFT;

        switch (configuration.measurementUnits)
        {
            case MeasurementUnitsEnum::SI:
            {
                switch (resolution)
                {
                    case 0b0001: return 500;
                    case 0b0010: return 200;
                    case 0b0011: return 100;
                    case 0b0100: return 50;
                    case 0b0101: return 20;
                    case 0b0110: return 10;
                    case 0b0111: return 5;
                }
                break;
            }
            case MeasurementUnitsEnum::Imperial:
            {
                switch (resolution)
                {
                    case 0b0001: return 1000;
                    case 0b0010: return 500;
                    case 0b0011: return 200;
                    case 0b0100: return 100;
                    case 0b0101: return 50;
                    case 0b0110: return 20;
                    case 0b0111: return 10;
                }
                break;
            }
        }

        return 0;
    }

    BVP_GETTER_CONF(uint16_t, heightResolution, BodyCompositionFeatureStruct)
    {
        uint32_t resolution =
            (btSpecObject.flags & BCS_FLAG_BCF_HEIGHT_RESOLUTION0) +
            (btSpecObject.flags & BCS_FLAG_BCF_HEIGHT_RESOLUTION1) +
            (btSpecObject.flags & BCS_FLAG_BCF_HEIGHT_RESOLUTION2);
        resolution = resolution >> BCS_FLAG_BCF_HEIGHT_RESOLUTION_SHIFT;

        switch (configuration.measurementUnits)
        {
            case MeasurementUnitsEnum::SI:
            {
                switch (resolution)
                {
                    case 0b0001 : return 10;
                    case 0b0010 : return 5;
                    case 0b0011 : return 1;
                }
                break;
            }
            case MeasurementUnitsEnum::Imperial:
            {
                switch (resolution)
                {
                    case 0b0001 : return 1000;
                    case 0b0010 : return 500;
                    case 0b0011 : return 100;
                }
                break;
            }
        }

        return 0;
    }

private:
    BVP_CTORS(BaseValueSpec, BodyCompositionFeature, BodyCompositionFeatureStruct)

    BVP_PARSE(BodyCompositionFeatureStruct)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt32();

        return result;
    }

    BVP_TO_STRING_CONF(BodyCompositionFeatureStruct)
    {
        std::string str;

        str.append("Features: {");
        if (isTimeStampSupported(btSpecObject))
        {
            str.append(" TimeStamp");
        }
        if (isMultipleUsersSupported(btSpecObject))
        {
            str.append(" MultipleUsers");
        }
        if (isBasalMetabolismSupported(btSpecObject))
        {
            str.append(" BasalMetabolism");
        }
        if (isMusclePercentageSupported(btSpecObject))
        {
            str.append(" MusclePercentage");
        }
        if (isMuscleMassSupported(btSpecObject))
        {
            str.append(" MuscleMass");
        }
        if (isFatFreeMassSupported(btSpecObject))
        {
            str.append(" FatFreeMass");
        }
        if (isSoftLeanMassSupported(btSpecObject))
        {
            str.append(" SoftLeanMass");
        }
        if (isBodyWaterMassSupported(btSpecObject))
        {
            str.append(" BodyWaterMass");
        }
        if (isImpedanceSupported(btSpecObject))
        {
            str.append(" Impedance");
        }
        if (isWeightSupported(btSpecObject))
        {
            str.append(" Weight");
        }
        if (isHeightSupported(btSpecObject))
        {
            str.append(" Height");
        }
        str.append(" }");

        if (isWeightSupported(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", WeightResolution: {}{}",
                weightResolution(btSpecObject, configuration) / 1000.0,
                configuration.massUnits()
            );
        }

        if (isHeightSupported(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", HeightResolution: {}{}",
                heightResolution(btSpecObject, configuration) / 1000.0,
                configuration.lenghtUnits()
            );
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 4;
    }
};

}  // namespace bvp
