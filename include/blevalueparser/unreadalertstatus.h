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
    static AlertCategoryIDEnum categoryID(const UnreadAlertStatusStruct &btSpecObject)
    {
        return btSpecObject.categoryID.categoryID;
    }
    AlertCategoryIDEnum categoryID() const
    {
        return categoryID(m_btSpecObject);
    }

    static uint8_t unreadCount(const UnreadAlertStatusStruct &btSpecObject)
    {
        return btSpecObject.unreadCount;
    }
    uint8_t unreadCount() const
    {
        return unreadCount(m_btSpecObject);
    }

    static bool isUnreadCountGreater(const UnreadAlertStatusStruct &btSpecObject)
    {
        return s_greater == btSpecObject.unreadCount;
    }
    bool isUnreadCountGreater() const
    {
        return isUnreadCountGreater(m_btSpecObject);
    }

private:
    BVP_CTORS(BaseValueSpec, UnreadAlertStatus, UnreadAlertStatusStruct)

    static constexpr uint8_t s_greater = 255;
    static constexpr uint8_t s_max = s_greater - 1;

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    static bool parse(Parser &parser, UnreadAlertStatusStruct &btSpecObject)
    {
        bool result{true};

        result &= AlertCategoryID::parse(parser, btSpecObject.categoryID);
        btSpecObject.unreadCount = parser.parseUInt8();

        return result;
    }
    virtual bool parse(Parser &parser) override
    {
        return parse(parser, m_btSpecObject);
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
