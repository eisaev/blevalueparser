#include "gtest/gtest.h"

#include "blevalueparser/bvp.h"


namespace bvp
{

class LocalTimeInformationTest : public testing::Test
{
protected:
    explicit LocalTimeInformationTest() {}
    virtual ~LocalTimeInformationTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(LocalTimeInformationTest, TZUnknown_DSTUnknown)
{
    constexpr char data[] = { char(-128), '\xFF' };

    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Unknown, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::Unknown, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Unknown, btSpecObj.timeZone.timeZone);
    EXPECT_EQ(DSTOffsetEnum::Unknown, btSpecObj.dstOffset.dstOffset);

    EXPECT_EQ("TZ: <Unknown>, DST: <Unknown>", result->toString());
}

TEST_F(LocalTimeInformationTest, TZUnreal_DSTUnreal)
{
    constexpr char data[] = { 57, '\x2A' };

    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Unknown, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::Unknown, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Unknown, btSpecObj.timeZone.timeZone);
    EXPECT_EQ(DSTOffsetEnum::Unknown, btSpecObj.dstOffset.dstOffset);

    EXPECT_EQ("TZ: <Unknown>, DST: <Unknown>", result->toString());
}

TEST_F(LocalTimeInformationTest, TZPlus0_DST1h)
{
    constexpr char data[] = { '\x00', '\x04' };

    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Plus0, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::DaylightTime1h, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Plus0, btSpecObj.timeZone.timeZone);
    EXPECT_EQ(DSTOffsetEnum::DaylightTime1h, btSpecObj.dstOffset.dstOffset);

    EXPECT_EQ("TZ: 0, DST: Daylight Time (+1h)", result->toString());
}

TEST_F(LocalTimeInformationTest, TZMinus48_DST0_5h)
{
    constexpr char data[] = { '\xD0', '\x02' };

    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Minus48, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::HalfAnHourDaylightTime0_5h, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Minus48, btSpecObj.timeZone.timeZone);
    EXPECT_EQ(DSTOffsetEnum::HalfAnHourDaylightTime0_5h, btSpecObj.dstOffset.dstOffset);

    EXPECT_EQ("TZ: -48, DST: Half an Hour Daylight Time (+0.5h)", result->toString());
}

TEST_F(LocalTimeInformationTest, TZPlus56_DST0)
{
    constexpr char data[] = { '\x38', '\x00' };

    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Plus56, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::StandardTime, result->dstOffset());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeZoneEnum::Plus56, btSpecObj.timeZone.timeZone);
    EXPECT_EQ(DSTOffsetEnum::StandardTime, btSpecObj.dstOffset.dstOffset);

    EXPECT_EQ("TZ: 56, DST: Standard Time", result->toString());
}
TEST_F(LocalTimeInformationTest, ToString)
{
    constexpr char data[] = { char(-42), '\x08' };

    auto result = bleValueParser.make_value(CharacteristicType::LocalTimeInformation,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("TZ: -42, DST: Double Daylight Time (+2h)", result->toString());
}

}  // namespace bvp
