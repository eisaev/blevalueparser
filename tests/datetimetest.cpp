#include "gtest/gtest.h"

#include "blevalueparser.h"


namespace bvp
{

class DateTimeTest : public testing::Test
{
protected:
    explicit DateTimeTest() {}
    virtual ~DateTimeTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(DateTimeTest, Normal)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07' };

    auto result = bleValueParser.make_value<DateTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(1, result->month());
    EXPECT_EQ(2, result->day());
    EXPECT_EQ(20, result->hour());
    EXPECT_EQ(22, result->minute());
    EXPECT_EQ(7, result->seconds());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.year);
    EXPECT_EQ(1, btSpecObj.month);
    EXPECT_EQ(2, btSpecObj.day);
    EXPECT_EQ(20, btSpecObj.hour);
    EXPECT_EQ(22, btSpecObj.minute);
    EXPECT_EQ(7, btSpecObj.seconds);

    EXPECT_EQ("02.01.2023 20:22:07", result->toString());
}

TEST_F(DateTimeTest, TooShort)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16' };

    auto result = bleValueParser.make_value<DateTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DateTimeTest, TooLong)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07', '\x07' };

    auto result = bleValueParser.make_value<DateTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DateTimeTest, ToString)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B' };

    auto result = bleValueParser.make_value(CharacteristicType::DateTime,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("31.12.2022 23:59:59", result->toString());
}

}  // namespace bvp
