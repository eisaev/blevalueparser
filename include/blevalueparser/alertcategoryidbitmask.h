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
struct AlertCategoryIDBitMaskStruct
{
    uint16_t categoryIDBitMask{0};
};

class AlertCategoryIDBitMask final : public BaseValueSpec<AlertCategoryIDBitMaskStruct>
{
public:
    friend class SupportedAlertCategoryBase;

    BVP_GETTER(bool, hasSimpleAlert, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SIMPLE_ALERT) != 0;
    }

    BVP_GETTER(bool, hasEmail, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_EMAIL) != 0;
    }

    BVP_GETTER(bool, hasNews, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_NEWS) != 0;
    }

    BVP_GETTER(bool, hasCall, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_CALL) != 0;
    }

    BVP_GETTER(bool, hasMissedCall, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_MISSED_CALL) != 0;
    }

    BVP_GETTER(bool, hasSMSMMS, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SMS_MMS) != 0;
    }

    BVP_GETTER(bool, hasVoiceMail, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_VOICE_MAIL) != 0;
    }

    BVP_GETTER(bool, hasSchedule, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SCHEDULE) != 0;
    }

    BVP_GETTER(bool, hasHighPrioritizedAlert, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_HIGH_PRIORITIZED_ALERT) != 0;
    }

    BVP_GETTER(bool, hasInstantMessage, AlertCategoryIDBitMaskStruct)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_INSTANT_MESSAGE) != 0;
    }

private:
    BVP_CTORS(BaseValueSpec, AlertCategoryIDBitMask, AlertCategoryIDBitMaskStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    BVP_PARSE(AlertCategoryIDBitMaskStruct)
    {
        bool result{true};

        btSpecObject.categoryIDBitMask = parser.parseUInt16();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << "{";
        if (hasSimpleAlert())
        {
            oss << " " << AlertCategoryIDEnum::SimpleAlert;
        }
        if (hasEmail())
        {
            oss << " " << AlertCategoryIDEnum::Email;
        }
        if (hasNews())
        {
            oss << " " << AlertCategoryIDEnum::News;
        }
        if (hasCall())
        {
            oss << " " << AlertCategoryIDEnum::Call;
        }
        if (hasMissedCall())
        {
            oss << " " << AlertCategoryIDEnum::MissedCall;
        }
        if (hasSMSMMS())
        {
            oss << " " << AlertCategoryIDEnum::SMSMMS;
        }
        if (hasVoiceMail())
        {
            oss << " " << AlertCategoryIDEnum::VoiceMail;
        }
        if (hasSchedule())
        {
            oss << " " << AlertCategoryIDEnum::Schedule;
        }
        if (hasHighPrioritizedAlert())
        {
            oss << " " << AlertCategoryIDEnum::HighPrioritizedAlert;
        }
        if (hasInstantMessage())
        {
            oss << " " << AlertCategoryIDEnum::InstantMessage;
        }
        oss << " }";
    }
};

}  // namespace bvp
