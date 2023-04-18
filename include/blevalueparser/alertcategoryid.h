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
inline std::ostream &operator<<(std::ostream &os, const AlertCategoryIDEnum value)
{
    switch (value)
    {
        case AlertCategoryIDEnum::SimpleAlert:          os << "SimpleAlert";            break;
        case AlertCategoryIDEnum::Email:                os << "Email";                  break;
        case AlertCategoryIDEnum::News:                 os << "News";                   break;
        case AlertCategoryIDEnum::Call:                 os << "Call";                   break;
        case AlertCategoryIDEnum::MissedCall:           os << "MissedCall";             break;
        case AlertCategoryIDEnum::SMSMMS:               os << "SMS/MMS";                break;
        case AlertCategoryIDEnum::VoiceMail:            os << "VoiceMail";              break;
        case AlertCategoryIDEnum::Schedule:             os << "Schedule";               break;
        case AlertCategoryIDEnum::HighPrioritizedAlert: os << "HighPrioritizedAlert";   break;
        case AlertCategoryIDEnum::InstantMessage:       os << "InstantMessage";         break;
        case AlertCategoryIDEnum::Reserved:             os << "<Reserved>";             break;
        case AlertCategoryIDEnum::DefinedByService:     os << "<DefinedByService>";     break;
    }

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
struct AlertCategoryIDStruct
{
    AlertCategoryIDEnum categoryID{AlertCategoryIDEnum::SimpleAlert};
};

class AlertCategoryID final : public BaseValueSpec<AlertCategoryIDStruct>
{
public:
    friend class NewAlert;
    friend class UnreadAlertStatus;
    friend class AlertNotificationControlPoint;

    BVP_GETTER(AlertCategoryIDEnum, categoryID, AlertCategoryIDStruct)
    {
        return btSpecObject.categoryID;
    }

private:
    BVP_CTORS(BaseValueSpec, AlertCategoryID, AlertCategoryIDStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    BVP_PARSE(AlertCategoryIDStruct)
    {
        bool result{true};

        btSpecObject.categoryID %= AlertCategoryIDEnum(parser.parseUInt8());

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << m_btSpecObject.categoryID;
    }
};

}  // namespace bvp
