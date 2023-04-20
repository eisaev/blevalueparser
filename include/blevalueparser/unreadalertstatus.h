#pragma once

#include "basevalue.h"
#include "alertcategoryid.h"


namespace bvp
{

constexpr uint8_t UAS_GREATER = 255;
constexpr uint8_t UAS_MAX = UAS_GREATER - 1;

// GATT_Specification_Supplement_v8.pdf
// 3.238 Unread Alert Status
struct UnreadAlertStatusStruct
{
    AlertCategoryIDStruct categoryID;
    uint8_t unreadCount{0};
};

// ANS_SPEC_V10.pdf
// Alert Notification Service v10r00
// 3.4 Unread Alert Status
class UnreadAlertStatus final : public BaseValueSpec<UnreadAlertStatusStruct>
{
public:
    BVP_GETTER(AlertCategoryIDEnum, categoryID, UnreadAlertStatusStruct)
    {
        return btSpecObject.categoryID.categoryID;
    }

    BVP_GETTER(uint8_t, unreadCount, UnreadAlertStatusStruct)
    {
        return btSpecObject.unreadCount;
    }

    BVP_GETTER(bool, isUnreadCountGreater, UnreadAlertStatusStruct)
    {
        return UAS_GREATER == btSpecObject.unreadCount;
    }

private:
    BVP_CTORS(BaseValueSpec, UnreadAlertStatus, UnreadAlertStatusStruct)

    BVP_PARSE(UnreadAlertStatusStruct)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.unreadCount = parser.parseUInt8();

        return result;
    }

    BVP_TO_STRING(UnreadAlertStatusStruct)
    {
        std::string str;

        str.append("Category: ");
        str.append(enumToString(btSpecObject.categoryID.categoryID));

        str.append(", UnreadCount: ");
        if (isUnreadCountGreater(btSpecObject))
        {
            fmt::format_to(std::back_inserter(str), ">{}", UAS_MAX);
        }
        else
        {
            fmt::format_to(
                std::back_inserter(str),
                "{}",
                btSpecObject.unreadCount
            );
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }
};

}  // namespace bvp
