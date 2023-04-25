#pragma once

#include "basevalue.h"
#include "alertcategoryid.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.7.1 Category ID Bit Mask field
constexpr uint16_t ACI_FLAG_SIMPLE_ALERT            = 1 << static_cast<int>(AlertCategoryIDEnum::SimpleAlert);
constexpr uint16_t ACI_FLAG_EMAIL                   = 1 << static_cast<int>(AlertCategoryIDEnum::Email);
constexpr uint16_t ACI_FLAG_NEWS                    = 1 << static_cast<int>(AlertCategoryIDEnum::News);
constexpr uint16_t ACI_FLAG_CALL                    = 1 << static_cast<int>(AlertCategoryIDEnum::Call);
constexpr uint16_t ACI_FLAG_MISSED_CALL             = 1 << static_cast<int>(AlertCategoryIDEnum::MissedCall);
constexpr uint16_t ACI_FLAG_SMS_MMS                 = 1 << static_cast<int>(AlertCategoryIDEnum::SMSMMS);
constexpr uint16_t ACI_FLAG_VOICE_MAIL              = 1 << static_cast<int>(AlertCategoryIDEnum::VoiceMail);
constexpr uint16_t ACI_FLAG_SCHEDULE                = 1 << static_cast<int>(AlertCategoryIDEnum::Schedule);
constexpr uint16_t ACI_FLAG_HIGH_PRIORITIZED_ALERT  = 1 << static_cast<int>(AlertCategoryIDEnum::HighPrioritizedAlert);
constexpr uint16_t ACI_FLAG_INSTANT_MESSAGE         = 1 << static_cast<int>(AlertCategoryIDEnum::InstantMessage);
constexpr uint16_t ACI_FLAG_RESERVED1               = 1 << 10;
constexpr uint16_t ACI_FLAG_RESERVED2               = 1 << 11;
constexpr uint16_t ACI_FLAG_RESERVED3               = 1 << 12;
constexpr uint16_t ACI_FLAG_RESERVED4               = 1 << 13;
constexpr uint16_t ACI_FLAG_RESERVED5               = 1 << 14;
constexpr uint16_t ACI_FLAG_RESERVED6               = 1 << 15;

// GATT_Specification_Supplement_v8.pdf
// 3.7 Alert Category ID Bit Mask
BVP_STRUCT(AlertCategoryIDBitMask)
{
    uint16_t categoryIDBitMask{0};
};

class AlertCategoryIDBitMask final : public BaseValueSpec<AlertCategoryIDBitMask>
{
public:
    template<class T>
    friend class SupportedAlertCategoryBase;

    BVP_GETTER(bool, hasSimpleAlert, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SIMPLE_ALERT) != 0;
    }

    BVP_GETTER(bool, hasEmail, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_EMAIL) != 0;
    }

    BVP_GETTER(bool, hasNews, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_NEWS) != 0;
    }

    BVP_GETTER(bool, hasCall, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_CALL) != 0;
    }

    BVP_GETTER(bool, hasMissedCall, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_MISSED_CALL) != 0;
    }

    BVP_GETTER(bool, hasSMSMMS, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SMS_MMS) != 0;
    }

    BVP_GETTER(bool, hasVoiceMail, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_VOICE_MAIL) != 0;
    }

    BVP_GETTER(bool, hasSchedule, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SCHEDULE) != 0;
    }

    BVP_GETTER(bool, hasHighPrioritizedAlert, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_HIGH_PRIORITIZED_ALERT) != 0;
    }

    BVP_GETTER(bool, hasInstantMessage, AlertCategoryIDBitMask)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_INSTANT_MESSAGE) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, AlertCategoryIDBitMask)

    BVP_PARSE(AlertCategoryIDBitMask)
    {
        bool result{true};

        btSpecObject.categoryIDBitMask = parser.parseUInt16();

        return result;
    }

    BVP_TO_STRING(AlertCategoryIDBitMask)
    {
        (void)configuration;
        std::string str;

        str.append("{");
        if (hasSimpleAlert(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::SimpleAlert));
        }
        if (hasEmail(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::Email));
        }
        if (hasNews(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::News));
        }
        if (hasCall(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::Call));
        }
        if (hasMissedCall(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::MissedCall));
        }
        if (hasSMSMMS(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::SMSMMS));
        }
        if (hasVoiceMail(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::VoiceMail));
        }
        if (hasSchedule(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::Schedule));
        }
        if (hasHighPrioritizedAlert(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::HighPrioritizedAlert));
        }
        if (hasInstantMessage(btSpecObject))
        {
            str.append(" ");
            str.append(enumToString(AlertCategoryIDEnum::InstantMessage));
        }
        str.append(" }");

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }
};

}  // namespace bvp
