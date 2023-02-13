#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


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
    constexpr char data[] = { '\x00', '\x00',
                              '\xFF', '\x7F',
                              '\x00', '\x80',
                              '\xFF', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt16());
    EXPECT_EQ(32767, parser.parseUInt16());
    EXPECT_EQ(32768, parser.parseUInt16());
    EXPECT_EQ(UINT16_MAX, parser.parseUInt16());
}

TEST(InternalParserTest, UInt32)
{
    constexpr char data[] = { '\x00', '\x00', '\x00', '\x00',
                              '\xFF', '\xFF', '\xFF', '\x7F',
                              '\x00', '\x00', '\x00', '\x80',
                              '\xFF', '\xFF', '\xFF', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseUInt32());
    EXPECT_EQ(2147483647, parser.parseUInt32());
    EXPECT_EQ(2147483648, parser.parseUInt32());
    EXPECT_EQ(UINT32_MAX, parser.parseUInt32());
}

TEST(InternalParserTest, UInt64)
{
    constexpr char data[] = { '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
                              '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\x7F',
                              '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x80',
                              '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF' };
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
    constexpr char data[] = { '\x00', '\x00',
                              '\xFF', '\x7F',
                              '\x00', '\x80',
                              '\xFF', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt16());
    EXPECT_EQ(INT16_MAX, parser.parseInt16());
    EXPECT_EQ(INT16_MIN, parser.parseInt16());
    EXPECT_EQ(-1, parser.parseInt16());
}

TEST(InternalParserTest, Int32)
{
    constexpr char data[] = { '\x00', '\x00', '\x00', '\x00',
                              '\xFF', '\xFF', '\xFF', '\x7F',
                              '\x00', '\x00', '\x00', '\x80',
                              '\xFF', '\xFF', '\xFF', '\xFF' };
    BaseValue::Parser parser{data, sizeof(data)};
    EXPECT_EQ(0, parser.parseInt32());
    EXPECT_EQ(INT32_MAX, parser.parseInt32());
    EXPECT_EQ(INT32_MIN, parser.parseInt32());
    EXPECT_EQ(-1, parser.parseInt32());
}

TEST(InternalParserTest, Int64)
{
    constexpr char data[] = { '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00',
                              '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\x7F',
                              '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x80',
                              '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF', '\xFF' };
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

}  // namespace bvp
