#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BatteryHealthStatusTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BatteryHealthStatusTest, SummaryNo_CycleNo_TemperatureNo_DeepNo_ReservedAll)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b11110000);
    constexpr char data[] = {
        flags
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryHealthSummaryPresent());
    EXPECT_FALSE(result->isCycleCountPresent());
    EXPECT_FALSE(result->isCurrentTemperaturePresent());
    EXPECT_FALSE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0, result->cycleCount());
    EXPECT_EQ(0, result->currentTemperature());
    EXPECT_EQ(0, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(240, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0, btSpecObj.cycleCount);
    EXPECT_EQ(0, btSpecObj.currentTemperature);
    EXPECT_EQ(0, btSpecObj.deepDischargeCount);

    EXPECT_EQ("<NoData>", result->toString());
}

TEST_F(BatteryHealthStatusTest, Summary0_CycleNormal_TemperatureMax_DeepNo_ReservedOdd)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b01010111);
    constexpr char data[] = {
        flags,
        '\x00',         // batteryHealthSummary
        '\x00', '\x2A', // cycleCount
        '\x7E'          // currentTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryHealthSummaryPresent());
    EXPECT_TRUE(result->isCycleCountPresent());
    EXPECT_TRUE(result->isCurrentTemperaturePresent());
    EXPECT_FALSE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0x2A00, result->cycleCount());
    EXPECT_EQ(126, result->currentTemperature());
    EXPECT_EQ(0, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(87, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCount);
    EXPECT_EQ(126, btSpecObj.currentTemperature);
    EXPECT_EQ(0, btSpecObj.deepDischargeCount);

    EXPECT_EQ("BatteryHealthSummary: 0%, CycleCount: 10752, CurrentTemperature: 126°C", result->toString());
}

TEST_F(BatteryHealthStatusTest, SummaryNormal_CycleMax_TemperatureNo_Deep0_ReservedEven)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b10101011);
    constexpr char data[] = {
        flags,
        '\x2A',         // batteryHealthSummary
        '\xFF', '\xFF', // cycleCount
        '\x00', '\x00'  // deepDischargeCount
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryHealthSummaryPresent());
    EXPECT_TRUE(result->isCycleCountPresent());
    EXPECT_FALSE(result->isCurrentTemperaturePresent());
    EXPECT_TRUE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0x2A, result->batteryHealthSummary());
    EXPECT_EQ(0xFFFF, result->cycleCount());
    EXPECT_EQ(0, result->currentTemperature());
    EXPECT_EQ(0, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(171, btSpecObj.flags);
    EXPECT_EQ(0x2A, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0xFFFF, btSpecObj.cycleCount);
    EXPECT_EQ(0, btSpecObj.currentTemperature);
    EXPECT_EQ(0, btSpecObj.deepDischargeCount);

    EXPECT_EQ("BatteryHealthSummary: 42%, CycleCount: 65535, DeepDischargeCount: 0", result->toString());
}

TEST_F(BatteryHealthStatusTest, SummaryMax_CycleNo_TemperatureMin_DeepNormal_ReservedNone)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b00001101);
    constexpr char data[] = {
        flags,
        '\x64',         // batteryHealthSummary
        '\x81',         // currentTemperature
        '\x00', '\x2A'  // deepDischargeCount
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryHealthSummaryPresent());
    EXPECT_FALSE(result->isCycleCountPresent());
    EXPECT_TRUE(result->isCurrentTemperaturePresent());
    EXPECT_TRUE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(100, result->batteryHealthSummary());
    EXPECT_EQ(0, result->cycleCount());
    EXPECT_EQ(-127, result->currentTemperature());
    EXPECT_EQ(0x2A00, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(13, btSpecObj.flags);
    EXPECT_EQ(100, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0, btSpecObj.cycleCount);
    EXPECT_EQ(-127, btSpecObj.currentTemperature);
    EXPECT_EQ(0x2A00, btSpecObj.deepDischargeCount);

    EXPECT_EQ("BatteryHealthSummary: 100%, CurrentTemperature: -127°C, DeepDischargeCount: 10752", result->toString());
}

TEST_F(BatteryHealthStatusTest, SummaryNo_Cycle0_TemperatureNormal_DeepMax_ReservedAll)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b11111110);
    constexpr char data[] = {
        flags,
        '\x00', '\x00', // cycleCount
        '\x2A',         // currentTemperature
        '\xFF', '\xFF'  // deepDischargeCount
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryHealthSummaryPresent());
    EXPECT_TRUE(result->isCycleCountPresent());
    EXPECT_TRUE(result->isCurrentTemperaturePresent());
    EXPECT_TRUE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0, result->cycleCount());
    EXPECT_EQ(42, result->currentTemperature());
    EXPECT_EQ(0xFFFF, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(254, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0, btSpecObj.cycleCount);
    EXPECT_EQ(42, btSpecObj.currentTemperature);
    EXPECT_EQ(0xFFFF, btSpecObj.deepDischargeCount);

    EXPECT_EQ("CycleCount: 0, CurrentTemperature: 42°C, DeepDischargeCount: 65535", result->toString());
}

TEST_F(BatteryHealthStatusTest, SummaryNo_CycleNormal_TemperatureNo_DeepMax_ReservedEven)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b10101010);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCount
        '\xFF', '\xFF'  // deepDischargeCount
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryHealthSummaryPresent());
    EXPECT_TRUE(result->isCycleCountPresent());
    EXPECT_FALSE(result->isCurrentTemperaturePresent());
    EXPECT_TRUE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0x2A00, result->cycleCount());
    EXPECT_EQ(0, result->currentTemperature());
    EXPECT_EQ(0xFFFF, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(170, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCount);
    EXPECT_EQ(0, btSpecObj.currentTemperature);
    EXPECT_EQ(0xFFFF, btSpecObj.deepDischargeCount);

    EXPECT_EQ("CycleCount: 10752, DeepDischargeCount: 65535", result->toString());
}

TEST_F(BatteryHealthStatusTest, Summary0_CycleNo_TemperatureLess_DeepNo_ReservedNone)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b00000101);
    constexpr char data[] = {
        flags,
        '\x00',         // batteryHealthSummary
        '\x80'          // currentTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryHealthSummaryPresent());
    EXPECT_FALSE(result->isCycleCountPresent());
    EXPECT_TRUE(result->isCurrentTemperaturePresent());
    EXPECT_FALSE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0, result->cycleCount());
    EXPECT_EQ(-128, result->currentTemperature());
    EXPECT_EQ(0, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_TRUE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(5, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0, btSpecObj.cycleCount);
    EXPECT_EQ(-128, btSpecObj.currentTemperature);
    EXPECT_EQ(0, btSpecObj.deepDischargeCount);

    EXPECT_EQ("BatteryHealthSummary: 0%, CurrentTemperature: <-127°C", result->toString());
}

TEST_F(BatteryHealthStatusTest, SummaryNo_CycleMax_TemperatureGreater_DeepNo_ReservedOdd)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b01010110);
    constexpr char data[] = {
        flags,
        '\xFF', '\xFF', // cycleCount
        '\x7F'          // currentTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryHealthSummaryPresent());
    EXPECT_TRUE(result->isCycleCountPresent());
    EXPECT_TRUE(result->isCurrentTemperaturePresent());
    EXPECT_FALSE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0xFFFF, result->cycleCount());
    EXPECT_EQ(127, result->currentTemperature());
    EXPECT_EQ(0, result->deepDischargeCount());
    EXPECT_TRUE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(86, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0xFFFF, btSpecObj.cycleCount);
    EXPECT_EQ(127, btSpecObj.currentTemperature);
    EXPECT_EQ(0, btSpecObj.deepDischargeCount);

    EXPECT_EQ("CycleCount: 65535, CurrentTemperature: >126°C", result->toString());
}

TEST_F(BatteryHealthStatusTest, Summary0_CycleNormal_Temperature0_DeepMax_ReservedNone)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b00001111);
    constexpr char data[] = {
        flags,
        '\x00',         // batteryHealthSummary
        '\x00', '\x2A', // cycleCount
        '\x00',         // currentTemperature
        '\xFF', '\xFF'  // deepDischargeCount
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryHealthSummaryPresent());
    EXPECT_TRUE(result->isCycleCountPresent());
    EXPECT_TRUE(result->isCurrentTemperaturePresent());
    EXPECT_TRUE(result->isDeepDischargeCountPresent());
    EXPECT_EQ(0, result->batteryHealthSummary());
    EXPECT_EQ(0x2A00, result->cycleCount());
    EXPECT_EQ(0, result->currentTemperature());
    EXPECT_EQ(0xFFFF, result->deepDischargeCount());
    EXPECT_FALSE(result->isCurrentTemperatureGreater());
    EXPECT_FALSE(result->isCurrentTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(15, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.batteryHealthSummary);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCount);
    EXPECT_EQ(0, btSpecObj.currentTemperature);
    EXPECT_EQ(0xFFFF, btSpecObj.deepDischargeCount);

    EXPECT_EQ("BatteryHealthSummary: 0%, CycleCount: 10752, CurrentTemperature: 0°C, DeepDischargeCount: 65535", result->toString());
}

TEST_F(BatteryHealthStatusTest, InvalidPercent)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b00000001);
    constexpr char data[] = {
        flags,
        '\x8E'  // batteryHealthSummary
    };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryHealthStatusTest, TooShort)
{
    auto result = bleValueParser.make_value<BatteryHealthStatus>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryHealthStatusTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryHealthStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryHealthStatusTest, ToString)
{
    //                         RRRRDTCS
    constexpr char flags = C(0b00001111);
    constexpr char data[] = {
        flags,
        '\x64',         // batteryHealthSummary
        '\x00', '\x2A', // cycleCount
        '\x2A',         // currentTemperature
        '\xFF', '\xFF'  // deepDischargeCount
    };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryHealthStatus,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("BatteryHealthSummary: 100%, CycleCount: 10752, CurrentTemperature: 42°C, DeepDischargeCount: 65535", result->toString());
}

}  // namespace bvp
