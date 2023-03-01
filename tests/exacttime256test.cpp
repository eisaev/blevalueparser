#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct ExactTime256Test : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(ExactTime256Test, 255)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07', '\x01', '\xFF' };

    auto result = bleValueParser.make_value<ExactTime256>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(1, result->month());
    EXPECT_EQ(2, result->day());
    EXPECT_EQ(20, result->hour());
    EXPECT_EQ(22, result->minute());
    EXPECT_EQ(7, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Monday, result->dayOfWeek());
    EXPECT_EQ(255, result->fractionsOfSeconds());
    EXPECT_EQ(996, result->milliseconds());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.dayDateTime.dateTime.month);
    EXPECT_EQ(2, btSpecObj.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Monday, btSpecObj.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(255, btSpecObj.fractions256);

    EXPECT_EQ("Mon 02.01.2023 20:22:07.996", result->toString());
}

TEST_F(ExactTime256Test, 0)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x03', '\x14', '\x16', '\x07', '\x02', '\x00' };

    auto result = bleValueParser.make_value<ExactTime256>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(1, result->month());
    EXPECT_EQ(3, result->day());
    EXPECT_EQ(20, result->hour());
    EXPECT_EQ(22, result->minute());
    EXPECT_EQ(7, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Tuesday, result->dayOfWeek());
    EXPECT_EQ(0, result->fractionsOfSeconds());
    EXPECT_EQ(0, result->milliseconds());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.dayDateTime.dateTime.month);
    EXPECT_EQ(3, btSpecObj.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Tuesday, btSpecObj.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(0, btSpecObj.fractions256);

    EXPECT_EQ("Tue 03.01.2023 20:22:07.000", result->toString());
}

TEST_F(ExactTime256Test, 1)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03', '\x01' };

    auto result = bleValueParser.make_value<ExactTime256>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(1, result->month());
    EXPECT_EQ(4, result->day());
    EXPECT_EQ(20, result->hour());
    EXPECT_EQ(22, result->minute());
    EXPECT_EQ(7, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Wednesday, result->dayOfWeek());
    EXPECT_EQ(1, result->fractionsOfSeconds());
    EXPECT_EQ(3, result->milliseconds());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.dayDateTime.dateTime.month);
    EXPECT_EQ(4, btSpecObj.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Wednesday, btSpecObj.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(1, btSpecObj.fractions256);

    EXPECT_EQ("Wed 04.01.2023 20:22:07.003", result->toString());
}

TEST_F(ExactTime256Test, 128)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x05', '\x14', '\x16', '\x07', '\x04', '\x80' };

    auto result = bleValueParser.make_value<ExactTime256>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(1, result->month());
    EXPECT_EQ(5, result->day());
    EXPECT_EQ(20, result->hour());
    EXPECT_EQ(22, result->minute());
    EXPECT_EQ(7, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Thursday, result->dayOfWeek());
    EXPECT_EQ(128, result->fractionsOfSeconds());
    EXPECT_EQ(500, result->milliseconds());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.dayDateTime.dateTime.month);
    EXPECT_EQ(5, btSpecObj.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Thursday, btSpecObj.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(128, btSpecObj.fractions256);

    EXPECT_EQ("Thu 05.01.2023 20:22:07.500", result->toString());
}

TEST_F(ExactTime256Test, TooShort)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03' };

    auto result = bleValueParser.make_value<ExactTime256>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ExactTime256Test, TooLong)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03', '\x80', '\x2A' };

    auto result = bleValueParser.make_value<ExactTime256>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ExactTime256Test, ToString)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\x07', '\xFF' };

    auto result = bleValueParser.make_value(CharacteristicType::ExactTime256,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Sun 31.12.2022 23:59:59.996", result->toString());
}

}  // namespace bvp
