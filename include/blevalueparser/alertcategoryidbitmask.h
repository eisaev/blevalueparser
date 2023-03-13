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

    static bool hasSimpleAlert(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SIMPLE_ALERT) != 0;
    }
    bool hasSimpleAlert() const
    {
        return hasSimpleAlert(m_btSpecObject);
    }

    static bool hasEmail(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_EMAIL) != 0;
    }
    bool hasEmail() const
    {
        return hasEmail(m_btSpecObject);
    }

    static bool hasNews(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_NEWS) != 0;
    }
    bool hasNews() const
    {
        return hasNews(m_btSpecObject);
    }

    static bool hasCall(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_CALL) != 0;
    }
    bool hasCall() const
    {
        return hasCall(m_btSpecObject);
    }

    static bool hasMissedCall(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_MISSED_CALL) != 0;
    }
    bool hasMissedCall() const
    {
        return hasMissedCall(m_btSpecObject);
    }

    static bool hasSMSMMS(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SMS_MMS) != 0;
    }
    bool hasSMSMMS() const
    {
        return hasSMSMMS(m_btSpecObject);
    }

    static bool hasVoiceMail(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_VOICE_MAIL) != 0;
    }
    bool hasVoiceMail() const
    {
        return hasVoiceMail(m_btSpecObject);
    }

    static bool hasSchedule(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_SCHEDULE) != 0;
    }
    bool hasSchedule() const
    {
        return hasSchedule(m_btSpecObject);
    }

    static bool hasHighPrioritizedAlert(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_HIGH_PRIORITIZED_ALERT) != 0;
    }
    bool hasHighPrioritizedAlert() const
    {
        return hasHighPrioritizedAlert(m_btSpecObject);
    }

    static bool hasInstantMessage(const AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        return (btSpecObject.categoryIDBitMask & ACI_FLAG_INSTANT_MESSAGE) != 0;
    }
    bool hasInstantMessage() const
    {
        return hasInstantMessage(m_btSpecObject);
    }

private:
    BVP_CTORS(BaseValueSpec, AlertCategoryIDBitMask, AlertCategoryIDBitMaskStruct)

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    static bool parse(Parser &parser, AlertCategoryIDBitMaskStruct &btSpecObject)
    {
        bool result{true};

        btSpecObject.categoryIDBitMask = parser.parseUInt16();

        return result;
    }
    virtual bool parse(Parser &parser) override
    {
        return parse(parser, m_btSpecObject);
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
