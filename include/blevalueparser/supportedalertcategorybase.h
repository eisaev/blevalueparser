#pragma once

#include "basevalue.h"
#include "alertcategoryidbitmask.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.205 Supported New Alert Category
// and
// 3.209 Supported Unread Alert Category
struct SupportedAlertCategoryBaseStruct
{
    AlertCategoryIDBitMaskStruct categoryIDBitMask;
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.1 Supported New Alert Category
// &&
// 3.3 Supported Unread Alert Category
class SupportedAlertCategoryBase : public BaseValueSpec<SupportedAlertCategoryBaseStruct>
{
public:
    static bool isSimpleAlertSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasSimpleAlert(btSpecObject.categoryIDBitMask);
    }
    bool isSimpleAlertSupported() const
    {
        return isSimpleAlertSupported(m_btSpecObject);
    }

    static bool isEmailSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasEmail(btSpecObject.categoryIDBitMask);
    }
    bool isEmailSupported() const
    {
        return isEmailSupported(m_btSpecObject);
    }

    static bool isNewsSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasNews(btSpecObject.categoryIDBitMask);
    }
    bool isNewsSupported() const
    {
        return isNewsSupported(m_btSpecObject);
    }

    static bool isCallSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasCall(btSpecObject.categoryIDBitMask);
    }
    bool isCallSupported() const
    {
        return isCallSupported(m_btSpecObject);
    }

    static bool isMissedCallSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasMissedCall(btSpecObject.categoryIDBitMask);
    }
    bool isMissedCallSupported() const
    {
        return isMissedCallSupported(m_btSpecObject);
    }

    static bool isSMSMMSSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasSMSMMS(btSpecObject.categoryIDBitMask);
    }
    bool isSMSMMSSupported() const
    {
        return isSMSMMSSupported(m_btSpecObject);
    }

    static bool isVoiceMailSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasVoiceMail(btSpecObject.categoryIDBitMask);
    }
    bool isVoiceMailSupported() const
    {
        return isVoiceMailSupported(m_btSpecObject);
    }

    static bool isScheduleSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasSchedule(btSpecObject.categoryIDBitMask);
    }
    bool isScheduleSupported() const
    {
        return isScheduleSupported(m_btSpecObject);
    }

    static bool isHighPrioritizedAlertSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasHighPrioritizedAlert(btSpecObject.categoryIDBitMask);
    }
    bool isHighPrioritizedAlertSupported() const
    {
        return isHighPrioritizedAlertSupported(m_btSpecObject);
    }

    static bool isInstantMessageSupported(const SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        return AlertCategoryIDBitMask::hasInstantMessage(btSpecObject.categoryIDBitMask);
    }
    bool isInstantMessageSupported() const
    {
        return isInstantMessageSupported(m_btSpecObject);
    }

protected:
    explicit SupportedAlertCategoryBase(const Configuration &configuration) :
        BaseValueSpec{configuration}
    {}

    explicit SupportedAlertCategoryBase(const SupportedAlertCategoryBaseStruct &btSpecObject, const Configuration &configuration) :
        BaseValueSpec{btSpecObject, configuration}
    {}

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    static bool parse(Parser &parser, SupportedAlertCategoryBaseStruct &btSpecObject)
    {
        bool result{true};

        result &= AlertCategoryIDBitMask::parse(parser, btSpecObject.categoryIDBitMask);

        return result;
    }
    virtual bool parse(Parser &parser) override
    {
        return parse(parser, m_btSpecObject);
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << "SupportedCategories: " << AlertCategoryIDBitMask(m_btSpecObject.categoryIDBitMask, configuration);
    }
};

}  // namespace bvp
