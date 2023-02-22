#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

class TimeZoneTest : public testing::Test
{
protected:
    explicit TimeZoneTest() {}
    virtual ~TimeZoneTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(TimeZoneTest, Unknown)
{
    constexpr char data[] = { char(-128) };

    auto result = bleValueParser.make_value<TimeZone>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Unknown, result->timeZone());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Unknown, btSpecObj.timeZone);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(TimeZoneTest, Unreal)
{
    constexpr char data[] = { 57 };

    auto result = bleValueParser.make_value<TimeZone>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Unknown, result->timeZone());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Unknown, btSpecObj.timeZone);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(TimeZoneTest, Plus0)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<TimeZone>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Plus0, result->timeZone());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Plus0, btSpecObj.timeZone);

    EXPECT_EQ("0", result->toString());
}

TEST_F(TimeZoneTest, Minus48)
{
    constexpr char data[] = { '\xD0' };

    auto result = bleValueParser.make_value<TimeZone>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Minus48, result->timeZone());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Minus48, btSpecObj.timeZone);

    EXPECT_EQ("-48", result->toString());
}

TEST_F(TimeZoneTest, Plus56)
{
    constexpr char data[] = { '\x38' };

    auto result = bleValueParser.make_value<TimeZone>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Plus56, result->timeZone());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Plus56, btSpecObj.timeZone);

    EXPECT_EQ("56", result->toString());
}

TEST_F(TimeZoneTest, TooShort)
{
    auto result = bleValueParser.make_value<TimeZone>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(TimeZoneTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<TimeZone>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(TimeZoneTest, ToString)
{
    constexpr char data[] = { char(-42) };

    auto result = bleValueParser.make_value(CharacteristicType::TimeZone,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("-42", result->toString());
}

}  // namespace bvp
