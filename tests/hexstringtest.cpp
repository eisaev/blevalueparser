#include "gtest/gtest.h"

#include "blevalueparser.h"


namespace bvp
{

class HexStringTest : public testing::Test
{
protected:
    explicit HexStringTest() {}
    virtual ~HexStringTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(HexStringTest, Basic)
{
    constexpr char data[] = { '\x01', '\x02', '\x03', '\x0D', '\x0E', '\x0F' };

    auto result = bleValueParser.make_value<HexString>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("0x 01:02:03:0D:0E:0F", result->toString());
}

TEST_F(HexStringTest, Empty)
{
    constexpr char data[] = {};

    auto result = bleValueParser.make_value<HexString>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("0x", result->toString());
}

TEST_F(HexStringTest, ToString)
{
    constexpr char data[] = { '\x01', '\x02', '\x03', '\x0D', '\x0E', '\x0F' };

    auto result = bleValueParser.make_value(CharacteristicType::SystemID,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("0x 01:02:03:0D:0E:0F", result->toString());
}

TEST_F(HexStringTest, Configuration)
{
    constexpr char data[] = { '\x01', '\x02', '\x03', '\x0D', '\x0E', '\x0F' };

    bleValueParser.configuration.stringPrefix = "<< ";
    bleValueParser.configuration.stringSuffix = " >>";
    bleValueParser.configuration.hexPrefix = "hex> ";
    bleValueParser.configuration.hexSeparator = " ";

    auto result = bleValueParser.make_value(CharacteristicType::SystemID,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("<< hex> 01 02 03 0D 0E 0F >>", result->toString());
}

}  // namespace bvp
