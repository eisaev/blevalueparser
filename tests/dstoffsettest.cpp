#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

class DSTOffsetTest : public testing::Test
{
protected:
    explicit DSTOffsetTest() {}
    virtual ~DSTOffsetTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(DSTOffsetTest, Unknown)
{
    constexpr char data[] = { '\xFF' };

    auto result = bleValueParser.make_value<DSTOffset>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DSTOffsetEnum::Unknown, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DSTOffsetEnum::Unknown, btSpecObj.dstOffset);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(DSTOffsetTest, Unreal)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<DSTOffset>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DSTOffsetEnum::Unknown, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DSTOffsetEnum::Unknown, btSpecObj.dstOffset);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(DSTOffsetTest, 1h)
{
    constexpr char data[] = { '\x04' };

    auto result = bleValueParser.make_value<DSTOffset>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DSTOffsetEnum::DaylightTime1h, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DSTOffsetEnum::DaylightTime1h, btSpecObj.dstOffset);

    EXPECT_EQ("Daylight Time (+1h)", result->toString());
}

TEST_F(DSTOffsetTest, 0_5h)
{
    constexpr char data[] = { '\x02' };

    auto result = bleValueParser.make_value<DSTOffset>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DSTOffsetEnum::HalfAnHourDaylightTime0_5h, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DSTOffsetEnum::HalfAnHourDaylightTime0_5h, btSpecObj.dstOffset);

    EXPECT_EQ("Half an Hour Daylight Time (+0.5h)", result->toString());
}

TEST_F(DSTOffsetTest, 0)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<DSTOffset>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DSTOffsetEnum::StandardTime, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DSTOffsetEnum::StandardTime, btSpecObj.dstOffset);

    EXPECT_EQ("Standard Time", result->toString());
}

TEST_F(DSTOffsetTest, TooShort)
{
    auto result = bleValueParser.make_value<DSTOffset>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DSTOffsetTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<DSTOffset>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DSTOffsetTest, ToString)
{
    constexpr char data[] = { '\x08' };

    auto result = bleValueParser.make_value(CharacteristicType::DSTOffset,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Double Daylight Time (+2h)", result->toString());
}

}  // namespace bvp
