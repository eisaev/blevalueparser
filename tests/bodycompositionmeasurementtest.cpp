#include "gtest/gtest.h"

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

class BodyCompositionMeasurementTest : public testing::Test
{
protected:
    explicit BodyCompositionMeasurementTest() {}
    virtual ~BodyCompositionMeasurementTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(BodyCompositionMeasurementTest, FeaturesAll_SinglePacket_ReservedOdd)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10101111), C(0b11111110) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\x12', '\x34',                                         // bodyFatPercentage
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x2A',                                                 // userID
        '\x23', '\x45',                                         // basalMetabolism
        '\x34', '\x56',                                         // musclePercentage
        '\x45', '\x67',                                         // muscleMass
        '\x56', '\x78',                                         // fatFreeMass
        '\x67', '\x89',                                         // softLeanMass
        '\x78', '\x9A',                                         // bodyWaterMass
        '\x89', '\xAB',                                         // impedance
        '\x9A', '\xBC',                                         // weight
        '\xAB', '\xCD'                                          // height
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_TRUE(result->isUserIDPresent());
    EXPECT_TRUE(result->isBasalMetabolismPresent());
    EXPECT_TRUE(result->isMusclePercentagePresent());
    EXPECT_TRUE(result->isMuscleMassPresent());
    EXPECT_TRUE(result->isFatFreeMassPresent());
    EXPECT_TRUE(result->isSoftLeanMassPresent());
    EXPECT_TRUE(result->isBodyWaterMassPresent());
    EXPECT_TRUE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_TRUE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(42, result->userID());
    EXPECT_EQ(17699, result->basalMetabolism());
    EXPECT_FLOAT_EQ(2206.8, result->musclePercentage());
    EXPECT_FLOAT_EQ(132.185, result->muscleMass());
    EXPECT_FLOAT_EQ(154.03, result->fatFreeMass());
    EXPECT_FLOAT_EQ(175.875, result->softLeanMass());
    EXPECT_FLOAT_EQ(197.72, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(4391.3, result->impedance());
    EXPECT_FLOAT_EQ(241.40999, result->weight());
    EXPECT_FLOAT_EQ(52.651, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(45054, btSpecObj.flags);
    EXPECT_EQ(0x3412, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(42, btSpecObj.userID.userIndex);
    EXPECT_EQ(0x4523, btSpecObj.basalMetabolism);
    EXPECT_EQ(0x5634, btSpecObj.musclePercentage);
    EXPECT_EQ(0x6745, btSpecObj.muscleMass);
    EXPECT_EQ(0x7856, btSpecObj.fatFreeMass);
    EXPECT_EQ(0x8967, btSpecObj.softLeanMass);
    EXPECT_EQ(0x9A78, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0xAB89, btSpecObj.impedance);
    EXPECT_EQ(0xBC9A, btSpecObj.weight);
    EXPECT_EQ(0xCDAB, btSpecObj.height);

    EXPECT_EQ("BodyFatPercentage: 1333%, TimeStamp: 06.02.2023 18:28:00, UserID: 42, BasalMetabolism: 17699kJ, MusclePercentage: 2206.8%, MuscleMass: 132.185kg, FatFreeMass: 154.03kg, SoftLeanMass: 175.875kg, BodyWaterMass: 197.72kg, Impedance: 4391.3Ω, Weight: 241.41kg, Height: 52.651m", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(42, result->userID());
    EXPECT_EQ(17699, result->basalMetabolism());
    EXPECT_FLOAT_EQ(2206.8, result->musclePercentage());
    EXPECT_FLOAT_EQ(264.37, result->muscleMass());
    EXPECT_FLOAT_EQ(308.06, result->fatFreeMass());
    EXPECT_FLOAT_EQ(351.75, result->softLeanMass());
    EXPECT_FLOAT_EQ(395.44, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(4391.3, result->impedance());
    EXPECT_FLOAT_EQ(482.81998, result->weight());
    EXPECT_FLOAT_EQ(5265.1, result->height());
    EXPECT_EQ("BodyFatPercentage: 1333%, TimeStamp: 06.02.2023 18:28:00, UserID: 42, BasalMetabolism: 17699kJ, MusclePercentage: 2206.8%, MuscleMass: 264.37lb, FatFreeMass: 308.06lb, SoftLeanMass: 351.75lb, BodyWaterMass: 395.44lb, Impedance: 4391.3Ω, Weight: 482.82lb, Height: 5265.1in", result->toString());
}

TEST_F(BodyCompositionMeasurementTest, FeaturesNone_MultiplePacket_ReservedEven)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b01010000), C(0b00000000) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\x12', '\x34'                                          // bodyFatPercentage
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_FALSE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_FALSE(result->isImpedancePresent());
    EXPECT_FALSE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_TRUE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(0, result->year());
    EXPECT_EQ(0, result->month());
    EXPECT_EQ(0, result->day());
    EXPECT_EQ(0, result->hour());
    EXPECT_EQ(0, result->minute());
    EXPECT_EQ(0, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0, result->muscleMass());
    EXPECT_FLOAT_EQ(0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(0, result->impedance());
    EXPECT_FLOAT_EQ(0, result->weight());
    EXPECT_FLOAT_EQ(0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(20480, btSpecObj.flags);
    EXPECT_EQ(0x3412, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(0, btSpecObj.timeStamp.year);
    EXPECT_EQ(0, btSpecObj.timeStamp.month);
    EXPECT_EQ(0, btSpecObj.timeStamp.day);
    EXPECT_EQ(0, btSpecObj.timeStamp.hour);
    EXPECT_EQ(0, btSpecObj.timeStamp.minute);
    EXPECT_EQ(0, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0, btSpecObj.impedance);
    EXPECT_EQ(0, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("BodyFatPercentage: 1333%", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(0, result->year());
    EXPECT_EQ(0, result->month());
    EXPECT_EQ(0, result->day());
    EXPECT_EQ(0, result->hour());
    EXPECT_EQ(0, result->minute());
    EXPECT_EQ(0, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0, result->muscleMass());
    EXPECT_FLOAT_EQ(0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(0, result->impedance());
    EXPECT_FLOAT_EQ(0, result->weight());
    EXPECT_FLOAT_EQ(0, result->height());
    EXPECT_EQ("BodyFatPercentage: 1333%", result->toString());
}

TEST_F(BodyCompositionMeasurementTest, FeaturesOdd_SinglePacket_ReservedAll)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b11101010), C(0b10101010) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\x12', '\x34',                                         // bodyFatPercentage
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x23', '\x45',                                         // basalMetabolism
        '\x45', '\x67',                                         // muscleMass
        '\x67', '\x89',                                         // softLeanMass
        '\x89', '\xAB',                                         // impedance
        '\xAB', '\xCD'                                          // height
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_TRUE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_TRUE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_TRUE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_TRUE(result->isImpedancePresent());
    EXPECT_FALSE(result->isWeightPresent());
    EXPECT_TRUE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(17699, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(132.185, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(175.875, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(4391.3, result->impedance());
    EXPECT_FLOAT_EQ(0.0, result->weight());
    EXPECT_FLOAT_EQ(52.651, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(60074, btSpecObj.flags);
    EXPECT_EQ(0x3412, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0x4523, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0x6745, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0x8967, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0xAB89, btSpecObj.impedance);
    EXPECT_EQ(0, btSpecObj.weight);
    EXPECT_EQ(0xCDAB, btSpecObj.height);

    EXPECT_EQ("BodyFatPercentage: 1333%, TimeStamp: 06.02.2023 18:28:00, BasalMetabolism: 17699kJ, MuscleMass: 132.185kg, SoftLeanMass: 175.875kg, Impedance: 4391.3Ω, Height: 52.651m", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(17699, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(264.37, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(351.75, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(4391.3, result->impedance());
    EXPECT_FLOAT_EQ(0.0, result->weight());
    EXPECT_FLOAT_EQ(5265.1, result->height());
    EXPECT_EQ("BodyFatPercentage: 1333%, TimeStamp: 06.02.2023 18:28:00, BasalMetabolism: 17699kJ, MuscleMass: 264.37lb, SoftLeanMass: 351.75lb, Impedance: 4391.3Ω, Height: 5265.1in", result->toString());
}

TEST_F(BodyCompositionMeasurementTest, FeaturesEven_MultiplePacket_ReservedNone)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b00010101), C(0b01010100) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\x12', '\x34',                                         // bodyFatPercentage
        '\x2A',                                                 // userID
        '\x34', '\x56',                                         // musclePercentage
        '\x56', '\x78',                                         // fatFreeMass
        '\x78', '\x9A',                                         // bodyWaterMass
        '\x9A', '\xBC'                                          // weight
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_FALSE(result->isTimeStampPresent());
    EXPECT_TRUE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_TRUE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_TRUE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_TRUE(result->isBodyWaterMassPresent());
    EXPECT_FALSE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_TRUE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(0, result->year());
    EXPECT_EQ(0, result->month());
    EXPECT_EQ(0, result->day());
    EXPECT_EQ(0, result->hour());
    EXPECT_EQ(0, result->minute());
    EXPECT_EQ(0, result->seconds());
    EXPECT_EQ(42, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(2206.8, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(154.03, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(197.72, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(0.0, result->impedance());
    EXPECT_FLOAT_EQ(241.40999, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(5460, btSpecObj.flags);
    EXPECT_EQ(0x3412, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(0, btSpecObj.timeStamp.year);
    EXPECT_EQ(0, btSpecObj.timeStamp.month);
    EXPECT_EQ(0, btSpecObj.timeStamp.day);
    EXPECT_EQ(0, btSpecObj.timeStamp.hour);
    EXPECT_EQ(0, btSpecObj.timeStamp.minute);
    EXPECT_EQ(0, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(42, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0x5634, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0x7856, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0x9A78, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0, btSpecObj.impedance);
    EXPECT_EQ(0xBC9A, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("BodyFatPercentage: 1333%, UserID: 42, MusclePercentage: 2206.8%, FatFreeMass: 154.03kg, BodyWaterMass: 197.72kg, Weight: 241.41kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(0, result->year());
    EXPECT_EQ(0, result->month());
    EXPECT_EQ(0, result->day());
    EXPECT_EQ(0, result->hour());
    EXPECT_EQ(0, result->minute());
    EXPECT_EQ(0, result->seconds());
    EXPECT_EQ(42, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(2206.8, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(308.06, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(395.44, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(0.0, result->impedance());
    EXPECT_FLOAT_EQ(482.81998, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());
    EXPECT_EQ("BodyFatPercentage: 1333%, UserID: 42, MusclePercentage: 2206.8%, FatFreeMass: 308.06lb, BodyWaterMass: 395.44lb, Weight: 482.82lb", result->toString());
}

TEST_F(BodyCompositionMeasurementTest, MeasurementUnsuccessful)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b00000000), C(0b00000000) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\xFF', '\xFF'                                          // bodyFatPercentage
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isMeasurementUnsuccessful());

    EXPECT_EQ("<MeasurementUnsuccessful>", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ("<MeasurementUnsuccessful>", result->toString());
}

TEST_F(BodyCompositionMeasurementTest, Imperial)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10101111), C(0b11111111) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\x12', '\x34',                                         // bodyFatPercentage
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x2A',                                                 // userID
        '\x23', '\x45',                                         // basalMetabolism
        '\x34', '\x56',                                         // musclePercentage
        '\x45', '\x67',                                         // muscleMass
        '\x56', '\x78',                                         // fatFreeMass
        '\x67', '\x89',                                         // softLeanMass
        '\x78', '\x9A',                                         // bodyWaterMass
        '\x89', '\xAB',                                         // impedance
        '\x9A', '\xBC',                                         // weight
        '\xAB', '\xCD'                                          // height
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurement>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::Imperial, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_TRUE(result->isUserIDPresent());
    EXPECT_TRUE(result->isBasalMetabolismPresent());
    EXPECT_TRUE(result->isMusclePercentagePresent());
    EXPECT_TRUE(result->isMuscleMassPresent());
    EXPECT_TRUE(result->isFatFreeMassPresent());
    EXPECT_TRUE(result->isSoftLeanMassPresent());
    EXPECT_TRUE(result->isBodyWaterMassPresent());
    EXPECT_TRUE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_TRUE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(1333.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(42, result->userID());
    EXPECT_EQ(17699, result->basalMetabolism());
    EXPECT_FLOAT_EQ(2206.8, result->musclePercentage());
    EXPECT_FLOAT_EQ(264.37, result->muscleMass());
    EXPECT_FLOAT_EQ(308.06, result->fatFreeMass());
    EXPECT_FLOAT_EQ(351.75, result->softLeanMass());
    EXPECT_FLOAT_EQ(395.44, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(4391.3, result->impedance());
    EXPECT_FLOAT_EQ(482.81998, result->weight());
    EXPECT_FLOAT_EQ(5265.1, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(45055, btSpecObj.flags);
    EXPECT_EQ(0x3412, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(42, btSpecObj.userID.userIndex);
    EXPECT_EQ(0x4523, btSpecObj.basalMetabolism);
    EXPECT_EQ(0x5634, btSpecObj.musclePercentage);
    EXPECT_EQ(0x6745, btSpecObj.muscleMass);
    EXPECT_EQ(0x7856, btSpecObj.fatFreeMass);
    EXPECT_EQ(0x8967, btSpecObj.softLeanMass);
    EXPECT_EQ(0x9A78, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0xAB89, btSpecObj.impedance);
    EXPECT_EQ(0xBC9A, btSpecObj.weight);
    EXPECT_EQ(0xCDAB, btSpecObj.height);

    EXPECT_EQ("BodyFatPercentage: 1333%, TimeStamp: 06.02.2023 18:28:00, UserID: 42, BasalMetabolism: 17699kJ, MusclePercentage: 2206.8%, MuscleMass: 264.37lb, FatFreeMass: 308.06lb, SoftLeanMass: 351.75lb, BodyWaterMass: 395.44lb, Impedance: 4391.3Ω, Weight: 482.82lb, Height: 5265.1in", result->toString());
}

TEST_F(BodyCompositionMeasurementTest, ToString)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10101111), C(0b11111110) };
    constexpr char data[] = {
        flags[1], flags[0],                                     // flags
        '\x12', '\x34',                                         // bodyFatPercentage
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x2A',                                                 // userID
        '\x23', '\x45',                                         // basalMetabolism
        '\x34', '\x56',                                         // musclePercentage
        '\x45', '\x67',                                         // muscleMass
        '\x56', '\x78',                                         // fatFreeMass
        '\x67', '\x89',                                         // softLeanMass
        '\x78', '\x9A',                                         // bodyWaterMass
        '\x89', '\xAB',                                         // impedance
        '\x9A', '\xBC',                                         // weight
        '\xAB', '\xCD'                                          // height
    };

    auto result = bleValueParser.make_value(CharacteristicType::BodyCompositionMeasurement,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("BodyFatPercentage: 1333%, TimeStamp: 06.02.2023 18:28:00, UserID: 42, BasalMetabolism: 17699kJ, MusclePercentage: 2206.8%, MuscleMass: 132.185kg, FatFreeMass: 154.03kg, SoftLeanMass: 175.875kg, BodyWaterMass: 197.72kg, Impedance: 4391.3Ω, Weight: 241.41kg, Height: 52.651m", result->toString());
}

}  // namespace bvp
