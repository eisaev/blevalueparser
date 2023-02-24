#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

class HeartRateMeasurementTest : public testing::Test
{
protected:
    explicit HeartRateMeasurementTest() {}
    virtual ~HeartRateMeasurementTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(HeartRateMeasurementTest, ContactsSupportedNotConnected)
{
    constexpr char flags = C(0b00000100);
    constexpr char data[] = { flags, '\xAA' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(4, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_TRUE(btSpecObj.rrIntervals.empty());

    EXPECT_EQ("(disconnected) HR: 170bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, ContactsSupportedConnected)
{
    constexpr char flags = C(0b00000110);
    constexpr char data[] = { flags, '\xAA' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isContactSupported());
    EXPECT_TRUE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(6, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_TRUE(btSpecObj.rrIntervals.empty());

    EXPECT_EQ("(connected) HR: 170bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8)
{
    constexpr char flags = C(0b00000000);
    constexpr char data[] = { flags, '\xAA' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(0, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_TRUE(btSpecObj.rrIntervals.empty());

    EXPECT_EQ("HR: 170bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16)
{
    constexpr char flags = C(0b00000001);
    constexpr char data[] = { flags, '\xAA', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1, btSpecObj.flags);
    EXPECT_EQ(0x01AA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_TRUE(btSpecObj.rrIntervals.empty());

    EXPECT_EQ("HR: 426bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_EE)
{
    constexpr char flags = C(0b00001000);
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(8, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_TRUE(btSpecObj.rrIntervals.empty());

    EXPECT_EQ("HR: 170bpm, EE: 443kJ", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16_EE)
{
    constexpr char flags = C(0b00001001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(9, btSpecObj.flags);
    EXPECT_EQ(0x01AA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_TRUE(btSpecObj.rrIntervals.empty());

    EXPECT_EQ("HR: 426bpm, EE: 443kJ", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_EE_RR1)
{
    constexpr char flags = C(0b00011000);
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01', '\xCC', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(1, result->rrIntervals().size());
    EXPECT_EQ(449, result->rrIntervals().at(0));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(24, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(1, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01CC, btSpecObj.rrIntervals.at(0));

    EXPECT_EQ("HR: 170bpm, EE: 443kJ, RR: { 449ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_RR9)
{
    constexpr char flags = C(0b00010000);
    constexpr char data[] = { flags, '\xAA', '\x00', '\x00', '\x01', '\x00', '\x02', '\x00', '\x03', '\x00', '\xF3', '\x03', '\xFC', '\xFF', '\xFD', '\xFF', '\xFE', '\xFF', '\xFF', '\xFF' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(    9, result->rrIntervals().size());
    EXPECT_EQ(    0, result->rrIntervals().at(0));
    EXPECT_EQ(    0, result->rrIntervals().at(1));
    EXPECT_EQ(    1, result->rrIntervals().at(2));
    EXPECT_EQ(    2, result->rrIntervals().at(3));
    EXPECT_EQ(  987, result->rrIntervals().at(4));
    EXPECT_EQ(63996, result->rrIntervals().at(5));
    EXPECT_EQ(63997, result->rrIntervals().at(6));
    EXPECT_EQ(63998, result->rrIntervals().at(7));
    EXPECT_EQ(63999, result->rrIntervals().at(8));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(16, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(9, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x0000, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x0001, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x0002, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x0003, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x03F3, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0xFFFC, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0xFFFD, btSpecObj.rrIntervals.at(6));
    EXPECT_EQ(0xFFFE, btSpecObj.rrIntervals.at(7));
    EXPECT_EQ(0xFFFF, btSpecObj.rrIntervals.at(8));

    EXPECT_EQ("HR: 170bpm, RR: { 0ms; 0ms; 1ms; 2ms; 987ms; 63996ms; 63997ms; 63998ms; 63999ms; }", result->toString());
}

// 10th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR8_RR10)
{
    constexpr char flags = C(0b00010000);
    constexpr char data[] = { flags, '\xAA', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01', '\xA9', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(9, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));
    EXPECT_EQ(414, result->rrIntervals().at(7));
    EXPECT_EQ(415, result->rrIntervals().at(8));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(16, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(9, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));
    EXPECT_EQ(0x01A8, btSpecObj.rrIntervals.at(7));
    EXPECT_EQ(0x01A9, btSpecObj.rrIntervals.at(8));

    EXPECT_EQ("HR: 170bpm, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; 414ms; 415ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_EE_RR8)
{
    constexpr char flags = C(0b00011000);
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));
    EXPECT_EQ(414, result->rrIntervals().at(7));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(24, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(8, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));
    EXPECT_EQ(0x01A8, btSpecObj.rrIntervals.at(7));

    EXPECT_EQ("HR: 170bpm, EE: 443kJ, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; 414ms; }", result->toString());
}

// 9th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR8_EE_RR9)
{
    constexpr char flags = C(0b00011000);
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));
    EXPECT_EQ(414, result->rrIntervals().at(7));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(24, btSpecObj.flags);
    EXPECT_EQ(0xAA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(8, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));
    EXPECT_EQ(0x01A8, btSpecObj.rrIntervals.at(7));

    EXPECT_EQ("HR: 170bpm, EE: 443kJ, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; 414ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16_RR8)
{
    constexpr char flags = C(0b00010001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));
    EXPECT_EQ(414, result->rrIntervals().at(7));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(17, btSpecObj.flags);
    EXPECT_EQ(0x01AA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(8, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));
    EXPECT_EQ(0x01A8, btSpecObj.rrIntervals.at(7));

    EXPECT_EQ("HR: 426bpm, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; 414ms; }", result->toString());
}

// 9th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR16_RR9)
{
    constexpr char flags = C(0b00010001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));
    EXPECT_EQ(414, result->rrIntervals().at(7));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(17, btSpecObj.flags);
    EXPECT_EQ(0x01AA, btSpecObj.heartRate);
    EXPECT_EQ(0, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(8, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));
    EXPECT_EQ(0x01A8, btSpecObj.rrIntervals.at(7));

    EXPECT_EQ("HR: 426bpm, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; 414ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16_EE_RR7)
{
    constexpr char flags = C(0b00011001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(7, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(25, btSpecObj.flags);
    EXPECT_EQ(0x01AA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(7, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));

    EXPECT_EQ("HR: 426bpm, EE: 443kJ, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; }", result->toString());
}

// 8th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR16_EE_RR8)
{
    constexpr char flags = C(0b00011001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(7, result->rrIntervals().size());
    EXPECT_EQ(407, result->rrIntervals().at(0));
    EXPECT_EQ(408, result->rrIntervals().at(1));
    EXPECT_EQ(409, result->rrIntervals().at(2));
    EXPECT_EQ(410, result->rrIntervals().at(3));
    EXPECT_EQ(411, result->rrIntervals().at(4));
    EXPECT_EQ(412, result->rrIntervals().at(5));
    EXPECT_EQ(413, result->rrIntervals().at(6));

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(25, btSpecObj.flags);
    EXPECT_EQ(0x01AA, btSpecObj.heartRate);
    EXPECT_EQ(0x01BB, btSpecObj.energyExpended);
    EXPECT_FALSE(btSpecObj.rrIntervals.empty());
    EXPECT_EQ(7, btSpecObj.rrIntervals.size());
    EXPECT_EQ(0x01A1, btSpecObj.rrIntervals.at(0));
    EXPECT_EQ(0x01A2, btSpecObj.rrIntervals.at(1));
    EXPECT_EQ(0x01A3, btSpecObj.rrIntervals.at(2));
    EXPECT_EQ(0x01A4, btSpecObj.rrIntervals.at(3));
    EXPECT_EQ(0x01A5, btSpecObj.rrIntervals.at(4));
    EXPECT_EQ(0x01A6, btSpecObj.rrIntervals.at(5));
    EXPECT_EQ(0x01A7, btSpecObj.rrIntervals.at(6));

    EXPECT_EQ("HR: 426bpm, EE: 443kJ, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, TooShort)
{
    constexpr char flags = C(0b00000000);
    constexpr char data[] = { flags };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateMeasurementTest, TooLong)
{
    constexpr char flags = C(0b00011001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateMeasurementTest, BrokenPacket)
{
    constexpr char flags = C(0b00000001);
    constexpr char data[] = { flags, '\xAA' };

    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateMeasurementTest, ToString)
{
    constexpr char flags = C(0b00011001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };

    auto result = bleValueParser.make_value(CharacteristicType::HeartRateMeasurement,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("HR: 426bpm, EE: 443kJ, RR: { 407ms; 408ms; 409ms; 410ms; 411ms; 412ms; 413ms; }", result->toString());
}

}  // namespace bvp
