#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.23.1 Flags field
constexpr uint8_t BES_FLAG_EXTERNAL_SOURCE_POWER_PRESENT            = 1 << 0;
constexpr uint8_t BES_FLAG_PRESENT_VOLTAGE_PRESENT                  = 1 << 1;
constexpr uint8_t BES_FLAG_AVAILABLE_ENERGY_PRESENT                 = 1 << 2;
constexpr uint8_t BES_FLAG_AVAILABLE_BATTERY_CAPACITY_PRESENT       = 1 << 3;
constexpr uint8_t BES_FLAG_CHARGE_RATE_PRESENT                      = 1 << 4;
constexpr uint8_t BES_FLAG_AVAILABLE_ENERGY_AT_LAST_CHARGE_PRESENT  = 1 << 5;
constexpr uint8_t BES_FLAG_RESERVED1                                = 1 << 6;
constexpr uint8_t BES_FLAG_RESERVED2                                = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.23 Battery Energy Status
struct BatteryEnergyStatusStruct
{
    uint8_t flags{0};
    MedFloat16 externalSourcePower;  // org.bluetooth.unit.power.watt
    MedFloat16 presentVoltage;  // org.bluetooth.unit.electric_potential_difference.volt
    MedFloat16 availableEnergy;  // org.bluetooth.unit.energy.kilowatt_hour
    MedFloat16 availableBatteryCapacity;  // org.bluetooth.unit.energy.kilowatt_hour
    MedFloat16 chargeRate;  // org.bluetooth.unit.power.watt
    MedFloat16 availableEnergyAtLastCharge;  // org.bluetooth.unit.energy.kilowatt_hour
};

class BatteryEnergyStatus final : public BaseValueSpec<BatteryEnergyStatusStruct>
{
public:
    BVP_GETTER(bool, isExternalSourcePowerPresent, BatteryEnergyStatusStruct)
    {
        return (btSpecObject.flags & BES_FLAG_EXTERNAL_SOURCE_POWER_PRESENT) != 0;
    }

    BVP_GETTER(bool, isPresentVoltagePresent, BatteryEnergyStatusStruct)
    {
        return (btSpecObject.flags & BES_FLAG_PRESENT_VOLTAGE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isAvailableEnergyPresent, BatteryEnergyStatusStruct)
    {
        return (btSpecObject.flags & BES_FLAG_AVAILABLE_ENERGY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isAvailableBatteryCapacityPresent, BatteryEnergyStatusStruct)
    {
        return (btSpecObject.flags & BES_FLAG_AVAILABLE_BATTERY_CAPACITY_PRESENT) != 0;
    }

    BVP_GETTER(bool, isChargeRatePresent, BatteryEnergyStatusStruct)
    {
        return (btSpecObject.flags & BES_FLAG_CHARGE_RATE_PRESENT) != 0;
    }

    BVP_GETTER(bool, isAvailableEnergyAtLastChargePresent, BatteryEnergyStatusStruct)
    {
        return (btSpecObject.flags & BES_FLAG_AVAILABLE_ENERGY_AT_LAST_CHARGE_PRESENT) != 0;
    }

    BVP_GETTER(MedFloat16, externalSourcePower, BatteryEnergyStatusStruct)
    {
        return btSpecObject.externalSourcePower;
    }

    BVP_GETTER(MedFloat16, presentVoltage, BatteryEnergyStatusStruct)
    {
        return btSpecObject.presentVoltage;
    }

    BVP_GETTER(MedFloat16, availableEnergy, BatteryEnergyStatusStruct)
    {
        return btSpecObject.availableEnergy;
    }

    BVP_GETTER(MedFloat16, availableBatteryCapacity, BatteryEnergyStatusStruct)
    {
        return btSpecObject.availableBatteryCapacity;
    }

    BVP_GETTER(MedFloat16, chargeRate, BatteryEnergyStatusStruct)
    {
        return btSpecObject.chargeRate;
    }

    BVP_GETTER(MedFloat16, availableEnergyAtLastCharge, BatteryEnergyStatusStruct)
    {
        return btSpecObject.availableEnergyAtLastCharge;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryEnergyStatus, BatteryEnergyStatusStruct)

    BVP_PARSE(BatteryEnergyStatusStruct)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt8();

        if (isExternalSourcePowerPresent(btSpecObject))
        {
            btSpecObject.externalSourcePower = parser.parseMedFloat16();
        }
        if (isPresentVoltagePresent(btSpecObject))
        {
            btSpecObject.presentVoltage = parser.parseMedFloat16();
        }
        if (isAvailableEnergyPresent(btSpecObject))
        {
            btSpecObject.availableEnergy = parser.parseMedFloat16();
        }
        if (isAvailableBatteryCapacityPresent(btSpecObject))
        {
            btSpecObject.availableBatteryCapacity = parser.parseMedFloat16();
        }
        if (isChargeRatePresent(btSpecObject))
        {
            btSpecObject.chargeRate = parser.parseMedFloat16();
        }
        if (isAvailableEnergyAtLastChargePresent(btSpecObject))
        {
            btSpecObject.availableEnergyAtLastCharge = parser.parseMedFloat16();
        }

        return result;
    }

    BVP_TO_STRING(BatteryEnergyStatusStruct)
    {
        std::string str;

        if (isExternalSourcePowerPresent(btSpecObject))
        {
            str.append("ExternalSourcePower: ");
            str.append(btSpecObject.externalSourcePower.toString());
            str.append("W, ");
        }
        if (isPresentVoltagePresent(btSpecObject))
        {
            str.append("PresentVoltage: ");
            str.append(btSpecObject.presentVoltage.toString());
            str.append("V, ");
        }
        if (isAvailableEnergyPresent(btSpecObject))
        {
            str.append("AvailableEnergy: ");
            str.append(btSpecObject.availableEnergy.toString());
            str.append("kWh, ");
        }
        if (isAvailableBatteryCapacityPresent(btSpecObject))
        {
            str.append("AvailableBatteryCapacity: ");
            str.append(btSpecObject.availableBatteryCapacity.toString());
            str.append("kWh, ");
        }
        if (isChargeRatePresent(btSpecObject))
        {
            str.append("ChargeRate: ");
            str.append(btSpecObject.chargeRate.toString());
            str.append("W, ");
        }
        if (isAvailableEnergyAtLastChargePresent(btSpecObject))
        {
            str.append("AvailableEnergyAtLastCharge: ");
            str.append(btSpecObject.availableEnergyAtLastCharge.toString());
            str.append("kWh, ");
        }

        if (str.empty())
        {
            return "<NoData>";
        }

        str.pop_back();
        str.pop_back();

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size > 0 && size < 14;
    }
};

}  // namespace bvp
