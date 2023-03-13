#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct UnreadAlertStatusTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(UnreadAlertStatusTest, SimpleAlert_UnreadGreater)
{
    constexpr char data[] = {
        '\x00', // categoryID
        '\xFF'  // unreadCount
    };

    auto result = bleValueParser.make_value<UnreadAlertStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::SimpleAlert, result->categoryID());
    EXPECT_EQ(255, result->unreadCount());
    EXPECT_TRUE(result->isUnreadCountGreater());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::SimpleAlert, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(255, btSpecObj.unreadCount);

    EXPECT_EQ("Category: SimpleAlert, UnreadCount: >254", result->toString());
}

TEST_F(UnreadAlertStatusTest, Email_UnreadMax)
{
    constexpr char data[] = {
        '\x01', // categoryID
        '\xFE'  // unreadCount
    };

    auto result = bleValueParser.make_value<UnreadAlertStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Email, result->categoryID());
    EXPECT_EQ(254, result->unreadCount());
    EXPECT_FALSE(result->isUnreadCountGreater());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Email, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(254, btSpecObj.unreadCount);

    EXPECT_EQ("Category: Email, UnreadCount: 254", result->toString());
}

TEST_F(UnreadAlertStatusTest, News_UnreadNormal)
{
    constexpr char data[] = {
        '\x02', // categoryID
        '\x2A'  // unreadCount
    };

    auto result = bleValueParser.make_value<UnreadAlertStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::News, result->categoryID());
    EXPECT_EQ(42, result->unreadCount());
    EXPECT_FALSE(result->isUnreadCountGreater());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::News, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(42, btSpecObj.unreadCount);

    EXPECT_EQ("Category: News, UnreadCount: 42", result->toString());
}

TEST_F(UnreadAlertStatusTest, Call_Unread0)
{
    constexpr char data[] = {
        '\x03', // categoryID
        '\x00'  // unreadCount
    };

    auto result = bleValueParser.make_value<UnreadAlertStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Call, result->categoryID());
    EXPECT_EQ(0, result->unreadCount());
    EXPECT_FALSE(result->isUnreadCountGreater());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Call, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(0, btSpecObj.unreadCount);

    EXPECT_EQ("Category: Call, UnreadCount: 0", result->toString());
}

TEST_F(UnreadAlertStatusTest, TooShort)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<UnreadAlertStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(UnreadAlertStatusTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<UnreadAlertStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(UnreadAlertStatusTest, ToString)
{
    constexpr char data[] = {
        '\x04', // categoryID
        '\x2A'  // unreadCount
    };

    auto result = bleValueParser.make_value(CharacteristicType::UnreadAlertStatus,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Category: MissedCall, UnreadCount: 42", result->toString());
}

}  // namespace bvp
