#pragma once

#include "basevalue.h"
#include "dateutc.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.26.1 Flags field
constexpr uint16_t BAI_FLAG_BATTERY_MANUFACTURE_DATE_PRESENT    = 1 << 0;
constexpr uint16_t BAI_FLAG_BATTERY_EXPIRATION_DATE_PRESENT     = 1 << 1;
constexpr uint16_t BAI_FLAG_BATTERY_DESIGNED_CAPACITY_PRESENT   = 1 << 2;
constexpr uint16_t BAI_FLAG_BATTERY_LOW_ENERGY_PRESENT          = 1 << 3;
constexpr uint16_t BAI_FLAG_BATTERY_CRITICAL_ENERGY_PRESENT     = 1 << 4;
constexpr uint16_t BAI_FLAG_BATTERY_CHEMISTRY_PRESENT           = 1 << 5;
constexpr uint16_t BAI_FLAG_NOMINAL_VOLTAGE_PRESENT             = 1 << 6;
constexpr uint16_t BAI_FLAG_BATTERY_AGGREGATION_GROUP_PRESENT   = 1 << 7;
constexpr uint16_t BAI_FLAG_RESERVED1                           = 1 << 8;
constexpr uint16_t BAI_FLAG_RESERVED2                           = 1 << 9;
constexpr uint16_t BAI_FLAG_RESERVED3                           = 1 << 10;
constexpr uint16_t BAI_FLAG_RESERVED4                           = 1 << 11;
constexpr uint16_t BAI_FLAG_RESERVED5                           = 1 << 12;
constexpr uint16_t BAI_FLAG_RESERVED6                           = 1 << 13;
constexpr uint16_t BAI_FLAG_RESERVED7                           = 1 << 14;
constexpr uint16_t BAI_FLAG_RESERVED8                           = 1 << 15;

// GATT_Specification_Supplement_v8.pdf
// 3.26.2 Battery Features field
constexpr uint8_t BAI_FEATURE_BATTERY_REPLACEABLE  = 1 << 0;
constexpr uint8_t BAI_FEATURE_BATTERY_RECHARGEABLE = 1 << 1;
constexpr uint8_t BAI_FEATURE_RESERVED1            = 1 << 2;
constexpr uint8_t BAI_FEATURE_RESERVED2            = 1 << 3;
constexpr uint8_t BAI_FEATURE_RESERVED3            = 1 << 4;
constexpr uint8_t BAI_FEATURE_RESERVED4            = 1 << 5;
constexpr uint8_t BAI_FEATURE_RESERVED5            = 1 << 6;
constexpr uint8_t BAI_FEATURE_RESERVED6            = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.26.3 Battery Chemistry field
enum class BatteryChemistryEnum : uint8_t
{
    Unknown     = 0,
    Alkaline    = 1,
    LeadAcid    = 2,
    LiFeS2      = 3,
    LiMnO2      = 4,
    LiIon       = 5,
    LiPo        = 6,
    NiOx        = 7,
    NiCd        = 8,
    NiMH        = 9,
    AgZn        = 10,
    ZnChloride  = 11,
    ZnAir       = 12,
    ZnCarbon    = 13,
    // 14–254 - Reserved for Future Use
    Other       = 255
};
inline std::string enumToString(const BatteryChemistryEnum value)
{
    std::string str;

    switch (value)
    {
        case BatteryChemistryEnum::Unknown:     str = "<Unknown>";  break;
        case BatteryChemistryEnum::Alkaline:    str = "Alkaline";   break;
        case BatteryChemistryEnum::LeadAcid:    str = "LeadAcid";   break;
        case BatteryChemistryEnum::LiFeS2:      str = "LiFeS2";     break;
        case BatteryChemistryEnum::LiMnO2:      str = "LiMnO2";     break;
        case BatteryChemistryEnum::LiIon:       str = "LiIon";      break;
        case BatteryChemistryEnum::LiPo:        str = "LiPo";       break;
        case BatteryChemistryEnum::NiOx:        str = "NiOx";       break;
        case BatteryChemistryEnum::NiCd:        str = "NiCd";       break;
        case BatteryChemistryEnum::NiMH:        str = "NiMH";       break;
        case BatteryChemistryEnum::AgZn:        str = "AgZn";       break;
        case BatteryChemistryEnum::ZnChloride:  str = "ZnChloride"; break;
        case BatteryChemistryEnum::ZnAir:       str = "ZnAir";      break;
        case BatteryChemistryEnum::ZnCarbon:    str = "ZnCarbon";   break;
        case BatteryChemistryEnum::Other:       str = "<Other>";    break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const BatteryChemistryEnum value)
{
    os << enumToString(value);
    return os;
}
inline BatteryChemistryEnum &operator%=(BatteryChemistryEnum &lhs, const BatteryChemistryEnum &rhs)
{
    lhs = BatteryChemistryEnum::Unknown;

    switch (rhs)
    {
        case BatteryChemistryEnum::Unknown:
        case BatteryChemistryEnum::Alkaline:
        case BatteryChemistryEnum::LeadAcid:
        case BatteryChemistryEnum::LiFeS2:
        case BatteryChemistryEnum::LiMnO2:
        case BatteryChemistryEnum::LiIon:
        case BatteryChemistryEnum::LiPo:
        case BatteryChemistryEnum::NiOx:
        case BatteryChemistryEnum::NiCd:
        case BatteryChemistryEnum::NiMH:
        case BatteryChemistryEnum::AgZn:
        case BatteryChemistryEnum::ZnChloride:
        case BatteryChemistryEnum::ZnAir:
        case BatteryChemistryEnum::ZnCarbon:
        case BatteryChemistryEnum::Other:
            lhs = rhs;
            break;
    }

    return lhs;
}

// GATT_Specification_Supplement_v8.pdf
// 3.26 Battery Information
struct BatteryInformationStruct
{
    uint16_t flags{0};
    uint8_t batteryFeatures{0};
    DateUTCStruct batteryManufactureDate;
    DateUTCStruct batteryExpirationDate;
    MedFloat16 batteryDesignedCapacity;  // org.bluetooth.unit.energy.kilowatt_hour
    MedFloat16 batteryLowEnergy;  // org.bluetooth.unit.energy.kilowatt_hour
    MedFloat16 batteryCriticalEnergy;  // org.bluetooth.unit.energy.kilowatt_hour
    BatteryChemistryEnum batteryChemistry{BatteryChemistryEnum::Unknown};
    MedFloat16 nominalVoltage;  // org.bluetooth.unit.electric_potential_difference.volt
    uint8_t batteryAggregationGroup{0};
};

class BatteryInformation final : public BaseValueSpec<BatteryInformationStruct>
{
public:
    BVP_GETTER(bool, isBatteryManufactureDatePresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_MANUFACTURE_DATE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryExpirationDatePresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_EXPIRATION_DATE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryDesignedCapacityPresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_DESIGNED_CAPACITY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryLowEnergyPresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_LOW_ENERGY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryCriticalEnergyPresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_CRITICAL_ENERGY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryChemistryPresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_CHEMISTRY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isNominalVoltagePresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_NOMINAL_VOLTAGE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryAggregationGroupPresent, BatteryInformationStruct)
    {
        return (btSpecObject.flags & BAI_FLAG_BATTERY_AGGREGATION_GROUP_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryReplaceable, BatteryInformationStruct)
    {
        return (btSpecObject.batteryFeatures & BAI_FEATURE_BATTERY_REPLACEABLE) != 0;
    }

    BVP_GETTER(bool, isBatteryRechargeable, BatteryInformationStruct)
    {
        return (btSpecObject.batteryFeatures & BAI_FEATURE_BATTERY_RECHARGEABLE) != 0;
    }

    BVP_GETTER(DateUTCStruct, batteryManufactureDate, BatteryInformationStruct)
    {
        return btSpecObject.batteryManufactureDate;
    }

    BVP_GETTER(DateUTCStruct, batteryExpirationDate, BatteryInformationStruct)
    {
        return btSpecObject.batteryExpirationDate;
    }

    BVP_GETTER(MedFloat16, batteryDesignedCapacity, BatteryInformationStruct)
    {
        return btSpecObject.batteryDesignedCapacity;
    }

    BVP_GETTER(MedFloat16, batteryLowEnergy, BatteryInformationStruct)
    {
        return btSpecObject.batteryLowEnergy;
    }

    BVP_GETTER(MedFloat16, batteryCriticalEnergy, BatteryInformationStruct)
    {
        return btSpecObject.batteryCriticalEnergy;
    }

    BVP_GETTER(BatteryChemistryEnum, batteryChemistry, BatteryInformationStruct)
    {
        return btSpecObject.batteryChemistry;
    }

    BVP_GETTER(MedFloat16, nominalVoltage, BatteryInformationStruct)
    {
        return btSpecObject.nominalVoltage;
    }

    BVP_GETTER(uint8_t, batteryAggregationGroup, BatteryInformationStruct)
    {
        return btSpecObject.batteryAggregationGroup;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryInformation, BatteryInformationStruct)

    BVP_PARSE(BatteryInformationStruct)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt16();
        btSpecObject.batteryFeatures = parser.parseUInt8();

        if (isBatteryManufactureDatePresent(btSpecObject))
        {
            result &= DateUTC::parse(parser, btSpecObject.batteryManufactureDate);
        }
        if (isBatteryExpirationDatePresent(btSpecObject))
        {
            result &= DateUTC::parse(parser, btSpecObject.batteryExpirationDate);
        }
        if (isBatteryDesignedCapacityPresent(btSpecObject))
        {
            btSpecObject.batteryDesignedCapacity = parser.parseMedFloat16();
        }
        if (isBatteryLowEnergyPresent(btSpecObject))
        {
            btSpecObject.batteryLowEnergy = parser.parseMedFloat16();
        }
        if (isBatteryCriticalEnergyPresent(btSpecObject))
        {
            btSpecObject.batteryCriticalEnergy = parser.parseMedFloat16();
        }
        if (isBatteryChemistryPresent(btSpecObject))
        {
            btSpecObject.batteryChemistry %= BatteryChemistryEnum(parser.parseUInt8());
        }
        if (isNominalVoltagePresent(btSpecObject))
        {
            btSpecObject.nominalVoltage = parser.parseMedFloat16();
        }
        if (isBatteryAggregationGroupPresent(btSpecObject))
        {
            btSpecObject.batteryAggregationGroup = parser.parseUInt8();
        }

        return result;
    }

    BVP_TO_STRING(BatteryInformationStruct)
    {
        std::string str;

        str.append("BatteryReplaceable: ");
        str.append(isBatteryReplaceable(btSpecObject) ? "Yes" : "No");

        str.append(", BatteryRechargeable: ");
        str.append(isBatteryRechargeable(btSpecObject) ? "Yes" : "No");

        if (isBatteryManufactureDatePresent(btSpecObject))
        {
            str.append(", BatteryManufactureDate: ");
            str.append(DateUTC::toStringInternal(btSpecObject.batteryManufactureDate));
        }
        if (isBatteryExpirationDatePresent(btSpecObject))
        {
            str.append(", BatteryExpirationDate: ");
            str.append(DateUTC::toStringInternal(btSpecObject.batteryExpirationDate));
        }
        if (isBatteryDesignedCapacityPresent(btSpecObject))
        {
            str.append(", BatteryDesignedCapacity: ");
            str.append(btSpecObject.batteryDesignedCapacity.toString());
            str.append("kWh");
        }
        if (isBatteryLowEnergyPresent(btSpecObject))
        {
            str.append(", BatteryLowEnergy: ");
            str.append(btSpecObject.batteryLowEnergy.toString());
            str.append("kWh");
        }
        if (isBatteryCriticalEnergyPresent(btSpecObject))
        {
            str.append(", BatteryCriticalEnergy: ");
            str.append(btSpecObject.batteryCriticalEnergy.toString());
            str.append("kWh");
        }
        if (isBatteryChemistryPresent(btSpecObject))
        {
            str.append(", BatteryChemistry: ");
            str.append(enumToString(btSpecObject.batteryChemistry));
        }
        if (isNominalVoltagePresent(btSpecObject))
        {
            str.append(", NominalVoltage: ");
            str.append(btSpecObject.nominalVoltage.toString());
            str.append("V");
        }
        if (isBatteryAggregationGroupPresent(btSpecObject))
        {
            str.append(", BatteryAggregationGroup: ");
            if (0 == btSpecObject.batteryAggregationGroup)
            {
                str.append("<NotInGroup>");
            }
            else if (255 == btSpecObject.batteryAggregationGroup)
            {
                str.append("<Reserved>");
            }
            else
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{}",
                    btSpecObject.batteryAggregationGroup
                );
            }
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size > 2 && size < 20;
    }
};

}  // namespace bvp
