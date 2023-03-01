#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct HeartRateControlPointTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(HeartRateControlPointTest, Zero)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<HeartRateControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(HeartRateControlPointEnum::Reserved, result->controlPointType());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(HeartRateControlPointEnum::Reserved, btSpecObj.heartRateControlPoint);

    EXPECT_EQ("<Reserved>", result->toString());
}

TEST_F(HeartRateControlPointTest, ResetEnergyExpended)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value<HeartRateControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(HeartRateControlPointEnum::ResetEnergyExpended, result->controlPointType());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(HeartRateControlPointEnum::ResetEnergyExpended, btSpecObj.heartRateControlPoint);

    EXPECT_EQ("ResetEnergyExpended", result->toString());
}

TEST_F(HeartRateControlPointTest, Reserved)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<HeartRateControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(HeartRateControlPointEnum::Reserved, result->controlPointType());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(HeartRateControlPointEnum::Reserved, btSpecObj.heartRateControlPoint);

    EXPECT_EQ("<Reserved>", result->toString());
}

TEST_F(HeartRateControlPointTest, TooShort)
{
    auto result = bleValueParser.make_value<HeartRateControlPoint>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateControlPointTest, TooLong)
{
    constexpr char data[] = { '\x01', '\x02' };

    auto result = bleValueParser.make_value<HeartRateControlPoint>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateControlPointTest, ToString)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value(CharacteristicType::HeartRateControlPoint,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("ResetEnergyExpended", result->toString());
}

}  // namespace bvp
