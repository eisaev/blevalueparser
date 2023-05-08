#pragma once

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
inline std::string enumToString(const ExternalPowerSourceConnectedEnum value)
{
    std::string str;

    switch (value)
    {
        case ExternalPowerSourceConnectedEnum::No:          str = "No";         break;
        case ExternalPowerSourceConnectedEnum::Yes:         str = "Yes";        break;
        case ExternalPowerSourceConnectedEnum::Unknown:     str = "<Unknown>";  break;
        case ExternalPowerSourceConnectedEnum::Reserved:    str = "<Reserved>"; break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const ExternalPowerSourceConnectedEnum value)
{
    os << enumToString(value);
    return os;
}

enum class BatteryChargeStateEnum
{
    Unknown             = 0,
    Charging            = 1,
    DischargingActive   = 2,
    DischargingInactive = 3
};
inline std::string enumToString(const BatteryChargeStateEnum value)
{
    std::string str;

    switch (value)
    {
        case BatteryChargeStateEnum::Unknown:               str = "<Unknown>";              break;
        case BatteryChargeStateEnum::Charging:              str = "Charging";               break;
        case BatteryChargeStateEnum::DischargingActive:     str = "DischargingActive";      break;
        case BatteryChargeStateEnum::DischargingInactive:   str = "DischargingInactive";    break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const BatteryChargeStateEnum value)
{
    os << enumToString(value);
    return os;
}

enum class BatteryChargeLevelEnum
{
    Unknown     = 0,
    Good        = 1,
    Low         = 2,
    Critical    = 3
};
inline std::string enumToString(BatteryChargeLevelEnum value)
{
    std::string str;

    switch (value) {
        case BatteryChargeLevelEnum::Unknown:   str = "<Unknown>";  break;
        case BatteryChargeLevelEnum::Good:      str = "Good";       break;
        case BatteryChargeLevelEnum::Low:       str = "Low";        break;
        case BatteryChargeLevelEnum::Critical:  str = "Critical";   break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const BatteryChargeLevelEnum value)
{
    os << enumToString(value);
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
inline std::string enumToString(const ChargingTypeEnum value)
{
    std::string str;

    switch (value) {
        case ChargingTypeEnum::UnknownOrNotCharging:    str = "UnknownOrNotCharging";   break;
        case ChargingTypeEnum::ConstantCurrent:         str = "ConstantCurrent";        break;
        case ChargingTypeEnum::ConstantVoltage:         str = "ConstantVoltage";        break;
        case ChargingTypeEnum::Trickle:                 str = "Trickle";                break;
        case ChargingTypeEnum::Float:                   str = "Float";                  break;
        case ChargingTypeEnum::Reserved1:               str = "<Reserved1>";            break;
        case ChargingTypeEnum::Reserved2:               str = "<Reserved2>";            break;
        case ChargingTypeEnum::Reserved3:               str = "<Reserved3>";            break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const ChargingTypeEnum value)
{
    os << enumToString(value);
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
inline std::string enumToString(const ServiceRequiredEnum value)
{
    std::string str;

    switch (value) {
        case ServiceRequiredEnum::False:    str = "False";      break;
        case ServiceRequiredEnum::True:     str = "True";       break;
        case ServiceRequiredEnum::Unknown:  str = "<Unknown>";  break;
        case ServiceRequiredEnum::Reserved: str = "<Reserved>"; break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const ServiceRequiredEnum value)
{
    os << enumToString(value);
    return os;
}

// GATT_Specification_Supplement_v8.pdf
// 3.28 Battery Level Status
BVP_STRUCT(BatteryLevelStatus)
{
    uint8_t flags{0};
    uint16_t powerState{0};
    uint16_t identifier{0};
    Struct<BatteryLevel> batteryLevel;
    uint8_t additionalStatus{0};
};

// BAS_V1.1.pdf
// Battery Service v1.1
// 3.2 Battery Level Status
class BatteryLevelStatus final : public BaseValueSpec<BatteryLevelStatus>
{
public:
    BVP_GETTER(bool, isIdentifierPresent, BatteryLevelStatus)
    {
        return (btSpecObject.flags & BAS_FLAG_IDENTIFIER_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryLevelPresent, BatteryLevelStatus)
    {
        return (btSpecObject.flags & BAS_FLAG_BATTERY_LEVEL_PRESENT) != 0;
    }

    BVP_GETTER(bool, isAdditionalStatusPresent, BatteryLevelStatus)
    {
        return (btSpecObject.flags & BAS_FLAG_ADDITIONAL_STATUS_PRESENT) != 0;
    }

    BVP_GETTER(bool, isBatteryPresent, BatteryLevelStatus)
    {
        return (btSpecObject.powerState & BAS_PS_BATTERY_PRESENT) != 0;
    }

    BVP_GETTER(ExternalPowerSourceConnectedEnum, wiredExternalPowerSourceConnected, BatteryLevelStatus)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED0) +
            (btSpecObject.powerState & BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED1);
        value = value >> BAS_PS_WIRED_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT;

        return ExternalPowerSourceConnectedEnum(value);
    }

    BVP_GETTER(ExternalPowerSourceConnectedEnum, wirelessExternalPowerSourceConnected, BatteryLevelStatus)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED0) +
            (btSpecObject.powerState & BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED1);
        value = value >> BAS_PS_WIRELESS_EXTERNAL_POWER_SOURCE_CONNECTED_SHIFT;

        return ExternalPowerSourceConnectedEnum(value);
    }

    BVP_GETTER(BatteryChargeStateEnum, batteryChargeState, BatteryLevelStatus)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_STATE0) +
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_STATE1);
        value = value >> BAS_PS_BATTERY_CHARGE_STATE_SHIFT;

        return BatteryChargeStateEnum(value);
    }

    BVP_GETTER(BatteryChargeLevelEnum, batteryChargeLevel, BatteryLevelStatus)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_LEVEL0) +
            (btSpecObject.powerState & BAS_PS_BATTERY_CHARGE_LEVEL1);
        value = value >> BAS_PS_BATTERY_CHARGE_LEVEL_SHIFT;

        return BatteryChargeLevelEnum(value);
    }

    BVP_GETTER(ChargingTypeEnum, chargingType, BatteryLevelStatus)
    {
        uint16_t value =
            (btSpecObject.powerState & BAS_PS_CHARGING_TYPE0) +
            (btSpecObject.powerState & BAS_PS_CHARGING_TYPE1) +
            (btSpecObject.powerState & BAS_PS_CHARGING_TYPE2);
        value = value >> BAS_PS_CHARGING_TYPE_SHIFT;

        return ChargingTypeEnum(value);
    }

    BVP_GETTER(bool, isChargingFaultReasonBattery, BatteryLevelStatus)
    {
        return (btSpecObject.powerState & BAS_PS_CHARGING_FAULT_REASON_BATTERY) != 0;
    }

    BVP_GETTER(bool, isChargingFaultReasonExternalPowerSource, BatteryLevelStatus)
    {
        return (btSpecObject.powerState & BAS_PS_CHARGING_FAULT_REASON_EXTERNAL_POWER_SOURCE) != 0;
    }

    BVP_GETTER(bool, isChargingFaultReasonOther, BatteryLevelStatus)
    {
        return (btSpecObject.powerState & BAS_PS_CHARGING_FAULT_REASON_OTHER) != 0;
    }

    BVP_GETTER(bool, hasChargingFault, BatteryLevelStatus)
    {
        return
            isChargingFaultReasonBattery(btSpecObject) ||
            isChargingFaultReasonExternalPowerSource(btSpecObject) ||
            isChargingFaultReasonOther(btSpecObject);
    }

    BVP_GETTER(uint16_t, identifier, BatteryLevelStatus)
    {
        return btSpecObject.identifier;
    }

    BVP_GETTER(uint8_t, batteryLevel, BatteryLevelStatus)
    {
        return btSpecObject.batteryLevel.batteryLevel;
    }

    BVP_GETTER(ServiceRequiredEnum, serviceRequired, BatteryLevelStatus)
    {
        uint8_t value =
            (btSpecObject.additionalStatus & BAS_AS_SERVICE_REQUIRED0) +
            (btSpecObject.additionalStatus & BAS_AS_SERVICE_REQUIRED1);
        value = value >> BAS_AS_SERVICE_REQUIRED_SHIFT;

        return ServiceRequiredEnum(value);
    }

    BVP_GETTER(bool, hasBatteryFault, BatteryLevelStatus)
    {
        return (btSpecObject.additionalStatus & BAS_AS_BATTERY_FAULT) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, BatteryLevelStatus)

    BVP_PARSE(BatteryLevelStatus)
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

    BVP_TO_STRING(BatteryLevelStatus)
    {
        std::string str;

        str.append("WiredExternalPowerSourceConnected: ");
        str.append(enumToString(wiredExternalPowerSourceConnected(btSpecObject)));

        str.append(", WirelessExternalPowerSourceConnected: ");
        str.append(enumToString(wirelessExternalPowerSourceConnected(btSpecObject)));

        str.append(", BatteryChargeState: ");
        str.append(enumToString(batteryChargeState(btSpecObject)));

        str.append(", BatteryChargeLevel: ");
        str.append(enumToString(batteryChargeLevel(btSpecObject)));

        str.append(", ChargingType: ");
        str.append(enumToString(chargingType(btSpecObject)));

        if (hasChargingFault(btSpecObject))
        {
            str.append(", ChargingFaultReason: {");
            if (isChargingFaultReasonBattery(btSpecObject))
            {
                str.append(" Battery");
            }
            if (isChargingFaultReasonExternalPowerSource(btSpecObject))
            {
                str.append(" ExternalPowerSource");
            }
            if (isChargingFaultReasonOther(btSpecObject))
            {
                str.append(" Other");
            }
            str.append(" }");
        }

        if (isIdentifierPresent(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                // TODO: try to replace by local implementation (see HexString)
                ", ID: 0x{:04X}",
                btSpecObject.identifier
            );
        }

        if (isBatteryLevelPresent(btSpecObject))
        {
            str.append(", BatteryLevel: ");
            str.append(BatteryLevel::toStringInternal(btSpecObject.batteryLevel, configuration));
        }

        if (isAdditionalStatusPresent(btSpecObject))
        {
            str.append(", ServiceRequired: ");
            str.append(enumToString(serviceRequired(btSpecObject)));
            if (hasBatteryFault(btSpecObject))
            {
                str.append(", BatteryFailed");
            }
        }

        if (isBatteryPresent(btSpecObject))
        {
            str.append(", BatteryPresent");
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size > 2 && size < 8;
    }
};

}  // namespace bvp
