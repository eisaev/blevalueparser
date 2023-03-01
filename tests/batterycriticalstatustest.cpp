#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BatteryCriticalStatusTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BatteryCriticalStatusTest, ReservedAll_CriticalPowerStateNo_ImmediateServiceRequiredNo)
{
    constexpr char data[] = { C(0b11111100) };

    auto result = bleValueParser.make_value<BatteryCriticalStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isCriticalPowerState());
    EXPECT_FALSE(result->isImmediateServiceRequired());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(252, btSpecObj.batteryCriticalStatus);

    EXPECT_EQ("{ }", result->toString());
}

TEST_F(BatteryCriticalStatusTest, ReservedOdd_CriticalPowerStateNo_ImmediateServiceRequiredYes)
{
    constexpr char data[] = { C(0b01010101) };

    auto result = bleValueParser.make_value<BatteryCriticalStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCriticalPowerState());
    EXPECT_FALSE(result->isImmediateServiceRequired());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(85, btSpecObj.batteryCriticalStatus);

    EXPECT_EQ("{ CriticalPowerState }", result->toString());
}

TEST_F(BatteryCriticalStatusTest, ReservedEven_CriticalPowerStateYes_ImmediateServiceRequiredNo)
{
    constexpr char data[] = { C(0b10101010) };

    auto result = bleValueParser.make_value<BatteryCriticalStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isCriticalPowerState());
    EXPECT_TRUE(result->isImmediateServiceRequired());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(170, btSpecObj.batteryCriticalStatus);

    EXPECT_EQ("{ ImmediateServiceRequired }", result->toString());
}

TEST_F(BatteryCriticalStatusTest, ReservedNone_CriticalPowerStateYes_ImmediateServiceRequiredYes)
{
    constexpr char data[] = { C(0b00000011) };

    auto result = bleValueParser.make_value<BatteryCriticalStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCriticalPowerState());
    EXPECT_TRUE(result->isImmediateServiceRequired());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(3, btSpecObj.batteryCriticalStatus);

    EXPECT_EQ("{ CriticalPowerState ImmediateServiceRequired }", result->toString());
}

TEST_F(BatteryCriticalStatusTest, TooShort)
{
    auto result = bleValueParser.make_value<BatteryCriticalStatus>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryCriticalStatusTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryCriticalStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryCriticalStatusTest, ToString)
{
    constexpr char data[] = { C(0b00000010) };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryCriticalStatus,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("{ ImmediateServiceRequired }", result->toString());
}

}  // namespace bvp
