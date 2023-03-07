#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BatteryTimeStatusTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BatteryTimeStatusTest, Discharged0_DischargedOnStandbyGreater_RechargedMax_ReservedNone)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x00', '\x00', // timeUntilDischarged
        '\xFE', '\xFF', '\xFF', // timeUntilDischargedOnStandby
        '\xFD', '\xFF', '\xFF'  // timeUntilRecharged
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_TRUE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0, result->timeUntilDischarged());
    EXPECT_EQ(0xFFFFFE, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0xFFFFFD, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(3, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0xFFFFFE, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0xFFFFFD, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: 0 minutes, TimeUntilDischargedOnStandby: >16777213 minutes, TimeUntilRecharged: 16777213 minutes", result->toString());
}

TEST_F(BatteryTimeStatusTest, DischargedNormal_DischargedOnStandbyUnknow_RechargedGreater_ReservedEven)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b10101011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', '\x2A', // timeUntilDischarged
        '\xFF', '\xFF', '\xFF', // timeUntilDischargedOnStandby
        '\xFE', '\xFF', '\xFF'  // timeUntilRecharged
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_TRUE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0x2A2A00, result->timeUntilDischarged());
    EXPECT_EQ(0xFFFFFF, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0xFFFFFE, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(171, btSpecObj.flags);
    EXPECT_EQ(0x2A2A00, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0xFFFFFF, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0xFFFFFE, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: 2763264 minutes, TimeUntilDischargedOnStandby: <Unknown>, TimeUntilRecharged: >16777213 minutes", result->toString());
}

TEST_F(BatteryTimeStatusTest, DischargedMax_DischargedOnStandbyNo_RechargedUnknown_ReservedAll)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b11111110);
    constexpr char data[] = {
        flags,
        '\xFD', '\xFF', '\xFF', // timeUntilDischarged
        '\xFF', '\xFF', '\xFF'  // timeUntilRecharged
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_TRUE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0xFFFFFD, result->timeUntilDischarged());
    EXPECT_EQ(0, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0xFFFFFF, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(254, btSpecObj.flags);
    EXPECT_EQ(0xFFFFFD, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0xFFFFFF, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: 16777213 minutes, TimeUntilRecharged: <Unknown>", result->toString());
}

TEST_F(BatteryTimeStatusTest, DischargedGreater_DischargedOnStandby0_RechargedNo_ReservedOdd)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b01010101);
    constexpr char data[] = {
        flags,
        '\xFE', '\xFF', '\xFF', // timeUntilDischarged
        '\x00', '\x00', '\x00'  // timeUntilDischargedOnStandby
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_FALSE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0xFFFFFE, result->timeUntilDischarged());
    EXPECT_EQ(0, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(85, btSpecObj.flags);
    EXPECT_EQ(0xFFFFFE, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: >16777213 minutes, TimeUntilDischargedOnStandby: 0 minutes", result->toString());
}

TEST_F(BatteryTimeStatusTest, DischargedUnknown_DischargedOnStandbyNormal_Recharged0_ReservedNone)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\xFF', '\xFF', '\xFF', // timeUntilDischarged
        '\x00', '\x2A', '\x2A', // timeUntilDischargedOnStandby
        '\x00', '\x00', '\x00'  // timeUntilRecharged
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_TRUE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0xFFFFFF, result->timeUntilDischarged());
    EXPECT_EQ(0x2A2A00, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(3, btSpecObj.flags);
    EXPECT_EQ(0xFFFFFF, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0x2A2A00, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: <Unknown>, TimeUntilDischargedOnStandby: 2763264 minutes, TimeUntilRecharged: 0 minutes", result->toString());
}

TEST_F(BatteryTimeStatusTest, Discharged0_DischargedOnStandbyMax_RechargedNormal_ReservedEven)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b10101011);
    constexpr char data[] = {
        flags,
        '\x00', '\x00', '\x00', // timeUntilDischarged
        '\xFD', '\xFF', '\xFF', // timeUntilDischargedOnStandby
        '\x00', '\x2A', '\x2A'  // timeUntilRecharged
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_TRUE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0, result->timeUntilDischarged());
    EXPECT_EQ(0xFFFFFD, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0x2A2A00, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(171, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0xFFFFFD, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0x2A2A00, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: 0 minutes, TimeUntilDischargedOnStandby: 16777213 minutes, TimeUntilRecharged: 2763264 minutes", result->toString());
}

TEST_F(BatteryTimeStatusTest, DischargedNormal_DischargedOnStandbyNo_RechargedNo_ReservedOdd)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b01010100);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', '\x2A'  // timeUntilDischarged
    };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeUntilDischargedOnStandbyPresent());
    EXPECT_FALSE(result->isTimeUntilRechargedPresent());
    EXPECT_EQ(0x2A2A00, result->timeUntilDischarged());
    EXPECT_EQ(0, result->timeUntilDischargedOnStandby());
    EXPECT_EQ(0, result->timeUntilRecharged());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(84, btSpecObj.flags);
    EXPECT_EQ(0x2A2A00, btSpecObj.timeUntilDischarged);
    EXPECT_EQ(0, btSpecObj.timeUntilDischargedOnStandby);
    EXPECT_EQ(0, btSpecObj.timeUntilRecharged);

    EXPECT_EQ("TimeUntilDischarged: 2763264 minutes", result->toString());
}

TEST_F(BatteryTimeStatusTest, TooShort)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryTimeStatusTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryTimeStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryTimeStatusTest, ToString)
{
    //                         RRRRRRCS
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', '\x2A', // timeUntilDischarged
        '\xFD', '\xFF', '\xFF', // timeUntilDischargedOnStandby
        '\xFF', '\xFF', '\xFF'  // timeUntilRecharged
    };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryTimeStatus,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("TimeUntilDischarged: 2763264 minutes, TimeUntilDischargedOnStandby: 16777213 minutes, TimeUntilRecharged: <Unknown>", result->toString());
}

}  // namespace bvp
