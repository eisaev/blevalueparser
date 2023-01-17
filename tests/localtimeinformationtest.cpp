#include "gtest/gtest.h"

#include "blevalueparser.h"


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
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Unknown, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::Unknown, result->dstOffset());
    EXPECT_EQ("TZ: <Unknown>, DST: <Unknown>", result->toString());
}

TEST_F(LocalTimeInformationTest, TZUnreal_DSTUnreal)
{
    constexpr char data[] = { 57, '\x2A' };
    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Unknown, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::Unknown, result->dstOffset());
    EXPECT_EQ("TZ: <Unknown>, DST: <Unknown>", result->toString());
}

TEST_F(LocalTimeInformationTest, TZ0_DST1h)
{
    constexpr char data[] = { '\x00', '\x04' };
    auto result = bleValueParser.make_value<LocalTimeInformation>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeZoneEnum::Plus0, result->timeZone());
    EXPECT_EQ(DSTOffsetEnum::DaylightTime1h, result->dstOffset());
    EXPECT_EQ("TZ: 0, DST: Daylight Time (+1h)", result->toString());
}

TEST_F(LocalTimeInformationTest, ToString)
{
    constexpr char data[] = { char(-42), '\x08' };
    BLEValueParser bleValueParser;
    auto result = bleValueParser.make_value(CharacteristicType::LocalTimeInformation,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ("TZ: -42, DST: Double Daylight Time (+2h)", result->toString());
}

}  // namespace bvp
