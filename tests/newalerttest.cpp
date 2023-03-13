#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct NewAlertTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(NewAlertTest, InstantMessage_New0_TextNone)
{
    constexpr char data[] = {
        '\x09', // categoryID
        '\x00'  // numberOfNewAlert
    };

    auto result = bleValueParser.make_value<NewAlert>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::InstantMessage, result->categoryID());
    EXPECT_EQ(0, result->numberOfNewAlert());
    EXPECT_EQ("", result->recentAlertBrief());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::InstantMessage, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(0, btSpecObj.numberOfNewAlert);
    EXPECT_EQ("", btSpecObj.textStringInformation);

    EXPECT_EQ("Category: InstantMessage, NumberOfNewAlert: 0, RecentAlertBrief: ''", result->toString());
}

TEST_F(NewAlertTest, HighPrioritizedAlert_NewNormal_TextNone)
{
    constexpr char data[] = {
        '\x08', // categoryID
        '\x2A'  // numberOfNewAlert
    };

    auto result = bleValueParser.make_value<NewAlert>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::HighPrioritizedAlert, result->categoryID());
    EXPECT_EQ(42, result->numberOfNewAlert());
    EXPECT_EQ("", result->recentAlertBrief());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::HighPrioritizedAlert, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(42, btSpecObj.numberOfNewAlert);
    EXPECT_EQ("", btSpecObj.textStringInformation);

    EXPECT_EQ("Category: HighPrioritizedAlert, NumberOfNewAlert: 42, RecentAlertBrief: ''", result->toString());
}

TEST_F(NewAlertTest, Schedule_NewMax_TextNormal)
{
    constexpr char data[] = {
        '\x07',                                     // categoryID
        '\xFF',                                     // numberOfNewAlert
        'S', 'o', 'm', 'e', ' ', 't', 'e', 'x', 't' // textStringInformation
    };

    auto result = bleValueParser.make_value<NewAlert>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Schedule, result->categoryID());
    EXPECT_EQ(255, result->numberOfNewAlert());
    EXPECT_EQ("Some text", result->recentAlertBrief());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Schedule, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(255, btSpecObj.numberOfNewAlert);
    EXPECT_EQ("Some text", btSpecObj.textStringInformation);

    EXPECT_EQ("Category: Schedule, NumberOfNewAlert: 255, RecentAlertBrief: 'Some text'", result->toString());
}

TEST_F(NewAlertTest, VoiceMail_New0_TextMax)
{
    constexpr char data[] = {
        '\x06',                                     // categoryID
        '\x00',                                     // numberOfNewAlert
        'S', 'o', 'm', 'e', ' ', 'v', 'e', 'r', 'y',
        ' ', 'l', 'o', 'n', 'g', ' ', 't', 'x', 't' // textStringInformation
    };

    auto result = bleValueParser.make_value<NewAlert>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::VoiceMail, result->categoryID());
    EXPECT_EQ(0, result->numberOfNewAlert());
    EXPECT_EQ("Some very long txt", result->recentAlertBrief());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::VoiceMail, btSpecObj.categoryID.categoryID);
    EXPECT_EQ(0, btSpecObj.numberOfNewAlert);
    EXPECT_EQ("Some very long txt", btSpecObj.textStringInformation);

    EXPECT_EQ("Category: VoiceMail, NumberOfNewAlert: 0, RecentAlertBrief: 'Some very long txt'", result->toString());
}

TEST_F(NewAlertTest, TooShort)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<NewAlert>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(NewAlertTest, TooLong)
{
    constexpr char data[] = {
        '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A',
        '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A',
        '\x2A'
    };

    auto result = bleValueParser.make_value<NewAlert>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(NewAlertTest, ToString)
{
    constexpr char data[] = {
        '\x05',                         // categoryID
        '\x2A',                         // numberOfNewAlert
        'D', 'o', 'n', '\'', 't', ' ',
        'p', 'a', 'n', 'i', 'c', '!'    // textStringInformation
    };

    auto result = bleValueParser.make_value(CharacteristicType::NewAlert,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Category: SMS/MMS, NumberOfNewAlert: 42, RecentAlertBrief: 'Don't panic!'", result->toString());
}

}  // namespace bvp
