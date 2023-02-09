#include "gtest/gtest.h"

#include "blevalueparser/bvp.h"


namespace bvp
{

class UserIndexTest : public testing::Test
{
protected:
    explicit UserIndexTest() {}
    virtual ~UserIndexTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(UserIndexTest, Min)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<UserIndex>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(0, result->userIndex());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(0, btSpecObj.userIndex);

    EXPECT_EQ("0", result->toString());
}

TEST_F(UserIndexTest, Valid42)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<UserIndex>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(42, result->userIndex());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(42, btSpecObj.userIndex);

    EXPECT_EQ("42", result->toString());
}

TEST_F(UserIndexTest, Max)
{
    constexpr char data[] = { '\xFE' };

    auto result = bleValueParser.make_value<UserIndex>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(254, result->userIndex());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(254, btSpecObj.userIndex);

    EXPECT_EQ("254", result->toString());
}

TEST_F(UserIndexTest, Unknown)
{
    constexpr char data[] = { '\xFF' };

    auto result = bleValueParser.make_value<UserIndex>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(255, result->userIndex());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(255, btSpecObj.userIndex);

    EXPECT_EQ("<Unknown User>", result->toString());
}

TEST_F(UserIndexTest, ToString)
{
    constexpr char data[] = { '\xFE' };

    auto result = bleValueParser.make_value(CharacteristicType::UserIndex,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("254", result->toString());
}

}  // namespace bvp
