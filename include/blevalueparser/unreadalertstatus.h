#pragma once

#include "basevalue.h"
#include "alertcategoryid.h"


namespace bvp
{

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
        return s_greater == btSpecObject.unreadCount;
    }

private:
    BVP_CTORS(BaseValueSpec, UnreadAlertStatus, UnreadAlertStatusStruct)

    static constexpr uint8_t s_greater = 255;
    static constexpr uint8_t s_max = s_greater - 1;

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    BVP_PARSE(UnreadAlertStatusStruct)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.unreadCount = parser.parseUInt8();

        return result;
    }

    virtual void toStringStream(std::ostringstream &oss) const override
    {
        oss <<   "Category: " << m_btSpecObject.categoryID.categoryID;

        oss << ", UnreadCount: ";
        if (isUnreadCountGreater())
        {
            oss << ">" << static_cast<int>(s_max);
        }
        else
        {
            oss << static_cast<int>(m_btSpecObject.unreadCount);
        }
    }
};

}  // namespace bvp
