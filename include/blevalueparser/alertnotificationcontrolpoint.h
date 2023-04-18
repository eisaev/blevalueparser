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
inline std::ostream &operator<<(std::ostream &os, const AlertNotificationControlPointCommandIDEnum value)
{
    switch (value)
    {
        case AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification:        os << "EnableNewIncomingAlertNotification";         break;
        case AlertNotificationControlPointCommandIDEnum::EnableUnreadCategoryStatusNotification:    os << "EnableUnreadCategoryStatusNotification";     break;
        case AlertNotificationControlPointCommandIDEnum::DisableNewIncomingAlertNotification:       os << "DisableNewIncomingAlertNotification";        break;
        case AlertNotificationControlPointCommandIDEnum::DisableUnreadCategoryStatusNotification:   os << "DisableUnreadCategoryStatusNotification";    break;
        case AlertNotificationControlPointCommandIDEnum::NotifyNewIncomingAlertImmediately:         os << "NotifyNewIncomingAlertImmediately";          break;
        case AlertNotificationControlPointCommandIDEnum::NotifyUnreadCategoryStatusImmediately:     os << "NotifyUnreadCategoryStatusImmediately";      break;
        case AlertNotificationControlPointCommandIDEnum::Reserved:                                  os << "<Reserved>";                                 break;
    }

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
struct AlertNotificationControlPointStruct
{
    AlertNotificationControlPointCommandIDEnum commandID{AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification};
    AlertCategoryIDStruct categoryID;
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.5 Alert Notification Control Point
class AlertNotificationControlPoint final : public BaseValueSpec<AlertNotificationControlPointStruct>
{
public:
    BVP_GETTER(AlertNotificationControlPointCommandIDEnum, commandID, AlertNotificationControlPointStruct)
    {
        return btSpecObject.commandID;
    }

    BVP_GETTER(AlertCategoryIDEnum, categoryID, AlertNotificationControlPointStruct)
    {
        return btSpecObject.categoryID.categoryID;
    }

private:
    BVP_CTORS(BaseValueSpec, AlertNotificationControlPoint, AlertNotificationControlPointStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    BVP_PARSE(AlertNotificationControlPointStruct)
    {
        bool result{true};

        btSpecObject.commandID %= AlertNotificationControlPointCommandIDEnum(parser.parseUInt8());
        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "Command: " << m_btSpecObject.commandID;
        oss << ", Category: " << m_btSpecObject.categoryID.categoryID;
    }
};

}  // namespace bvp
