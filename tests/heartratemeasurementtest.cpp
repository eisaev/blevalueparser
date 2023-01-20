#include "gtest/gtest.h"

#include "blevalueparser.h"


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
    constexpr char flags = 0b00000100;
    constexpr char data[] = { flags, '\xAA' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());
    EXPECT_EQ("(disconnected) HR: 170bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, ContactsSupportedConnected)
{
    constexpr char flags = 0b00000110;
    constexpr char data[] = { flags, '\xAA' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isContactSupported());
    EXPECT_TRUE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());
    EXPECT_EQ("(connected) HR: 170bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8)
{
    constexpr char flags = 0b00000000;
    constexpr char data[] = { flags, '\xAA' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());
    EXPECT_EQ("HR: 170bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16)
{
    constexpr char flags = 0b00000001;
    constexpr char data[] = { flags, '\xAA', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());
    EXPECT_EQ("HR: 426bpm", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_EE)
{
    constexpr char flags = 0b00001000;
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());
    EXPECT_EQ("HR: 170bpm, EE: 443kJ", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16_EE)
{
    constexpr char flags = 0b00001001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_TRUE(result->rrIntervals().empty());
    EXPECT_EQ("HR: 426bpm, EE: 443kJ", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_EE_RR1)
{
    constexpr char flags = 0b00011000;
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01', '\xCC', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(1, result->rrIntervals().size());
    EXPECT_EQ(0x01CC, result->rrIntervals().at(0));
    EXPECT_EQ("HR: 170bpm, EE: 443kJ, RR: { 460ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_RR9)
{
    constexpr char flags = 0b00010000;
    constexpr char data[] = { flags, '\xAA', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01', '\xA9', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(9, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ(0x01A8, result->rrIntervals().at(7));
    EXPECT_EQ(0x01A9, result->rrIntervals().at(8));
    EXPECT_EQ("HR: 170bpm, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; 424ms; 425ms; }", result->toString());
}

// 10th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR8_RR10)
{
    constexpr char flags = 0b00010000;
    constexpr char data[] = { flags, '\xAA', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01', '\xA9', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(9, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ(0x01A8, result->rrIntervals().at(7));
    EXPECT_EQ(0x01A9, result->rrIntervals().at(8));
    EXPECT_EQ("HR: 170bpm, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; 424ms; 425ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR8_EE_RR8)
{
    constexpr char flags = 0b00011000;
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ(0x01A8, result->rrIntervals().at(7));
    EXPECT_EQ("HR: 170bpm, EE: 443kJ, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; 424ms; }", result->toString());
}

// 9th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR8_EE_RR9)
{
    constexpr char flags = 0b00011000;
    constexpr char data[] = { flags, '\xAA', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0xAA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ(0x01A8, result->rrIntervals().at(7));
    EXPECT_EQ("HR: 170bpm, EE: 443kJ, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; 424ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16_RR8)
{
    constexpr char flags = 0b00010001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ(0x01A8, result->rrIntervals().at(7));
    EXPECT_EQ("HR: 426bpm, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; 424ms; }", result->toString());
}

// 9th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR16_RR9)
{
    constexpr char flags = 0b00010001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_FALSE(result->hasEnergyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(8, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ(0x01A8, result->rrIntervals().at(7));
    EXPECT_EQ("HR: 426bpm, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; 424ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, HR16_EE_RR7)
{
    constexpr char flags = 0b00011001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(7, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ("HR: 426bpm, EE: 443kJ, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; }", result->toString());
}

// 8th RR-Interval should be ignored in this case
TEST_F(HeartRateMeasurementTest, HR16_EE_RR8)
{
    constexpr char flags = 0b00011001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isContactSupported());
    EXPECT_FALSE(result->isContacted());
    EXPECT_EQ(0x01AA, result->heartRate());
    EXPECT_TRUE(result->hasEnergyExpended());
    EXPECT_EQ(0x01BB, result->energyExpended());
    EXPECT_FALSE(result->rrIntervals().empty());
    EXPECT_EQ(7, result->rrIntervals().size());
    EXPECT_EQ(0x01A1, result->rrIntervals().at(0));
    EXPECT_EQ(0x01A2, result->rrIntervals().at(1));
    EXPECT_EQ(0x01A3, result->rrIntervals().at(2));
    EXPECT_EQ(0x01A4, result->rrIntervals().at(3));
    EXPECT_EQ(0x01A5, result->rrIntervals().at(4));
    EXPECT_EQ(0x01A6, result->rrIntervals().at(5));
    EXPECT_EQ(0x01A7, result->rrIntervals().at(6));
    EXPECT_EQ("HR: 426bpm, EE: 443kJ, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; }", result->toString());
}

TEST_F(HeartRateMeasurementTest, TooShort)
{
    constexpr char flags = 0b00000000;
    constexpr char data[] = { flags };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateMeasurementTest, TooLong)
{
    constexpr char flags = 0b00011001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01', '\xA8', '\x01' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateMeasurementTest, BrokenPacket)
{
    constexpr char flags = 0b00000001;
    constexpr char data[] = { flags, '\xAA' };
    auto result = bleValueParser.make_value<HeartRateMeasurement>(data, sizeof(data));
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(HeartRateMeasurementTest, ToString)
{
    constexpr char flags = 0b00011001;
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };
    auto result = bleValueParser.make_value(CharacteristicType::HeartRateMeasurement,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ("HR: 426bpm, EE: 443kJ, RR: { 417ms; 418ms; 419ms; 420ms; 421ms; 422ms; 423ms; }", result->toString());
}

}  // namespace bvp
