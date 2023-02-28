#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

class DateUTCTest : public testing::Test
{
protected:
    explicit DateUTCTest() {}
    virtual ~DateUTCTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(DateUTCTest, Zero)
{
    constexpr char data[] = { '\x00', '\x00', '\x00' };

    auto result = bleValueParser.make_value<DateUTC>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(0, result->date());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(0, btSpecObj.date);

    EXPECT_EQ("01.01.1970 (0 seconds since 1 Jan 1970)", result->toString());
}

TEST_F(DateUTCTest, Nowadays)
{
    constexpr char data[] = { '\xD8', '\x4B', '\x00' };

    auto result = bleValueParser.make_value<DateUTC>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(1677542400, result->date());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(19416, btSpecObj.date);

    EXPECT_EQ("28.02.2023 (1677542400 seconds since 1 Jan 1970)", result->toString());
}

TEST_F(DateUTCTest, Epochalypse)
{
    constexpr char data[] = { '\xFF', '\xFF', '\xFF' };

    auto result = bleValueParser.make_value<DateUTC>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2147397248, result->date());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(16777215, btSpecObj.date);

    EXPECT_EQ("18.01.2038 (2147397248 seconds since 1 Jan 1970)", result->toString());
}

TEST_F(DateUTCTest, TooShort)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<DateUTC>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DateUTCTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<DateUTC>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DateUTCTest, ToString)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value(CharacteristicType::DateUTC,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("22.01.2050 (2526437120 seconds since 1 Jan 1970)", result->toString());
}

}  // namespace bvp
