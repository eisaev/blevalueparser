#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"


namespace bvp
{

class TimeSourceTest : public testing::Test
{
protected:
    explicit TimeSourceTest() {}
    virtual ~TimeSourceTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(TimeSourceTest, Unknown)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Unknown, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Unknown, btSpecObj.timeSource);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(TimeSourceTest, NetworkTimeProtocol)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::NetworkTimeProtocol, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::NetworkTimeProtocol, btSpecObj.timeSource);

    EXPECT_EQ("NetworkTimeProtocol", result->toString());
}

TEST_F(TimeSourceTest, GPS)
{
    constexpr char data[] = { '\x02' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::GPS, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::GPS, btSpecObj.timeSource);

    EXPECT_EQ("GPS", result->toString());
}

TEST_F(TimeSourceTest, RadioTimeSignal)
{
    constexpr char data[] = { '\x03' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::RadioTimeSignal, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::RadioTimeSignal, btSpecObj.timeSource);

    EXPECT_EQ("RadioTimeSignal", result->toString());
}

TEST_F(TimeSourceTest, Manual)
{
    constexpr char data[] = { '\x04' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Manual, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Manual, btSpecObj.timeSource);

    EXPECT_EQ("Manual", result->toString());
}

TEST_F(TimeSourceTest, AtomicClock)
{
    constexpr char data[] = { '\x05' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::AtomicClock, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::AtomicClock, btSpecObj.timeSource);

    EXPECT_EQ("AtomicClock", result->toString());
}

TEST_F(TimeSourceTest, CellularNetwork)
{
    constexpr char data[] = { '\x06' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::CellularNetwork, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::CellularNetwork, btSpecObj.timeSource);

    EXPECT_EQ("CellularNetwork", result->toString());
}

TEST_F(TimeSourceTest, Reserved)
{
    constexpr char data[] = { '\x07' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Unknown, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Unknown, btSpecObj.timeSource);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(TimeSourceTest, ReservedMax)
{
    constexpr char data[] = { '\xFF' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(TimeSourceEnum::Unknown, result->timeSource());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(TimeSourceEnum::Unknown, btSpecObj.timeSource);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(TimeSourceTest, TooShort)
{
    auto result = bleValueParser.make_value<TimeSource>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(TimeSourceTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<TimeSource>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(TimeSourceTest, ToString)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value(CharacteristicType::TimeSource,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("NetworkTimeProtocol", result->toString());
}

}  // namespace bvp
