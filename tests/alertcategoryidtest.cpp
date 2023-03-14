#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct AlertCategoryIDTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(AlertCategoryIDTest, SimpleAlert)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::SimpleAlert, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::SimpleAlert, btSpecObj.categoryID);

    EXPECT_EQ("SimpleAlert", result->toString());
}

TEST_F(AlertCategoryIDTest, Email)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Email, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Email, btSpecObj.categoryID);

    EXPECT_EQ("Email", result->toString());
}

TEST_F(AlertCategoryIDTest, News)
{
    constexpr char data[] = { '\x02' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::News, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::News, btSpecObj.categoryID);

    EXPECT_EQ("News", result->toString());
}

TEST_F(AlertCategoryIDTest, Call)
{
    constexpr char data[] = { '\x03' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Call, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Call, btSpecObj.categoryID);

    EXPECT_EQ("Call", result->toString());
}

TEST_F(AlertCategoryIDTest, MissedCall)
{
    constexpr char data[] = { '\x04' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::MissedCall, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::MissedCall, btSpecObj.categoryID);

    EXPECT_EQ("MissedCall", result->toString());
}

TEST_F(AlertCategoryIDTest, SMSMMS)
{
    constexpr char data[] = { '\x05' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::SMSMMS, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::SMSMMS, btSpecObj.categoryID);

    EXPECT_EQ("SMS/MMS", result->toString());
}

TEST_F(AlertCategoryIDTest, VoiceMail)
{
    constexpr char data[] = { '\x06' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::VoiceMail, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::VoiceMail, btSpecObj.categoryID);

    EXPECT_EQ("VoiceMail", result->toString());
}

TEST_F(AlertCategoryIDTest, Schedule)
{
    constexpr char data[] = { '\x07' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Schedule, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Schedule, btSpecObj.categoryID);

    EXPECT_EQ("Schedule", result->toString());
}

TEST_F(AlertCategoryIDTest, HighPrioritizedAlert)
{
    constexpr char data[] = { '\x08' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::HighPrioritizedAlert, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::HighPrioritizedAlert, btSpecObj.categoryID);

    EXPECT_EQ("HighPrioritizedAlert", result->toString());
}

TEST_F(AlertCategoryIDTest, InstantMessage)
{
    constexpr char data[] = { '\x09' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::InstantMessage, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::InstantMessage, btSpecObj.categoryID);

    EXPECT_EQ("InstantMessage", result->toString());
}

TEST_F(AlertCategoryIDTest, Reserved)
{
    constexpr char data[] = { '\x0A' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Reserved, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Reserved, btSpecObj.categoryID);

    EXPECT_EQ("<Reserved>", result->toString());
}

TEST_F(AlertCategoryIDTest, Reserved42)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Reserved, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Reserved, btSpecObj.categoryID);

    EXPECT_EQ("<Reserved>", result->toString());
}

TEST_F(AlertCategoryIDTest, ReservedMax)
{
    constexpr char data[] = { '\xFA' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::Reserved, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::Reserved, btSpecObj.categoryID);

    EXPECT_EQ("<Reserved>", result->toString());
}

TEST_F(AlertCategoryIDTest, DefinedByService)
{
    constexpr char data[] = { '\xFB' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::DefinedByService, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::DefinedByService, btSpecObj.categoryID);

    EXPECT_EQ("<DefinedByService>", result->toString());
}

TEST_F(AlertCategoryIDTest, DefinedByServiceMax)
{
    constexpr char data[] = { '\xFF' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(AlertCategoryIDEnum::DefinedByService, result->categoryID());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(AlertCategoryIDEnum::DefinedByService, btSpecObj.categoryID);

    EXPECT_EQ("<DefinedByService>", result->toString());
}

TEST_F(AlertCategoryIDTest, TooShort)
{
    auto result = bleValueParser.make_value<AlertCategoryID>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(AlertCategoryIDTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<AlertCategoryID>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(AlertCategoryIDTest, ToString)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value(CharacteristicType::AlertCategoryID,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("SimpleAlert", result->toString());
}

}  // namespace bvp
