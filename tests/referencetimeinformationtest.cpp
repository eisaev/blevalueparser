#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

struct ReferenceTimeInformationTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(ReferenceTimeInformationTest, Unknown_0ms_0d_0h)
{
    constexpr char data[] = { '\x00', '\x00', '\x00', '\x00' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Unknown, result->timeSource());
    EXPECT_EQ(0, result->timeAccuracyMs());
    EXPECT_EQ(0, result->daysSinceUpdate());
    EXPECT_EQ(0, result->hoursSinceUpdate());
    EXPECT_EQ(0, result->timeSinceUpdateH());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Unknown, btSpecObj.timeSource.timeSource);
    EXPECT_EQ(0, btSpecObj.timeAccuracy.accuracy);
    EXPECT_EQ(0, btSpecObj.daysSinceUpdate);
    EXPECT_EQ(0, btSpecObj.hoursSinceUpdate);

    EXPECT_EQ("Src: <Unknown>, Drift: 0ms, Updated: 0hours ago", result->toString());
}

TEST_F(ReferenceTimeInformationTest, GPS_5250ms_0d_23h)
{
    constexpr char data[] = { '\x02', '\x2A', '\x00', '\x17' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::GPS, result->timeSource());
    EXPECT_EQ(5250, result->timeAccuracyMs());
    EXPECT_EQ(0, result->daysSinceUpdate());
    EXPECT_EQ(23, result->hoursSinceUpdate());
    EXPECT_EQ(23, result->timeSinceUpdateH());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::GPS, btSpecObj.timeSource.timeSource);
    EXPECT_EQ(42, btSpecObj.timeAccuracy.accuracy);
    EXPECT_EQ(0, btSpecObj.daysSinceUpdate);
    EXPECT_EQ(23, btSpecObj.hoursSinceUpdate);

    EXPECT_EQ("Src: GPS, Drift: 5250ms, Updated: 23hours ago", result->toString());
}

TEST_F(ReferenceTimeInformationTest, Manual_31625ms_254d_0h)
{
    constexpr char data[] = { '\x04', '\xFD', '\xFE', '\x00' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Manual, result->timeSource());
    EXPECT_EQ(31625, result->timeAccuracyMs());
    EXPECT_EQ(254, result->daysSinceUpdate());
    EXPECT_EQ(0, result->hoursSinceUpdate());
    EXPECT_EQ(6096, result->timeSinceUpdateH());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Manual, btSpecObj.timeSource.timeSource);
    EXPECT_EQ(253, btSpecObj.timeAccuracy.accuracy);
    EXPECT_EQ(254, btSpecObj.daysSinceUpdate);
    EXPECT_EQ(0, btSpecObj.hoursSinceUpdate);

    EXPECT_EQ("Src: Manual, Drift: 31625ms, Updated: 254days 0hours ago", result->toString());
}

TEST_F(ReferenceTimeInformationTest, CellularNetwork_Greater_254d_23h)
{
    constexpr char data[] = { '\x06', '\xFE', '\xFE', '\x17' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::CellularNetwork, result->timeSource());
    EXPECT_EQ(UINT16_MAX, result->timeAccuracyMs());
    EXPECT_EQ(254, result->daysSinceUpdate());
    EXPECT_EQ(23, result->hoursSinceUpdate());
    EXPECT_EQ(6119, result->timeSinceUpdateH());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::CellularNetwork, btSpecObj.timeSource.timeSource);
    EXPECT_EQ(254, btSpecObj.timeAccuracy.accuracy);
    EXPECT_EQ(254, btSpecObj.daysSinceUpdate);
    EXPECT_EQ(23, btSpecObj.hoursSinceUpdate);

    EXPECT_EQ("Src: CellularNetwork, Drift: >31625ms, Updated: 254days 23hours ago", result->toString());
}

TEST_F(ReferenceTimeInformationTest, Reserved_Unknown_Greater)
{
    constexpr char data[] = { '\xFF', '\xFF', '\xFF', '\xFF' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Unknown, result->timeSource());
    EXPECT_FALSE(result->isTimeAccuracyLarger());
    EXPECT_TRUE(result->isTimeAccuracyUnknown());
    EXPECT_EQ(UINT16_MAX, result->timeAccuracyMs());
    EXPECT_EQ(255, result->daysSinceUpdate());
    EXPECT_EQ(255, result->hoursSinceUpdate());
    EXPECT_EQ(UINT32_MAX, result->timeSinceUpdateH());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Unknown, btSpecObj.timeSource.timeSource);
    EXPECT_EQ(255, btSpecObj.timeAccuracy.accuracy);
    EXPECT_EQ(255, btSpecObj.daysSinceUpdate);
    EXPECT_EQ(255, btSpecObj.hoursSinceUpdate);

    EXPECT_EQ("Src: <Unknown>, Drift: <Unknown>, Updated: >254days ago", result->toString());
}

TEST_F(ReferenceTimeInformationTest, InvalidHoursSinceUpdate)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x18' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ReferenceTimeInformationTest, InvalidSinceUpdate1)
{
    constexpr char data[] = { '\x2A', '\x2A', '\xFF', '\x2A' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ReferenceTimeInformationTest, InvalidSinceUpdate2)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\xFF' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ReferenceTimeInformationTest, TooShort)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ReferenceTimeInformationTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<ReferenceTimeInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(ReferenceTimeInformationTest, ToString)
{
    constexpr char data[] = { '\x01', '\xAA', '\x2A', '\x0F' };

    auto result = bleValueParser.make_value(CharacteristicType::ReferenceTimeInformation,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Src: NetworkTimeProtocol, Drift: 21250ms, Updated: 42days 15hours ago", result->toString());
}

}  // namespace bvp
