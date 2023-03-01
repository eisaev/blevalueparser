#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BatteryHealthInformationTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BatteryHealthInformationTest, CycleNo_TemperatureNo_ReservedAll)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b11111100);
    constexpr char data[] = {
        flags
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_FALSE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0, result->cycleCountDesignedLifetime());
    EXPECT_EQ(0, result->minDesignedOperatingTemperature());
    EXPECT_EQ(0, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(252, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(0, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(0, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("<NoData>", result->toString());
}

TEST_F(BatteryHealthInformationTest, Cycle0_TemperatureNo_ReservedOdd)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b01010101);
    constexpr char data[] = {
        flags,
        '\x00', '\x00'  // cycleCountDesignedLifetime
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_FALSE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0, result->cycleCountDesignedLifetime());
    EXPECT_EQ(0, result->minDesignedOperatingTemperature());
    EXPECT_EQ(0, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(85, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(0, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(0, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 0", result->toString());
}

TEST_F(BatteryHealthInformationTest, CycleNormal_TemperatureMinMax_ReservedNone)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCountDesignedLifetime
        '\x81',         // minDesignedOperatingTemperature
        '\x7E'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0x2A00, result->cycleCountDesignedLifetime());
    EXPECT_EQ(-127, result->minDesignedOperatingTemperature());
    EXPECT_EQ(126, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(3, btSpecObj.flags);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(-127, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(126, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 10752, MinDesignedOperatingTemperature: -127°C, MaxDesignedOperatingTemperature: 126°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, CycleMax_TemperatureLessGreater_ReservedPat1)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b01111011);
    constexpr char data[] = {
        flags,
        '\xFF', '\xFF', // cycleCountDesignedLifetime
        '\x80',         // minDesignedOperatingTemperature
        '\x7F'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0xFFFF, result->cycleCountDesignedLifetime());
    EXPECT_EQ(-128, result->minDesignedOperatingTemperature());
    EXPECT_EQ(127, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_TRUE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_TRUE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(123, btSpecObj.flags);
    EXPECT_EQ(0xFFFF, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(-128, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(127, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 65535, MinDesignedOperatingTemperature: <-127°C, MaxDesignedOperatingTemperature: >126°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, CycleNo_TemperatureLessMax_ReservedEven)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b10101010);
    constexpr char data[] = {
        flags,
        '\x80',         // minDesignedOperatingTemperature
        '\x7E'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0, result->cycleCountDesignedLifetime());
    EXPECT_EQ(-128, result->minDesignedOperatingTemperature());
    EXPECT_EQ(126, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_TRUE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(170, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(-128, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(126, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("MinDesignedOperatingTemperature: <-127°C, MaxDesignedOperatingTemperature: 126°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, Cycle0_TemperatureMinGreater_ReservedPat2)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b01001011);
    constexpr char data[] = {
        flags,
        '\x00', '\x00', // cycleCountDesignedLifetime
        '\x81',         // minDesignedOperatingTemperature
        '\x7F'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0, result->cycleCountDesignedLifetime());
    EXPECT_EQ(-127, result->minDesignedOperatingTemperature());
    EXPECT_EQ(127, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_TRUE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(75, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(-127, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(127, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 0, MinDesignedOperatingTemperature: -127°C, MaxDesignedOperatingTemperature: >126°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, CycleNormal_Temperature0Normal_ReservedPat3)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b10110111);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCountDesignedLifetime
        '\x00',         // minDesignedOperatingTemperature
        '\x2A'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0x2A00, result->cycleCountDesignedLifetime());
    EXPECT_EQ(0, result->minDesignedOperatingTemperature());
    EXPECT_EQ(42, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(183, btSpecObj.flags);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(0, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(42, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 10752, MinDesignedOperatingTemperature: 0°C, MaxDesignedOperatingTemperature: 42°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, CycleNormal_TemperatureLessLess_ReservedPat3)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b10110111);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCountDesignedLifetime
        '\x80',         // minDesignedOperatingTemperature
        '\x80'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0x2A00, result->cycleCountDesignedLifetime());
    EXPECT_EQ(-128, result->minDesignedOperatingTemperature());
    EXPECT_EQ(-128, result->maxDesignedOperatingTemperature());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_TRUE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_TRUE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(183, btSpecObj.flags);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(-128, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(-128, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 10752, MinDesignedOperatingTemperature: <-127°C, MaxDesignedOperatingTemperature: <-127°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, CycleNormal_TemperatureGreaterGreater_ReservedPat3)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b10110111);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCountDesignedLifetime
        '\x7F',         // minDesignedOperatingTemperature
        '\x7F'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isCycleCountDesignedLifetimePresent());
    EXPECT_TRUE(result->isMinAndMaxDesignedOperatingTemperaturePresent());
    EXPECT_EQ(0x2A00, result->cycleCountDesignedLifetime());
    EXPECT_EQ(127, result->minDesignedOperatingTemperature());
    EXPECT_EQ(127, result->maxDesignedOperatingTemperature());
    EXPECT_TRUE(result->isMinDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMinDesignedOperatingTemperatureLess());
    EXPECT_TRUE(result->isMaxDesignedOperatingTemperatureGreater());
    EXPECT_FALSE(result->isMaxDesignedOperatingTemperatureLess());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(183, btSpecObj.flags);
    EXPECT_EQ(0x2A00, btSpecObj.cycleCountDesignedLifetime);
    EXPECT_EQ(127, btSpecObj.minDesignedOperatingTemperature);
    EXPECT_EQ(127, btSpecObj.maxDesignedOperatingTemperature);

    EXPECT_EQ("CycleCountDesignedLifetime: 10752, MinDesignedOperatingTemperature: >126°C, MaxDesignedOperatingTemperature: >126°C", result->toString());
}

TEST_F(BatteryHealthInformationTest, InvalidTemperatureRange)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\xFF', '\xFF', // cycleCountDesignedLifetime
        '\x7E',         // minDesignedOperatingTemperature
        '\x81'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryHealthInformationTest, TooShort)
{
    auto result = bleValueParser.make_value<BatteryHealthInformation>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryHealthInformationTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryHealthInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryHealthInformationTest, ToString)
{
    //                         RRRRRRTC
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x00', // cycleCountDesignedLifetime
        '\x00',         // minDesignedOperatingTemperature
        '\x2A'          // maxDesignedOperatingTemperature
    };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryHealthInformation,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("CycleCountDesignedLifetime: 0, MinDesignedOperatingTemperature: 0°C, MaxDesignedOperatingTemperature: 42°C", result->toString());
}

}  // namespace bvp
