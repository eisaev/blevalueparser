#include <array>
#include <gtest/gtest.h>

#include "blevalueparser/basevalue.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

TEST(InternalParserTest, Raw)
{
    constexpr char data[] = { 'a', 'b', 'c', 'X', 'Y', 'Z' };
    BaseValue::Parser parser{data, sizeof(data)};
    parser.parseInt16();
    size_t size = 3;
    EXPECT_EQ("cXY", std::string(parser.getRawData(size), size));
}

TEST(InternalParserTest, String)
{
    constexpr char data[] = { 'a', 'b', 'c', 'X', 'Y', 'Z' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ("abcXYZ", parser.parseString());
}

TEST(InternalParserTest, UInt8)
{
    constexpr char data[] = { '\x00', '\x7F', '\x80', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt8());
    EXPECT_EQ(127, parser.parseUInt8());
    EXPECT_EQ(128, parser.parseUInt8());
    EXPECT_EQ(UINT8_MAX, parser.parseUInt8());
}

TEST(InternalParserTest, UInt16)
{
    constexpr char data[] = {
        '\x00', '\x00',
        '\xFF', '\x7F',
        '\x00', '\x80',
        '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt16());
    EXPECT_EQ(32767, parser.parseUInt16());
    EXPECT_EQ(32768, parser.parseUInt16());
    EXPECT_EQ(UINT16_MAX, parser.parseUInt16());
}

TEST(InternalParserTest, UInt24)
{
    constexpr int32_t uint24_max = 16777215;
    constexpr char data[] = {
        '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt24());
    EXPECT_EQ(8388607, parser.parseUInt24());
    EXPECT_EQ(8388608, parser.parseUInt24());
    EXPECT_EQ(uint24_max, parser.parseUInt24());
}

TEST(InternalParserTest, UInt32)
{
    constexpr char data[] = {
        '\x00', '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt32());
    EXPECT_EQ(2147483647, parser.parseUInt32());
    EXPECT_EQ(2147483648, parser.parseUInt32());
    EXPECT_EQ(UINT32_MAX, parser.parseUInt32());
}

TEST(InternalParserTest, UInt48)
{
    constexpr uint64_t uint48_max = 281474976710655;
    constexpr char data[] = {
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt48());
    EXPECT_EQ(140737488355327, parser.parseUInt48());
    EXPECT_EQ(140737488355328, parser.parseUInt48());
    EXPECT_EQ(uint48_max, parser.parseUInt48());
}

TEST(InternalParserTest, UInt64)
{
    constexpr char data[] = {
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt64());
    EXPECT_EQ(9223372036854775807, parser.parseUInt64());
    EXPECT_EQ(9223372036854775808U, parser.parseUInt64());
    EXPECT_EQ(UINT64_MAX, parser.parseUInt64());
}

TEST(InternalParserTest, Int8)
{
    constexpr char data[] = { '\x00', '\x7F', '\x80', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt8());
    EXPECT_EQ(INT8_MAX, parser.parseInt8());
    EXPECT_EQ(INT8_MIN, parser.parseInt8());
    EXPECT_EQ(-1, parser.parseInt8());
}

TEST(InternalParserTest, Int16)
{
    constexpr char data[] = {
        '\x00', '\x00',
        '\xFF', '\x7F',
        '\x00', '\x80',
        '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt16());
    EXPECT_EQ(INT16_MAX, parser.parseInt16());
    EXPECT_EQ(INT16_MIN, parser.parseInt16());
    EXPECT_EQ(-1, parser.parseInt16());
}

TEST(InternalParserTest, Int24)
{
    constexpr int32_t int24_max = 8388607;
    constexpr int32_t int24_min = -8388608;
    constexpr char data[] = {
        '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt24());
    EXPECT_EQ(int24_max, parser.parseInt24());
    EXPECT_EQ(int24_min, parser.parseInt24());
    EXPECT_EQ(-1, parser.parseInt24());
}

TEST(InternalParserTest, Int32)
{
    constexpr char data[] = {
        '\x00', '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt32());
    EXPECT_EQ(INT32_MAX, parser.parseInt32());
    EXPECT_EQ(INT32_MIN, parser.parseInt32());
    EXPECT_EQ(-1, parser.parseInt32());
}

TEST(InternalParserTest, Int48)
{
    constexpr int64_t int48_max = 140737488355327;
    constexpr int64_t int48_min = -140737488355328;
    constexpr char data[] = {
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt48());
    EXPECT_EQ(int48_max, parser.parseInt48());
    EXPECT_EQ(int48_min, parser.parseInt48());
    EXPECT_EQ(-1, parser.parseInt48());
}

TEST(InternalParserTest, Int64)
{
    constexpr char data[] = {
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\x7F',
        '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x80',
        '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF'
    };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt64());
    EXPECT_EQ(INT64_MAX, parser.parseInt64());
    EXPECT_EQ(INT64_MIN, parser.parseInt64());
    EXPECT_EQ(-1, parser.parseInt64());
}

TEST(InternalParserTest, Raw_OutOfData)
{
    constexpr char data[] = { 'a', 'b', 'c', 'X', 'Y', 'Z' };
    BaseValue::Parser parser{data, sizeof(data)};
    parser.parseInt16();
    EXPECT_FALSE(parser.outOfData());
    size_t size = 5;
    parser.getRawData(size);
    EXPECT_TRUE(parser.outOfData());
}

TEST(InternalParserTest, Int_OutOfData)
{
    constexpr char data[] = { '\x00', '\x7F', '\x80', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data) - 1};
    EXPECT_EQ(0, parser.parseInt8());
    EXPECT_FALSE(parser.outOfData());
    EXPECT_EQ(INT8_MAX, parser.parseInt8());
    EXPECT_FALSE(parser.outOfData());
    EXPECT_EQ(INT8_MIN, parser.parseInt8());
    EXPECT_FALSE(parser.outOfData());
    parser.parseInt8();
    EXPECT_TRUE(parser.outOfData());
}

struct MedFloat16Test : public testing::TestWithParam<std::tuple<int8_t, int16_t, float, std::string>>
{
    std::array<char, 2> getData(int16_t mantissa, int8_t exponent) const
    {
        const uint8_t exponent_sign = exponent & 0b10000000;
        const uint8_t exponent_value = static_cast<uint8_t>((static_cast<uint8_t>(exponent) << 4) | exponent_sign);
        const uint8_t mantissa_sign = static_cast<uint8_t>((mantissa & 0b1000000000000000) >> 12);
        const uint8_t mantissa_hvalue = static_cast<uint8_t>((mantissa & 0b011100000000) >> 8) | mantissa_sign;
        const uint8_t mantissa_lvalue = static_cast<uint8_t>(mantissa & 0b000011111111);

        return
        {
            C(exponent_value + mantissa_hvalue),
            C(mantissa_lvalue)
        };
    };
};
TEST_P(MedFloat16Test, Convert)
{
    const int8_t exponent = std::get<0>(GetParam());
    const int16_t mantissa = std::get<1>(GetParam());
    const float expectedFloat = std::get<2>(GetParam());
    const std::string expectedString = std::get<3>(GetParam());

    const auto data = getData(mantissa, exponent);
    BaseValue::Parser parser{data.data(), data.size()};
    float abs_error = std::pow(10, exponent);
    MedFloat16 value = parser.parseMedFloat16();

    EXPECT_NEAR(expectedFloat, value.toFloat(), abs_error);
    EXPECT_EQ(expectedString, value.toString());
}
INSTANTIATE_TEST_SUITE_P(
    InternalParserTest,
    MedFloat16Test,
    // tuples of (exponent, mantissa, expectedFloat, expectedString)
    ::testing::Values(
        std::make_tuple( 7, -2048, -20480000000.0, "-2.048e+10"),
        std::make_tuple(-1, -2048, -204.8, "-204.8"),
        std::make_tuple(-8, -2048, -0.00002048, "-2.048e-05"),

        std::make_tuple( 0, -2045, -2045.0, "-2045"),

        std::make_tuple( 7, 0, 0.0, "0"),
        std::make_tuple( 0, 0, 0.0, "0"),
        std::make_tuple(-1, 0, 0.0, "0"),
        std::make_tuple(-8, 0, 0.0, "0"),

        std::make_tuple( 7, -1, -10000000.0, "-1e+07"),
        std::make_tuple( 0, -1, -1.0, "-1"),
        std::make_tuple(-1, -1, -0.1, "-0.1"),
        std::make_tuple(-8, -1, -0.00000001, "-1e-08"),

        std::make_tuple( 0, 2045, 2045.0, "2045"),

        std::make_tuple( 7, 2047, 20470000000.0, "2.047e+10"),
        std::make_tuple(-1, 2047, 204.7, "204.7"),
        std::make_tuple(-8, 2047, 0.00002047, "2.047e-05"),

           // Special values
        std::make_tuple( 0, 2047, 2047.0, "<NaN>"),
        std::make_tuple( 0, 2046, 2046.0, "<+Inf>"),
        std::make_tuple( 0, -2046, -2046.0, "<-Inf>"),
        std::make_tuple( 0, -2047, -2047.0, "<Reserved>"),
        std::make_tuple( 0, -2048, -2048.0, "<Nres>")
    )
);

}  // namespace bvp
