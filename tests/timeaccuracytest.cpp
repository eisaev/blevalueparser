#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct TimeAccuracyTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(TimeAccuracyTest, Mininum)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<TimeAccuracy>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isLarger());
    EXPECT_FALSE(result->isUnknown());
    EXPECT_EQ(0, result->accuracyMs());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(0, btSpecObj.accuracy);

    EXPECT_EQ("0ms", result->toString());
}

TEST_F(TimeAccuracyTest, Normal)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<TimeAccuracy>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isLarger());
    EXPECT_FALSE(result->isUnknown());
    EXPECT_EQ(5250, result->accuracyMs());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(42, btSpecObj.accuracy);

    EXPECT_EQ("5250ms", result->toString());
}

TEST_F(TimeAccuracyTest, Maximum)
{
    constexpr char data[] = { '\xFD' };

    auto result = bleValueParser.make_value<TimeAccuracy>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isLarger());
    EXPECT_FALSE(result->isUnknown());
    EXPECT_EQ(31625, result->accuracyMs());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(253, btSpecObj.accuracy);

    EXPECT_EQ("31625ms", result->toString());
}

TEST_F(TimeAccuracyTest, Larger)
{
    constexpr char data[] = { '\xFE' };

    auto result = bleValueParser.make_value<TimeAccuracy>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isLarger());
    EXPECT_FALSE(result->isUnknown());
    EXPECT_EQ(UINT16_MAX, result->accuracyMs());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(254, btSpecObj.accuracy);

    EXPECT_EQ(">31625ms", result->toString());
}

TEST_F(TimeAccuracyTest, Unknown)
{
    constexpr char data[] = { '\xFF' };

    auto result = bleValueParser.make_value<TimeAccuracy>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isLarger());
    EXPECT_TRUE(result->isUnknown());
    EXPECT_EQ(UINT16_MAX, result->accuracyMs());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(255, btSpecObj.accuracy);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(TimeAccuracyTest, TooShort)
{
    auto result = bleValueParser.make_value<TimeAccuracy>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(TimeAccuracyTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<TimeAccuracy>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(TimeAccuracyTest, ToString)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value(CharacteristicType::TimeAccuracy,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("125ms", result->toString());
}

}  // namespace bvp
