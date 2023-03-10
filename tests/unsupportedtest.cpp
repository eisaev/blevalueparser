#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct UnsupportedTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(UnsupportedTest, ToStringHex)
{
    constexpr char data[] = { '\x00', '\x01', '\x02', '\x03' };

    auto result = bleValueParser.make_value(CharacteristicType::RelativeRuntimeinaCorrelatedColorTemperatureRange,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("0x 00:01:02:03", result->toString());
}

TEST_F(UnsupportedTest, ToStringText)
{
    constexpr char data[] = { '\x30', '\x31', '\x32', '\x33' };

    auto result = bleValueParser.make_value(CharacteristicType::RelativeRuntimeinaCorrelatedColorTemperatureRange,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("0123", result->toString());
}

}  // namespace bvp
