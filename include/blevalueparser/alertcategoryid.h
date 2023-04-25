#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.6.1 Category ID field
enum class AlertCategoryIDEnum : uint8_t
{
    SimpleAlert             = 0,
    Email                   = 1,
    News                    = 2,
    Call                    = 3,
    MissedCall              = 4,
    SMSMMS                  = 5,
    VoiceMail               = 6,
    Schedule                = 7,
    HighPrioritizedAlert    = 8,
    InstantMessage          = 9,
    Reserved                = 10,  // 10–250 - Reserved for Future Use
    DefinedByService        = 251  // 251–255 - Defined by Service Specification
};
inline std::string enumToString(const AlertCategoryIDEnum value)
{
    std::string str;

    switch (value)
    {
        case AlertCategoryIDEnum::SimpleAlert:          str = "SimpleAlert";            break;
        case AlertCategoryIDEnum::Email:                str = "Email";                  break;
        case AlertCategoryIDEnum::News:                 str = "News";                   break;
        case AlertCategoryIDEnum::Call:                 str = "Call";                   break;
        case AlertCategoryIDEnum::MissedCall:           str = "MissedCall";             break;
        case AlertCategoryIDEnum::SMSMMS:               str = "SMS/MMS";                break;
        case AlertCategoryIDEnum::VoiceMail:            str = "VoiceMail";              break;
        case AlertCategoryIDEnum::Schedule:             str = "Schedule";               break;
        case AlertCategoryIDEnum::HighPrioritizedAlert: str = "HighPrioritizedAlert";   break;
        case AlertCategoryIDEnum::InstantMessage:       str = "InstantMessage";         break;
        case AlertCategoryIDEnum::Reserved:             str = "<Reserved>";             break;
        case AlertCategoryIDEnum::DefinedByService:     str = "<DefinedByService>";     break;
    }

    return str;
}
inline std::ostream &operator<<(std::ostream &os, const AlertCategoryIDEnum value)
{
    os << enumToString(value);
    return os;
}
inline AlertCategoryIDEnum &operator%=(AlertCategoryIDEnum &lhs, const AlertCategoryIDEnum &rhs)
{
    if (rhs > AlertCategoryIDEnum::DefinedByService)
    {
        lhs = AlertCategoryIDEnum::DefinedByService;
    }
    else
    {
        lhs = AlertCategoryIDEnum::Reserved;
    }

    switch (rhs)
    {
        case AlertCategoryIDEnum::SimpleAlert:
        case AlertCategoryIDEnum::Email:
        case AlertCategoryIDEnum::News:
        case AlertCategoryIDEnum::Call:
        case AlertCategoryIDEnum::MissedCall:
        case AlertCategoryIDEnum::SMSMMS:
        case AlertCategoryIDEnum::VoiceMail:
        case AlertCategoryIDEnum::Schedule:
        case AlertCategoryIDEnum::HighPrioritizedAlert:
        case AlertCategoryIDEnum::InstantMessage:
        case AlertCategoryIDEnum::Reserved:
        case AlertCategoryIDEnum::DefinedByService:
            lhs = rhs;
            break;
        }

    return lhs;
}

// GATT_Specification_Supplement_v8.pdf
// 3.6 Alert Category ID
BVP_STRUCT(AlertCategoryID)
{
    AlertCategoryIDEnum categoryID{AlertCategoryIDEnum::SimpleAlert};
};

class AlertCategoryID final : public BaseValueSpec<AlertCategoryID>
{
public:
    friend class NewAlert;
    friend class UnreadAlertStatus;
    friend class AlertNotificationControlPoint;

    BVP_GETTER(AlertCategoryIDEnum, categoryID, AlertCategoryID)
    {
        return btSpecObject.categoryID;
    }

private:
    BVP_CTORS(BaseValueSpec, AlertCategoryID)

    BVP_PARSE(AlertCategoryID)
    {
        bool result{true};

        btSpecObject.categoryID %= AlertCategoryIDEnum(parser.parseUInt8());

        return result;
    }

    BVP_TO_STRING(AlertCategoryID)
    {
        (void)configuration;
        return enumToString(btSpecObject.categoryID);
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }
};

}  // namespace bvp
