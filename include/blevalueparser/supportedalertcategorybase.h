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
    bool isSimpleAlertSupported() const
    {
        return AlertCategoryIDBitMask::hasSimpleAlert(m_btSpecObject.categoryIDBitMask);
    }

    bool isEmailSupported() const
    {
        return AlertCategoryIDBitMask::hasEmail(m_btSpecObject.categoryIDBitMask);
    }

    bool isNewsSupported() const
    {
        return AlertCategoryIDBitMask::hasNews(m_btSpecObject.categoryIDBitMask);
    }

    bool isCallSupported() const
    {
        return AlertCategoryIDBitMask::hasCall(m_btSpecObject.categoryIDBitMask);
    }

    bool isMissedCallSupported() const
    {
        return AlertCategoryIDBitMask::hasMissedCall(m_btSpecObject.categoryIDBitMask);
    }

    bool isSMSMMSSupported() const
    {
        return AlertCategoryIDBitMask::hasSMSMMS(m_btSpecObject.categoryIDBitMask);
    }

    bool isVoiceMailSupported() const
    {
        return AlertCategoryIDBitMask::hasVoiceMail(m_btSpecObject.categoryIDBitMask);
    }

    bool isScheduleSupported() const
    {
        return AlertCategoryIDBitMask::hasSchedule(m_btSpecObject.categoryIDBitMask);
    }

    bool isHighPrioritizedAlertSupported() const
    {
        return AlertCategoryIDBitMask::hasHighPrioritizedAlert(m_btSpecObject.categoryIDBitMask);
    }

    bool isInstantMessageSupported() const
    {
        return AlertCategoryIDBitMask::hasInstantMessage(m_btSpecObject.categoryIDBitMask);
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
        oss << "SupportedCategoryIDs: " << AlertCategoryIDBitMask(m_btSpecObject.categoryIDBitMask, configuration);
    }
};

}  // namespace bvp
