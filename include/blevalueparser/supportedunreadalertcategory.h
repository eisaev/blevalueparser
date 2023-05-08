#pragma once

#include "basevalue.h"
#include "supportedalertcategorybase.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.209 Supported Unread Alert Category
BVP_STRUCT_INHERITED(SupportedUnreadAlertCategory, SupportedAlertCategoryBaseStruct) {};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.3 Supported Unread Alert Category
class SupportedUnreadAlertCategory final : public SupportedAlertCategoryBase<SupportedUnreadAlertCategory>
{
private:
    BVP_CTORS(SupportedAlertCategoryBase<SupportedUnreadAlertCategory>, SupportedUnreadAlertCategory)
};

}  // namespace bvp
