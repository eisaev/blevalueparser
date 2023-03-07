#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct DayDateTimeTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(DayDateTimeTest, 20230102_202207_Mon)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07', '\x01' };

    auto result = bleValueParser.make_value<DayDateTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(1, result->month());
    EXPECT_EQ(2, result->day());
    EXPECT_EQ(20, result->hour());
    EXPECT_EQ(22, result->minute());
    EXPECT_EQ(7, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Monday, result->dayOfWeek());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.dateTime.year);
    EXPECT_EQ(1, btSpecObj.dateTime.month);
    EXPECT_EQ(2, btSpecObj.dateTime.day);
    EXPECT_EQ(20, btSpecObj.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Monday, btSpecObj.dayOfWeek.dayOfWeek);

    EXPECT_EQ("Mon 02.01.2023 20:22:07", result->toString());
}

TEST_F(DayDateTimeTest, TooShort)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07' };

    auto result = bleValueParser.make_value<DayDateTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DayDateTimeTest, TooLong)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03', '\x2A' };

    auto result = bleValueParser.make_value<DayDateTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(DayDateTimeTest, ToString)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\x07' };

    auto result = bleValueParser.make_value(CharacteristicType::DayDateTime,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Sun 31.12.2022 23:59:59", result->toString());
}

}  // namespace bvp
