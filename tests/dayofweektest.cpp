#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

class DayOfWeekTest : public testing::Test
{
protected:
    explicit DayOfWeekTest() {}
    virtual ~DayOfWeekTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(DayOfWeekTest, Monday)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Monday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Monday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Mon", result->toString());
}

TEST_F(DayOfWeekTest, Tuesday)
{
    constexpr char data[] = { '\02' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Tuesday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Tuesday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Tue", result->toString());
}

TEST_F(DayOfWeekTest, Wednesday)
{
    constexpr char data[] = { '\x03' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Wednesday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Wednesday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Wed", result->toString());
}

TEST_F(DayOfWeekTest, Thursday)
{
    constexpr char data[] = { '\x04' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Thursday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Thursday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Thu", result->toString());
}

TEST_F(DayOfWeekTest, Friday)
{
    constexpr char data[] = { '\x05' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Friday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Friday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Fri", result->toString());
}

TEST_F(DayOfWeekTest, Saturday)
{
    constexpr char data[] = { '\x06' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Saturday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Saturday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Sat", result->toString());
}

TEST_F(DayOfWeekTest, Sunday)
{
    constexpr char data[] = { '\x07' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(DayOfWeekEnum::Sunday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(DayOfWeekEnum::Sunday, btSpecObj.dayOfWeek);

    EXPECT_EQ("Sun", result->toString());
}

TEST_F(DayOfWeekTest, TooShort)
{
    auto result = bleValueParser.make_value<DayOfWeek>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DayOfWeekTest, TooLong)
{
    constexpr char data[] = { '\x01', '\x01' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DayOfWeekTest, Unknown)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(DayOfWeekTest, Reserved)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<DayOfWeek>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(DayOfWeekTest, ToString)
{
    constexpr char data[] = { '\x07' };

    auto result = bleValueParser.make_value(CharacteristicType::DayOfWeek,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Sun", result->toString());
}

}  // namespace bvp
