#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct EstimatedServiceDateTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(EstimatedServiceDateTest, Zero)
{
    constexpr char data[] = { '\x00', '\x00', '\x00' };

    auto result = bleValueParser.make_value<EstimatedServiceDate>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(0, result->date());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(0, btSpecObj.estimatedServiceDate.date);

    EXPECT_EQ("01.01.1970 (0 seconds since 1 Jan 1970)", result->toString());
}

TEST_F(EstimatedServiceDateTest, Nowadays)
{
    constexpr char data[] = { '\xD8', '\x4B', '\x00' };

    auto result = bleValueParser.make_value<EstimatedServiceDate>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(1677542400, result->date());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(19416, btSpecObj.estimatedServiceDate.date);

    EXPECT_EQ("28.02.2023 (1677542400 seconds since 1 Jan 1970)", result->toString());
}

TEST_F(EstimatedServiceDateTest, Epochalypse)
{
    constexpr char data[] = { '\xFF', '\xFF', '\xFF' };

    auto result = bleValueParser.make_value<EstimatedServiceDate>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2147397248, result->date());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(16777215, btSpecObj.estimatedServiceDate.date);

    EXPECT_EQ("18.01.2038 (2147397248 seconds since 1 Jan 1970)", result->toString());
}

TEST_F(EstimatedServiceDateTest, TooShort)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<EstimatedServiceDate>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(EstimatedServiceDateTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<EstimatedServiceDate>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(EstimatedServiceDateTest, ToString)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value(CharacteristicType::EstimatedServiceDate,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("22.01.2050 (2526437120 seconds since 1 Jan 1970)", result->toString());
}

}  // namespace bvp
