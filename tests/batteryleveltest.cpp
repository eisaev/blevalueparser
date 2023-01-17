#include "gtest/gtest.h"

#include "blevalueparser.h"


namespace bvp
{

class BatteryLevelTest : public testing::Test
{
protected:
    explicit BatteryLevelTest() {}
    virtual ~BatteryLevelTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(BatteryLevelTest, Zero)
{
    constexpr char data[] = { '\x00' };
    auto result = bleValueParser.make_value<BatteryLevel>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(0, result->level());
    EXPECT_EQ("0%", result->toString());
}

TEST_F(BatteryLevelTest, Full)
{
    constexpr char data[] = { '\x64' };
    auto result = bleValueParser.make_value<BatteryLevel>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(100, result->level());
    EXPECT_EQ("100%", result->toString());
}

TEST_F(BatteryLevelTest, Unreal)
{
    constexpr char data[] = { '\x92' };
    auto result = bleValueParser.make_value<BatteryLevel>(data, sizeof(data));
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryLevelTest, ToString)
{
    constexpr char data[] = { '\x63' };
    auto result = bleValueParser.make_value(CharacteristicType::BatteryLevel,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ("99%", result->toString());
}

}  // namespace bvp
