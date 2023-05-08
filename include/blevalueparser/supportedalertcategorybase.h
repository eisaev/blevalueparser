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
    Struct<AlertCategoryIDBitMask> categoryIDBitMask;
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.1 Supported New Alert Category
// &&
// 3.3 Supported Unread Alert Category
template<class T>
class SupportedAlertCategoryBase : public BaseValueSpec<T>
{
public:
    BVP_GETTER(bool, isSimpleAlertSupported, T)
    {
        return AlertCategoryIDBitMask::hasSimpleAlert(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isEmailSupported, T)
    {
        return AlertCategoryIDBitMask::hasEmail(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isNewsSupported, T)
    {
        return AlertCategoryIDBitMask::hasNews(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isCallSupported, T)
    {
        return AlertCategoryIDBitMask::hasCall(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isMissedCallSupported, T)
    {
        return AlertCategoryIDBitMask::hasMissedCall(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isSMSMMSSupported, T)
    {
        return AlertCategoryIDBitMask::hasSMSMMS(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isVoiceMailSupported, T)
    {
        return AlertCategoryIDBitMask::hasVoiceMail(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isScheduleSupported, T)
    {
        return AlertCategoryIDBitMask::hasSchedule(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isHighPrioritizedAlertSupported, T)
    {
        return AlertCategoryIDBitMask::hasHighPrioritizedAlert(btSpecObject.categoryIDBitMask);
    }

    BVP_GETTER(bool, isInstantMessageSupported, T)
    {
        return AlertCategoryIDBitMask::hasInstantMessage(btSpecObject.categoryIDBitMask);
    }

protected:
    explicit SupportedAlertCategoryBase(const Configuration &configuration) :
        BaseValueSpec<T>{configuration}
    {}

    explicit SupportedAlertCategoryBase(const Struct<T> &btSpecObject, const Configuration &configuration) :
        BaseValueSpec<T>{btSpecObject, configuration}
    {}

    BVP_PARSE(T)
    {
        bool result{true};

        result &= AlertCategoryIDBitMask::parse(parser, btSpecObject.categoryIDBitMask);

        return result;
    }

    BVP_TO_STRING(T)
    {
        std::string str;

        str.append("SupportedCategories: ");
        str.append(AlertCategoryIDBitMask::toStringInternal(btSpecObject.categoryIDBitMask, configuration));

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }
};

}  // namespace bvp
