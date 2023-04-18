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
    BVP_GETTER(bool, isSimpleAlertSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasSimpleAlert(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isEmailSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasEmail(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isNewsSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasNews(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isCallSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasCall(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isMissedCallSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasMissedCall(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isSMSMMSSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasSMSMMS(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isVoiceMailSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasVoiceMail(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isScheduleSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasSchedule(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isHighPrioritizedAlertSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasHighPrioritizedAlert(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isInstantMessageSupported, SupportedAlertCategoryBaseStruct)
    {
        return AlertCategoryIDBitMask::hasInstantMessage(btSpecObject.categoryIDBitMask);
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

    BVP_PARSE(SupportedAlertCategoryBaseStruct)
    {
        bool result{true};

        result &= AlertCategoryIDBitMask::parse(parser, btSpecObject.categoryIDBitMask);

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss << "SupportedCategories: " << AlertCategoryIDBitMask(m_btSpecObject.categoryIDBitMask, configuration());
    }
};

}  // namespace bvp
