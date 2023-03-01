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
inline std::ostream &operator<<(std::ostream &os, const BatteryChemistryEnum value)
{
    switch (value)
    {
        case BatteryChemistryEnum::Unknown:     os << "<Unknown>";  break;
        case BatteryChemistryEnum::Alkaline:    os << "Alkaline";   break;
        case BatteryChemistryEnum::LeadAcid:    os << "LeadAcid";   break;
        case BatteryChemistryEnum::LiFeS2:      os << "LiFeS2";     break;
        case BatteryChemistryEnum::LiMnO2:      os << "LiMnO2";     break;
        case BatteryChemistryEnum::LiIon:       os << "LiIon";      break;
        case BatteryChemistryEnum::LiPo:        os << "LiPo";       break;
        case BatteryChemistryEnum::NiOx:        os << "NiOx";       break;
        case BatteryChemistryEnum::NiCd:        os << "NiCd";       break;
        case BatteryChemistryEnum::NiMH:        os << "NiMH";       break;
        case BatteryChemistryEnum::AgZn:        os << "AgZn";       break;
        case BatteryChemistryEnum::ZnChloride:  os << "ZnChloride"; break;
        case BatteryChemistryEnum::ZnAir:       os << "ZnAir";      break;
        case BatteryChemistryEnum::ZnCarbon:    os << "ZnCarbon";   break;
        case BatteryChemistryEnum::Other:       os << "<Other>";    break;
    }

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
    bool isBatteryManufactureDatePresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_MANUFACTURE_DATE_PRESENT) != 0;
    }

    bool isBatteryExpirationDatePresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_EXPIRATION_DATE_PRESENT) != 0;
    }

    bool isBatteryDesignedCapacityPresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_DESIGNED_CAPACITY_PRESENT) != 0;
    }

    bool isBatteryLowEnergyPresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_LOW_ENERGY_PRESENT) != 0;
    }

    bool isBatteryCriticalEnergyPresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_CRITICAL_ENERGY_PRESENT) != 0;
    }

    bool isBatteryChemistryPresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_CHEMISTRY_PRESENT) != 0;
    }

    bool isNominalVoltagePresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_NOMINAL_VOLTAGE_PRESENT) != 0;
    }

    bool isBatteryAggregationGroupPresent() const
    {
        return (m_btSpecObject.flags & BAI_FLAG_BATTERY_AGGREGATION_GROUP_PRESENT) != 0;
    }

    bool isBatteryReplaceable() const
    {
        return (m_btSpecObject.batteryFeatures & BAI_FEATURE_BATTERY_REPLACEABLE) != 0;
    }

    bool isBatteryRechargeable() const
    {
        return (m_btSpecObject.batteryFeatures & BAI_FEATURE_BATTERY_RECHARGEABLE) != 0;
    }

    DateUTCStruct batteryManufactureDate() const
    {
        return m_btSpecObject.batteryManufactureDate;
    }

    DateUTCStruct batteryExpirationDate() const
    {
        return m_btSpecObject.batteryExpirationDate;
    }

    MedFloat16 batteryDesignedCapacity() const
    {
        return m_btSpecObject.batteryDesignedCapacity;
    }

    MedFloat16 batteryLowEnergy() const
    {
        return m_btSpecObject.batteryLowEnergy;
    }

    MedFloat16 batteryCriticalEnergy() const
    {
        return m_btSpecObject.batteryCriticalEnergy;
    }

    BatteryChemistryEnum batteryChemistry() const
    {
        return m_btSpecObject.batteryChemistry;
    }

    MedFloat16 nominalVoltage() const
    {
        return m_btSpecObject.nominalVoltage;
    }

    uint8_t batteryAggregationGroup() const
    {
        return m_btSpecObject.batteryAggregationGroup;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryInformation, BatteryInformationStruct)

    virtual bool checkSize(size_t size) override
    {
        return size > 2 && size < 20;
    }

    virtual bool parse(Parser &parser) override
    {
        m_btSpecObject.flags = parser.parseUInt16();
        m_btSpecObject.batteryFeatures = parser.parseUInt8();

        if (isBatteryManufactureDatePresent())
        {
            m_btSpecObject.batteryManufactureDate = DateUTC(parser, configuration).getBtSpecObject();
        }
        if (isBatteryExpirationDatePresent())
        {
            m_btSpecObject.batteryExpirationDate = DateUTC(parser, configuration).getBtSpecObject();
        }
        if (isBatteryDesignedCapacityPresent())
        {
            m_btSpecObject.batteryDesignedCapacity = parser.parseMedFloat16();
        }
        if (isBatteryLowEnergyPresent())
        {
            m_btSpecObject.batteryLowEnergy = parser.parseMedFloat16();
        }
        if (isBatteryCriticalEnergyPresent())
        {
            m_btSpecObject.batteryCriticalEnergy = parser.parseMedFloat16();
        }
        if (isBatteryChemistryPresent())
        {
            m_btSpecObject.batteryChemistry %= BatteryChemistryEnum(parser.parseUInt8());
        }
        if (isNominalVoltagePresent())
        {
            m_btSpecObject.nominalVoltage = parser.parseMedFloat16();
        }
        if (isBatteryAggregationGroupPresent())
        {
            m_btSpecObject.batteryAggregationGroup = parser.parseUInt8();
        }

        return true;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "BatteryReplaceable: " << (isBatteryReplaceable() ? "Yes" : "No");
        oss << ", BatteryRechargeable: " << (isBatteryRechargeable() ? "Yes" : "No");

        std::ostringstream ossInfo;
        if (isBatteryManufactureDatePresent())
        {
            ossInfo << ", BatteryManufactureDate: " << DateUTC(m_btSpecObject.batteryManufactureDate, configuration);
        }
        if (isBatteryExpirationDatePresent())
        {
            ossInfo << ", BatteryExpirationDate: " << DateUTC(m_btSpecObject.batteryExpirationDate, configuration);
        }
        if (isBatteryDesignedCapacityPresent())
        {
            ossInfo << ", BatteryDesignedCapacity: " << m_btSpecObject.batteryDesignedCapacity << "kWh";
        }
        if (isBatteryLowEnergyPresent())
        {
            ossInfo << ", BatteryLowEnergy: " << m_btSpecObject.batteryLowEnergy << "kWh";
        }
        if (isBatteryCriticalEnergyPresent())
        {
            ossInfo << ", BatteryCriticalEnergy: " << m_btSpecObject.batteryCriticalEnergy << "kWh";
        }
        if (isBatteryChemistryPresent())
        {
            ossInfo << ", BatteryChemistry: " << m_btSpecObject.batteryChemistry;
        }
        if (isNominalVoltagePresent())
        {
            ossInfo << ", NominalVoltage: " << m_btSpecObject.nominalVoltage << "V";
        }
        if (isBatteryAggregationGroupPresent())
        {
            ossInfo << ", BatteryAggregationGroup: ";
            if (0 == m_btSpecObject.batteryAggregationGroup)
            {
                ossInfo << "<NotInGroup>";
            }
            else if (255 == m_btSpecObject.batteryAggregationGroup)
            {
                ossInfo << "<Reserved>";
            }
            else
            {
                ossInfo << static_cast<int>(m_btSpecObject.batteryAggregationGroup);
            }
        }
        std::string info = ossInfo.str();

        if (!info.empty())
        {
            oss << info;
        }
    }
};

}  // namespace bvp
