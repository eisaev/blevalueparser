#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct AlertNotificationControlPointTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(AlertNotificationControlPointTest, EnableNewIncomingAlertNotification_InstantMessage)
{
    constexpr char data[] = {
        '\x00', // commandID
        '\x09'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::InstantMessage, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::EnableNewIncomingAlertNotification, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::InstantMessage, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: EnableNewIncomingAlertNotification, Category: InstantMessage", result->toString());
}

TEST_F(AlertNotificationControlPointTest, EnableUnreadCategoryStatusNotification_HighPrioritizedAlert)
{
    constexpr char data[] = {
        '\x01', // commandID
        '\x08'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::EnableUnreadCategoryStatusNotification, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::HighPrioritizedAlert, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::EnableUnreadCategoryStatusNotification, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::HighPrioritizedAlert, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: EnableUnreadCategoryStatusNotification, Category: HighPrioritizedAlert", result->toString());
}

TEST_F(AlertNotificationControlPointTest, DisableNewIncomingAlertNotification_Schedule)
{
    constexpr char data[] = {
        '\x02', // commandID
        '\x07'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::DisableNewIncomingAlertNotification, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::Schedule, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::DisableNewIncomingAlertNotification, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::Schedule, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: DisableNewIncomingAlertNotification, Category: Schedule", result->toString());
}

TEST_F(AlertNotificationControlPointTest, DisableUnreadCategoryStatusNotification_VoiceMail)
{
    constexpr char data[] = {
        '\x03', // commandID
        '\x06'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::DisableUnreadCategoryStatusNotification, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::VoiceMail, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::DisableUnreadCategoryStatusNotification, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::VoiceMail, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: DisableUnreadCategoryStatusNotification, Category: VoiceMail", result->toString());
}

TEST_F(AlertNotificationControlPointTest, NotifyNewIncomingAlertImmediately_SMSMMS)
{
    constexpr char data[] = {
        '\x04', // commandID
        '\x05'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::NotifyNewIncomingAlertImmediately, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::SMSMMS, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::NotifyNewIncomingAlertImmediately, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::SMSMMS, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: NotifyNewIncomingAlertImmediately, Category: SMS/MMS", result->toString());
}

TEST_F(AlertNotificationControlPointTest, NotifyUnreadCategoryStatusImmediately_MissedCall)
{
    constexpr char data[] = {
        '\x05', // commandID
        '\x04'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::NotifyUnreadCategoryStatusImmediately, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::MissedCall, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::NotifyUnreadCategoryStatusImmediately, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::MissedCall, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: NotifyUnreadCategoryStatusImmediately, Category: MissedCall", result->toString());
}

TEST_F(AlertNotificationControlPointTest, Reserved_Call)
{
    constexpr char data[] = {
        '\x06', // commandID
        '\x03'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::Reserved, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::Call, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::Reserved, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::Call, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: <Reserved>, Category: Call", result->toString());
}

TEST_F(AlertNotificationControlPointTest, ReservedNormal_News)
{
    constexpr char data[] = {
        '\x2A', // commandID
        '\x02'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::Reserved, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::News, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::Reserved, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::News, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: <Reserved>, Category: News", result->toString());
}

TEST_F(AlertNotificationControlPointTest, ReservedMax_Email)
{
    constexpr char data[] = {
        '\xFF', // commandID
        '\x01'  // categoryID
    };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::Reserved, result->commandID());
    EXPECT_EQ(AlertCategoryIDEnum::Email, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertNotificationControlPointCommandIDEnum::Reserved, btSpecObj.commandID);
    EXPECT_EQ(AlertCategoryIDEnum::Email, btSpecObj.categoryID.categoryID);

    EXPECT_EQ("Command: <Reserved>, Category: Email", result->toString());
}

TEST_F(AlertNotificationControlPointTest, TooShort)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(AlertNotificationControlPointTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<AlertNotificationControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(AlertNotificationControlPointTest, ToString)
{
    constexpr char data[] = {
        '\x05', // commandID
        '\x00'  // categoryID
    };

    auto result = bleValueParser.make_value(CharacteristicType::AlertNotificationControlPoint,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Command: NotifyUnreadCategoryStatusImmediately, Category: SimpleAlert", result->toString());
}

}  // namespace bvp
