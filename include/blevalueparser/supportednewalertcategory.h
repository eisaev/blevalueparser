#pragma once

#include "basevalue.h"
#include "supportedalertcategorybase.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.205 Supported New Alert Category
struct SupportedNewAlertCategoryStruct : SupportedAlertCategoryBaseStruct {};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.1 Supported New Alert Category
class SupportedNewAlertCategory final : public SupportedAlertCategoryBase
{
private:
    BVP_CTORS(SupportedAlertCategoryBase, SupportedNewAlertCategory, SupportedNewAlertCategoryStruct)
};

}  // namespace bvp
