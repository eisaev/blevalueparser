#pragma once

#include "basevalue.h"
#include "alertcategoryid.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.9 Alert Notification Control Point (Table 3.12)
enum class AlertNotificationControlPointCommandIDEnum : uint8_t
{
    EnableNewIncomingAlertNotification      = 0,
    EnableUnreadCategoryStatusNotification  = 1,
    DisableNewIncomingAlertNotification     = 2,
    DisableUnreadCategoryStatusNotification = 3,
    NotifyNewIncomingAlertImmediately       = 4,
    NotifyUnreadCategoryStatusImmediately   = 5,
    Reserved                                = 6  // 6–255 - Reserved for Future Use
};
inline std::string enumToString(const AlertNotificationControlPointCommandIDEnum value)
{
    std::string str;

    switch (value)
    {
        case AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification:        str = "EnableNewIncomingAlertNotification";         break;
        case AlertNotificationControlPointCommandIDEnum::EnableUnreadCategoryStatusNotification:    str = "EnableUnreadCategoryStatusNotification";     break;
        case AlertNotificationControlPointCommandIDEnum::DisableNewIncomingAlertNotification:       str = "DisableNewIncomingAlertNotification";        break;
        case AlertNotificationControlPointCommandIDEnum::DisableUnreadCategoryStatusNotification:   str = "DisableUnreadCategoryStatusNotification";    break;
        case AlertNotificationControlPointCommandIDEnum::NotifyNewIncomingAlertImmediately:         str = "NotifyNewIncomingAlertImmediately";          break;
        case AlertNotificationControlPointCommandIDEnum::NotifyUnreadCategoryStatusImmediately:     str = "NotifyUnreadCategoryStatusImmediately";      break;
        case AlertNotificationControlPointCommandIDEnum::Reserved:                                  str = "<Reserved>";                                 break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const AlertNotificationControlPointCommandIDEnum value)
{
    os << enumToString(value);
    return os;
}
inline AlertNotificationControlPointCommandIDEnum &operator%=(AlertNotificationControlPointCommandIDEnum &lhs, const AlertNotificationControlPointCommandIDEnum &rhs)
{
    lhs = AlertNotificationControlPointCommandIDEnum::Reserved;

    switch (rhs)
    {
        case AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification:
        case AlertNotificationControlPointCommandIDEnum::EnableUnreadCategoryStatusNotification:
        case AlertNotificationControlPointCommandIDEnum::DisableNewIncomingAlertNotification:
        case AlertNotificationControlPointCommandIDEnum::DisableUnreadCategoryStatusNotification:
        case AlertNotificationControlPointCommandIDEnum::NotifyNewIncomingAlertImmediately:
        case AlertNotificationControlPointCommandIDEnum::NotifyUnreadCategoryStatusImmediately:
        case AlertNotificationControlPointCommandIDEnum::Reserved:
            lhs = rhs;
            break;
        }

    return lhs;
}

// GATT_Specification_Supplement_v8.pdf
// 3.9 Alert Notification Control Point
BVP_STRUCT(AlertNotificationControlPoint)
{
    AlertNotificationControlPointCommandIDEnum commandID{AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification};
    Struct<AlertCategoryID> categoryID;
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.5 Alert Notification Control Point
class AlertNotificationControlPoint final : public BaseValueSpec<AlertNotificationControlPoint>
{
public:
    BVP_GETTER(AlertNotificationControlPointCommandIDEnum, commandID, AlertNotificationControlPoint)
    {
        return btSpecObject.commandID;
    }

    BVP_GETTER(AlertCategoryIDEnum, categoryID, AlertNotificationControlPoint)
    {
        return btSpecObject.categoryID.categoryID;
    }

private:
    BVP_CTORS(BaseValueSpec, AlertNotificationControlPoint)

    BVP_PARSE(AlertNotificationControlPoint)
    {
        bool result{true};

        btSpecObject.commandID %= AlertNotificationControlPointCommandIDEnum(parser.parseUInt8());
        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);

        return result;
    }

    BVP_TO_STRING(AlertNotificationControlPoint)
    {
        (void)configuration;
        std::string str;

        str.append("Command: ");
        str.append(enumToString(btSpecObject.commandID));

        str.append(", Category: ");
        str.append(enumToString(btSpecObject.categoryID.categoryID));

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }
};

}  // namespace bvp
