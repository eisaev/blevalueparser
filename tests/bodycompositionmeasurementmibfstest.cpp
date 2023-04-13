#include "gtest/gtest.h"

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BodyCompositionMeasurementMIBFSTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BodyCompositionMeasurementMIBFSTest, NoImpendance_Unstable_Loaded)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b00000100), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurementMIBFS>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_FALSE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(154.03, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1026, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0x3412, btSpecObj.impedance);
    EXPECT_EQ(0x7856, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("Unstable, TimeStamp: 06.02.2023 18:28:00, Weight: 154.03kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(308.06, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());
    EXPECT_EQ("Unstable, TimeStamp: 06.02.2023 18:28:00, Weight: 308.06lb", result->toString());
}

TEST_F(BodyCompositionMeasurementMIBFSTest, HasImpendance_Stabilized_Loaded)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b00100110), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurementMIBFS>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_TRUE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(154.03, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(9730, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0x3412, btSpecObj.impedance);
    EXPECT_EQ(0x7856, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("Stabilized, TimeStamp: 06.02.2023 18:28:00, Impedance: 1333Ω, Weight: 154.03kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(308.06, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());
    EXPECT_EQ("Stabilized, TimeStamp: 06.02.2023 18:28:00, Impedance: 1333Ω, Weight: 308.06lb", result->toString());
}

TEST_F(BodyCompositionMeasurementMIBFSTest, NoImpendance_Unstable_Unloaded)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10000100), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurementMIBFS>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_FALSE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(154.03, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(33794, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0x3412, btSpecObj.impedance);
    EXPECT_EQ(0x7856, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("Unloaded, TimeStamp: 06.02.2023 18:28:00, Weight: 154.03kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(308.06, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());
    EXPECT_EQ("Unloaded, TimeStamp: 06.02.2023 18:28:00, Weight: 308.06lb", result->toString());
}

TEST_F(BodyCompositionMeasurementMIBFSTest, HasImpendance_Stabilized_Unloaded)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10100110), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurementMIBFS>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::SI, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_TRUE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(154.03, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(42498, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0x3412, btSpecObj.impedance);
    EXPECT_EQ(0x7856, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("Unloaded, TimeStamp: 06.02.2023 18:28:00, Impedance: 1333Ω, Weight: 154.03kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(308.06, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());
    EXPECT_EQ("Unloaded, TimeStamp: 06.02.2023 18:28:00, Impedance: 1333Ω, Weight: 308.06lb", result->toString());
}

TEST_F(BodyCompositionMeasurementMIBFSTest, Imperial)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b00000100), C(0b00000011) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    auto result = bleValueParser.make_value<BodyCompositionMeasurementMIBFS>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isMeasurementUnsuccessful());
    EXPECT_EQ(MeasurementUnitsEnum::Imperial, result->measurementUnits());
    EXPECT_TRUE(result->isTimeStampPresent());
    EXPECT_FALSE(result->isUserIDPresent());
    EXPECT_FALSE(result->isBasalMetabolismPresent());
    EXPECT_FALSE(result->isMusclePercentagePresent());
    EXPECT_FALSE(result->isMuscleMassPresent());
    EXPECT_FALSE(result->isFatFreeMassPresent());
    EXPECT_FALSE(result->isSoftLeanMassPresent());
    EXPECT_FALSE(result->isBodyWaterMassPresent());
    EXPECT_FALSE(result->isImpedancePresent());
    EXPECT_TRUE(result->isWeightPresent());
    EXPECT_FALSE(result->isHeightPresent());
    EXPECT_FALSE(result->isMultiplePacketMeasurement());
    EXPECT_FLOAT_EQ(0.0, result->bodyFatPercentage());
    EXPECT_EQ(2023, result->year());
    EXPECT_EQ(02, result->month());
    EXPECT_EQ(06, result->day());
    EXPECT_EQ(18, result->hour());
    EXPECT_EQ(28, result->minute());
    EXPECT_EQ(00, result->seconds());
    EXPECT_EQ(0, result->userID());
    EXPECT_EQ(0, result->basalMetabolism());
    EXPECT_FLOAT_EQ(0.0, result->musclePercentage());
    EXPECT_FLOAT_EQ(0.0, result->muscleMass());
    EXPECT_FLOAT_EQ(0.0, result->fatFreeMass());
    EXPECT_FLOAT_EQ(0.0, result->softLeanMass());
    EXPECT_FLOAT_EQ(0.0, result->bodyWaterMass());
    EXPECT_FLOAT_EQ(1333.0, result->impedance());
    EXPECT_FLOAT_EQ(308.06, result->weight());
    EXPECT_FLOAT_EQ(0.0, result->height());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1027, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.bodyFatPercentage);
    EXPECT_EQ(2023, btSpecObj.timeStamp.year);
    EXPECT_EQ(02, btSpecObj.timeStamp.month);
    EXPECT_EQ(06, btSpecObj.timeStamp.day);
    EXPECT_EQ(18, btSpecObj.timeStamp.hour);
    EXPECT_EQ(28, btSpecObj.timeStamp.minute);
    EXPECT_EQ(00, btSpecObj.timeStamp.seconds);
    EXPECT_EQ(0, btSpecObj.userID.userIndex);
    EXPECT_EQ(0, btSpecObj.basalMetabolism);
    EXPECT_EQ(0, btSpecObj.musclePercentage);
    EXPECT_EQ(0, btSpecObj.muscleMass);
    EXPECT_EQ(0, btSpecObj.fatFreeMass);
    EXPECT_EQ(0, btSpecObj.softLeanMass);
    EXPECT_EQ(0, btSpecObj.bodyWaterMass);
    EXPECT_EQ(0x3412, btSpecObj.impedance);
    EXPECT_EQ(0x7856, btSpecObj.weight);
    EXPECT_EQ(0, btSpecObj.height);

    EXPECT_EQ("Unstable, TimeStamp: 06.02.2023 18:28:00, Weight: 308.06lb", result->toString());
}

TEST_F(BodyCompositionMeasurementMIBFSTest, ToString)
{
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b00000100), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x00', '\x00',                                         // impedance
        '\xE0', '\x38'                                          // weight
    };

    auto result = bleValueParser.make_value(CharacteristicType::BodyCompositionMeasurementMIBFS,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Unstable, TimeStamp: 06.02.2023 18:28:00, Weight: 72.8kg", result->toString());
}

}  // namespace bvp
