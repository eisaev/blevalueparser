#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

class CurrentTimeTest : public testing::Test
{
protected:
    explicit CurrentTimeTest() {}
    virtual ~CurrentTimeTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(CurrentTimeTest, Manual_255)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07', '\x01', '\xFF', '\01' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
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
    EXPECT_TRUE(result->isManuallyAdjusted());
    EXPECT_FALSE(result->isExternalReference());
    EXPECT_FALSE(result->isTZChanged());
    EXPECT_FALSE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(2, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Monday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(255, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Mon 02.01.2023 20:22:07.996 (adjust reason: { ManuallyAdjusted })", result->toString());
}

TEST_F(CurrentTimeTest, External_0)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x03', '\x14', '\x16', '\x07', '\x02', '\x00', '\02' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
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
    EXPECT_FALSE(result->isManuallyAdjusted());
    EXPECT_TRUE(result->isExternalReference());
    EXPECT_FALSE(result->isTZChanged());
    EXPECT_FALSE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(3, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Tuesday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(0, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Tue 03.01.2023 20:22:07.000 (adjust reason: { ExternalReference })", result->toString());
}

TEST_F(CurrentTimeTest, TZChanged_1)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03', '\x01', '\04' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
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
    EXPECT_FALSE(result->isManuallyAdjusted());
    EXPECT_FALSE(result->isExternalReference());
    EXPECT_TRUE(result->isTZChanged());
    EXPECT_FALSE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(4, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Wednesday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(1, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Wed 04.01.2023 20:22:07.003 (adjust reason: { TZChanged })", result->toString());
}

TEST_F(CurrentTimeTest, DSTChanged_128)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x05', '\x14', '\x16', '\x07', '\x04', '\x80', '\x08' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
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
    EXPECT_FALSE(result->isManuallyAdjusted());
    EXPECT_FALSE(result->isExternalReference());
    EXPECT_FALSE(result->isTZChanged());
    EXPECT_TRUE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2023, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(1, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(5, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(20, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(22, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(7, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Thursday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(128, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Thu 05.01.2023 20:22:07.500 (adjust reason: { DSTChanged })", result->toString());
}

TEST_F(CurrentTimeTest, Friday)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1D', '\x17', '\x3B', '\x3B', '\x05', '\xFF', '\x01' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2022, result->year());
    EXPECT_EQ(12, result->month());
    EXPECT_EQ(29, result->day());
    EXPECT_EQ(23, result->hour());
    EXPECT_EQ(59, result->minute());
    EXPECT_EQ(59, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Friday, result->dayOfWeek());
    EXPECT_EQ(255, result->fractionsOfSeconds());
    EXPECT_EQ(996, result->milliseconds());
    EXPECT_TRUE(result->isManuallyAdjusted());
    EXPECT_FALSE(result->isExternalReference());
    EXPECT_FALSE(result->isTZChanged());
    EXPECT_FALSE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2022, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(12, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(29, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(23, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(59, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(59, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Friday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(255, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Fri 29.12.2022 23:59:59.996 (adjust reason: { ManuallyAdjusted })", result->toString());
}

TEST_F(CurrentTimeTest, Saturday)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1E', '\x17', '\x3B', '\x3B', '\x06', '\xFF', '\x01' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2022, result->year());
    EXPECT_EQ(12, result->month());
    EXPECT_EQ(30, result->day());
    EXPECT_EQ(23, result->hour());
    EXPECT_EQ(59, result->minute());
    EXPECT_EQ(59, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Saturday, result->dayOfWeek());
    EXPECT_EQ(255, result->fractionsOfSeconds());
    EXPECT_EQ(996, result->milliseconds());
    EXPECT_TRUE(result->isManuallyAdjusted());
    EXPECT_FALSE(result->isExternalReference());
    EXPECT_FALSE(result->isTZChanged());
    EXPECT_FALSE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2022, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(12, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(30, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(23, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(59, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(59, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Saturday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(255, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Sat 30.12.2022 23:59:59.996 (adjust reason: { ManuallyAdjusted })", result->toString());
}

TEST_F(CurrentTimeTest, Sunday)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\x07', '\xFF', '\x01' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(2022, result->year());
    EXPECT_EQ(12, result->month());
    EXPECT_EQ(31, result->day());
    EXPECT_EQ(23, result->hour());
    EXPECT_EQ(59, result->minute());
    EXPECT_EQ(59, result->seconds());
    EXPECT_EQ(DayOfWeekEnum::Sunday, result->dayOfWeek());
    EXPECT_EQ(255, result->fractionsOfSeconds());
    EXPECT_EQ(996, result->milliseconds());
    EXPECT_TRUE(result->isManuallyAdjusted());
    EXPECT_FALSE(result->isExternalReference());
    EXPECT_FALSE(result->isTZChanged());
    EXPECT_FALSE(result->isDSTChanged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2022, btSpecObj.exactTime256.dayDateTime.dateTime.year);
    EXPECT_EQ(12, btSpecObj.exactTime256.dayDateTime.dateTime.month);
    EXPECT_EQ(31, btSpecObj.exactTime256.dayDateTime.dateTime.day);
    EXPECT_EQ(23, btSpecObj.exactTime256.dayDateTime.dateTime.hour);
    EXPECT_EQ(59, btSpecObj.exactTime256.dayDateTime.dateTime.minute);
    EXPECT_EQ(59, btSpecObj.exactTime256.dayDateTime.dateTime.seconds);
    EXPECT_EQ(DayOfWeekEnum::Sunday, btSpecObj.exactTime256.dayDateTime.dayOfWeek.dayOfWeek);
    EXPECT_EQ(255, btSpecObj.exactTime256.fractions256);

    EXPECT_EQ("Sun 31.12.2022 23:59:59.996 (adjust reason: { ManuallyAdjusted })", result->toString());
}

TEST_F(CurrentTimeTest, TooShort)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03', '\x80' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(CurrentTimeTest, TooLong)
{
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x04', '\x14', '\x16', '\x07', '\x03', '\x80', '\x08', '\x08' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(CurrentTimeTest, UnknownDayOfWeek)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\xAA', '\xFF', '\x01' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("<Unknown> 31.12.2022 23:59:59.996 (adjust reason: { ManuallyAdjusted })", result->toString());
}

TEST_F(CurrentTimeTest, NoReason)
{
    constexpr char data[] = { '\xE7', '\x07', '\x02', '\x06', '\x0E', '\x2F', '\x2A', '\x00', '\x00', '\x00' };

    auto result = bleValueParser.make_value<CurrentTime>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("<Unknown> 06.02.2023 14:47:42.000", result->toString());
}

TEST_F(CurrentTimeTest, ToString)
{
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\x07', '\xFF', '\x01' };

    auto result = bleValueParser.make_value(CharacteristicType::CurrentTime,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Sun 31.12.2022 23:59:59.996 (adjust reason: { ManuallyAdjusted })", result->toString());
}

}  // namespace bvp
