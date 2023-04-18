#pragma once

#include <iomanip>

#include "basevalue.h"
#include "batterylevel.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.28.1 Flags field
constexpr uint8_t BAS_FLAG_IDENTIFIER_PRESENT           = 1 << 0;
constexpr uint8_t BAS_FLAG_BATTERY_LEVEL_PRESENT        = 1 << 1;
constexpr uint8_t BAS_FLAG_ADDITIONAL_STATUS_PRESENT    = 1 << 2;
constexpr uint8_t BAS_FLAG_RESERVED1                    = 1 << 3;
constexpr uint8_t BAS_FLAG_RESERVED2                    = 1 << 4;
constexpr uint8_t BAS_FLAG_RESERVED3                    = 1 << 5;
constexpr uint8_t BAS_FLAG_RESERVED4                    = 1 << 6;
constexpr uint8_t BAS_FLAG_RESERVED5                    = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.28.2 Power State field
constexpr uint8_t BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT    = 1;
constexpr uint8_t BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT = 3;
constexpr uint8_t BAS_PS_BATTERY_CHARGE_STATE_SHIFT                     = 5;
constexpr uint8_t BAS_PS_BATTERY_CHARGE_LEVEL_SHIFT                     = 7;
constexpr uint8_t BAS_PS_CHARGING_TYPE_SHIFT                            = 9;

constexpr uint16_t BAS_PS_BATTERY_PRESENT                               = 1 <<  0;
constexpr uint16_t BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED0        = 1 << BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT;
constexpr uint16_t BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED1        = 1 <<  2;
constexpr uint16_t BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED0     = 1 << BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT;
constexpr uint16_t BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED1     = 1 <<  4;
constexpr uint16_t BAS_PS_BATTERY_CHARGE_STATE0                         = 1 << BAS_PS_BATTERY_CHARGE_STATE_SHIFT;
constexpr uint16_t BAS_PS_BATTERY_CHARGE_STATE1                         = 1 <<  6;
constexpr uint16_t BAS_PS_BATTERY_CHARGE_LEVEL0                         = 1 << BAS_PS_BATTERY_CHARGE_LEVEL_SHIFT;
constexpr uint16_t BAS_PS_BATTERY_CHARGE_LEVEL1                         = 1 <<  8;
constexpr uint16_t BAS_PS_CHARGING_TYPE0                                = 1 << BAS_PS_CHARGING_TYPE_SHIFT;
constexpr uint16_t BAS_PS_CHARGING_TYPE1                                = 1 << 10;
constexpr uint16_t BAS_PS_CHARGING_TYPE2                                = 1 << 11;
constexpr uint16_t BAS_PS_CHARGING_FAULT_REASON_BATTERY                 = 1 << 12;
constexpr uint16_t BAS_PS_CHARGING_FAULT_REASON_EXTERNAL_POWER_SOURCE   = 1 << 13;
constexpr uint16_t BAS_PS_CHARGING_FAULT_REASON_OTHER                   = 1 << 14;
constexpr uint16_t BAS_PS_RESERVED1                                     = 1 << 15;

enum class ExternalPowerSourceConnectedEnum
{
    No          = 0,
    Yes         = 1,
    Unknown     = 2,
    Reserved    = 3
};
inline std::ostream &operator<<(std::ostream &os, const ExternalPowerSourceConnectedEnum value)
{
    switch (value)
    {
        case ExternalPowerSourceConnectedEnum::No:          os << "No";         break;
        case ExternalPowerSourceConnectedEnum::Yes:         os << "Yes";        break;
        case ExternalPowerSourceConnectedEnum::Unknown:     os << "<Unknown>";  break;
        case ExternalPowerSourceConnectedEnum::Reserved:    os << "<Reserved>"; break;
    }

    return os;
}

enum class BatteryChargeStateEnum
{
    Unknown             = 0,
    Charging            = 1,
    DischargingActive   = 2,
    DischargingInactive = 3
};
inline std::ostream &operator<<(std::ostream &os, const BatteryChargeStateEnum value)
{
    switch (value)
    {
        case BatteryChargeStateEnum::Unknown:               os << "<Unknown>";              break;
        case BatteryChargeStateEnum::Charging:              os << "Charging";               break;
        case BatteryChargeStateEnum::DischargingActive:     os << "DischargingActive";      break;
        case BatteryChargeStateEnum::DischargingInactive:   os << "DischargingInactive";    break;
    }

    return os;
}

enum class BatteryChargeLevelEnum
{
    Unknown     = 0,
    Good        = 1,
    Low         = 2,
    Critical    = 3
};
inline std::ostream &operator<<(std::ostream &os, const BatteryChargeLevelEnum value)
{
    switch (value) {
        case BatteryChargeLevelEnum::Unknown:   os << "<Unknown>";  break;
        case BatteryChargeLevelEnum::Good:      os << "Good";       break;
        case BatteryChargeLevelEnum::Low:       os << "Low";        break;
        case BatteryChargeLevelEnum::Critical:  os << "Critical";   break;
    }

    return os;
}

enum class ChargingTypeEnum
{
    UnknownOrNotCharging    = 0,
    ConstantCurrent         = 1,
    ConstantVoltage         = 2,
    Trickle                 = 3,
    Float                   = 4,
    Reserved1               = 5,
    Reserved2               = 6,
    Reserved3               = 7
};
inline std::ostream &operator<<(std::ostream &os, const ChargingTypeEnum value)
{
    switch (value) {
        case ChargingTypeEnum::UnknownOrNotCharging:    os << "UnknownOrNotCharging";   break;
        case ChargingTypeEnum::ConstantCurrent:         os << "ConstantCurrent";        break;
        case ChargingTypeEnum::ConstantVoltage:         os << "ConstantVoltage";        break;
        case ChargingTypeEnum::Trickle:                 os << "Trickle";                break;
        case ChargingTypeEnum::Float:                   os << "Float";                  break;
        case ChargingTypeEnum::Reserved1:               os << "<Reserved1>";            break;
        case ChargingTypeEnum::Reserved2:               os << "<Reserved2>";            break;
        case ChargingTypeEnum::Reserved3:               os << "<Reserved3>";            break;
    }

    return os;
}

// GATT_Specification_Supplement_v8.pdf
// 3.28.3 Additional Status field
constexpr uint8_t BAS_AS_SERVICE_REQUIRED_SHIFT = 0;

constexpr uint8_t BAS_AS_SERVICE_REQUIRED0  = 1 << BAS_AS_SERVICE_REQUIRED_SHIFT;
constexpr uint8_t BAS_AS_SERVICE_REQUIRED1  = 1 << 1;
constexpr uint8_t BAS_AS_BATTERY_FAULT      = 1 << 2;
constexpr uint8_t BAS_AS_RESERVED1          = 1 << 3;
constexpr uint8_t BAS_AS_RESERVED2          = 1 << 4;
constexpr uint8_t BAS_AS_RESERVED3          = 1 << 5;
constexpr uint8_t BAS_AS_RESERVED4          = 1 << 6;
constexpr uint8_t BAS_AS_RESERVED5          = 1 << 7;

enum class ServiceRequiredEnum
{
    False       = 0,
    True        = 1,
    Unknown     = 2,
    Reserved    = 3
};
inline std::ostream &operator<<(std::ostream &os, const ServiceRequiredEnum value)
{
    switch (value) {
        case ServiceRequiredEnum::False:    os << "False";      break;
        case ServiceRequiredEnum::True:     os << "True";       break;
        case ServiceRequiredEnum::Unknown:  os << "<Unknown>";  break;
        case ServiceRequiredEnum::Reserved: os << "<Reserved>"; break;
    }

    return os;
}

// GATT_Specification_Supplement_v8.pdf
// 3.28 Battery Level Status
struct BatteryLevelStatusStruct
{
    uint8_t flags{0};
    uint16_t powerState{0};
    uint16_t identifier{0};
    BatteryLevelStruct batteryLevel;
    uint8_t additionalStatus{0};
};

// BAS_V1.1.pdf
// Battery Service v1.1
// 3.2 Battery Level Status
class BatteryLevelStatus final : public BaseValueSpec<BatteryLevelStatusStruct>
{
public:
    BVP_GETTER(bool, isIdentifierPresent, BatteryLevelStatusStruct)
    {
        return (btSpecObject.flags & BAS_FLAG_IDENTIFIER_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryLevelPresent, BatteryLevelStatusStruct)
    {
        return (btSpecObject.flags & BAS_FLAG_BATTERY_LEVEL_PRESENT) != 0;
    }

    BVP_GETTER(bool, isAdditionalStatusPresent, BatteryLevelStatusStruct)
    {
        return (btSpecObject.flags & BAS_FLAG_ADDITIONAL_STATUS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryPresent, BatteryLevelStatusStruct)
    {
        return (btSpecObject.powerState & BAS_PS_BATTERY_PRESENT) != 0;
    }

    BVP_GETTER(ExternalPowerSourceConnectedEnum, wiredExternalPowerSourceConnected, BatteryLevelStatusStruct)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED0) +
            (btSpecObject.powerState & BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED1);
        value = value >> BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT;

        return ExternalPowerSourceConnectedEnum(value);
    }

    BVP_GETTER(ExternalPowerSourceConnectedEnum, wirelessExternalPowerSourceConnected, BatteryLevelStatusStruct)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED0) +
            (btSpecObject.powerState & BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED1);
        value = value >> BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT;

        return ExternalPowerSourceConnectedEnum(value);
    }

    BVP_GETTER(BatteryChargeStateEnum, batteryChargeState, BatteryLevelStatusStruct)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_STATE0) +
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_STATE1);
        value = value >> BAS_PS_BATTERY_CHARGE_STATE_SHIFT;

        return BatteryChargeStateEnum(value);
    }

    BVP_GETTER(BatteryChargeLevelEnum, batteryChargeLevel, BatteryLevelStatusStruct)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_LEVEL0) +
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_LEVEL1);
        value = value >> BAS_PS_BATTERY_CHARGE_LEVEL_SHIFT;

        return BatteryChargeLevelEnum(value);
    }

    BVP_GETTER(ChargingTypeEnum, chargingType, BatteryLevelStatusStruct)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_CHARGING_TYPE0) +
            (btSpecObject.powerState & BAS_PS_CHARGING_TYPE1) +
            (btSpecObject.powerState & BAS_PS_CHARGING_TYPE2);
        value = value >> BAS_PS_CHARGING_TYPE_SHIFT;

        return ChargingTypeEnum(value);
    }

    BVP_GETTER(bool, isChargingFaultReasonBattery, BatteryLevelStatusStruct)
    {
        return (btSpecObject.powerState & BAS_PS_CHARGING_FAULT_REASON_BATTERY) != 0;
    }

    BVP_GETTER(bool, isChargingFaultReasonExternalPowerSource, BatteryLevelStatusStruct)
    {
        return (btSpecObject.powerState & BAS_PS_CHARGING_FAULT_REASON_EXTERNAL_POWER_SOURCE) != 0;
    }

    BVP_GETTER(bool, isChargingFaultReasonOther, BatteryLevelStatusStruct)
    {
        return (btSpecObject.powerState & BAS_PS_CHARGING_FAULT_REASON_OTHER) != 0;
    }

    BVP_GETTER(bool, hasChargingFault, BatteryLevelStatusStruct)
    {
        return
            isChargingFaultReasonBattery(btSpecObject) ||
            isChargingFaultReasonExternalPowerSource(btSpecObject) ||
            isChargingFaultReasonOther(btSpecObject);
    }

    BVP_GETTER(uint16_t, identifier, BatteryLevelStatusStruct)
    {
        return btSpecObject.identifier;
    }

    BVP_GETTER(uint8_t, batteryLevel, BatteryLevelStatusStruct)
    {
        return btSpecObject.batteryLevel.batteryLevel;
    }

    BVP_GETTER(ServiceRequiredEnum, serviceRequired, BatteryLevelStatusStruct)
    {
        uint8_t value =
            (btSpecObject.additionalStatus & BAS_AS_SERVICE_REQUIRED0) +
            (btSpecObject.additionalStatus & BAS_AS_SERVICE_REQUIRED1);
        value = value >> BAS_AS_SERVICE_REQUIRED_SHIFT;

        return ServiceRequiredEnum(value);
    }

    BVP_GETTER(bool, hasBatteryFault, BatteryLevelStatusStruct)
    {
        return (btSpecObject.additionalStatus & BAS_AS_BATTERY_FAULT) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryLevelStatus, BatteryLevelStatusStruct)

    virtual bool checkSize(size_t size) override
    {
        return size > 2 && size < 8;
    }

    BVP_PARSE(BatteryLevelStatusStruct)
    {
        bool result{true};

        btSpecObject.flags = parser.parseUInt8();
        btSpecObject.powerState = parser.parseUInt16();

        if (isIdentifierPresent(btSpecObject))
        {
            btSpecObject.identifier = parser.parseUInt16();
        }

        if (isBatteryLevelPresent(btSpecObject))
        {
            result &= BatteryLevel::parse(parser, btSpecObject.batteryLevel);
        }

        if (isAdditionalStatusPresent(btSpecObject))
        {
            btSpecObject.additionalStatus = parser.parseUInt8();
        }

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "WiredExternalPowerSourceConnected: " << wiredExternalPowerSourceConnected();
        oss << ", WirelessExternalPowerSourceConnected: " << wirelessExternalPowerSourceConnected();
        oss << ", BatteryChargeState: " << batteryChargeState();
        oss << ", BatteryChargeLevel: " << batteryChargeLevel();
        oss << ", ChargingType: " << chargingType();

        if (hasChargingFault())
        {
            oss << ", ChargingFaultReason: {";
            if (isChargingFaultReasonBattery())
            {
                oss << " Battery";
            }
            if (isChargingFaultReasonExternalPowerSource())
            {
                oss << " ExternalPowerSource";
            }
            if (isChargingFaultReasonOther())
            {
                oss << " Other";
            }
            oss << " }";
        }

        if (isIdentifierPresent())
        {
            auto originalFlags = oss.flags();
            oss << ", ID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_btSpecObject.identifier;
            oss.flags(originalFlags);
        }

        if (isBatteryLevelPresent())
        {
            oss << ", BatteryLevel: " << BatteryLevel(m_btSpecObject.batteryLevel, configuration());
        }

        if (isAdditionalStatusPresent())
        {
            oss << ", ServiceRequired: " << serviceRequired();
            if (hasBatteryFault())
            {
                oss << ", BatteryFailed";
            }
        }

        if (isBatteryPresent())
        {
            oss << ", BatteryPresent";
        }
    }
};

}  // namespace bvp
