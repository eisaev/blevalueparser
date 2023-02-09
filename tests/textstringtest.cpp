#include "gtest/gtest.h"

#include "blevalueparser.h"


namespace bvp
{

class TextStringTest : public testing::Test
{
protected:
    explicit TextStringTest() {}
    virtual ~TextStringTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(TextStringTest, Basic)
{
    constexpr char data[] = { 'a', 'B', 'c', 'X', 'y', 'Z' };

    auto result = bleValueParser.make_value<TextString>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("aBcXyZ", result->toString());
}

TEST_F(TextStringTest, Empty)
{
    constexpr char data[] = {};

    auto result = bleValueParser.make_value<TextString>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("", result->toString());
}

TEST_F(TextStringTest, ToString)
{
    constexpr char data[] = { 'a', 'B', 'c', 'X', 'y', 'Z' };

    auto result = bleValueParser.make_value(CharacteristicType::ModelNumberString,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("aBcXyZ", result->toString());
}

}  // namespace bvp
