#include "gtest/gtest.h"

#include "blevalueparser.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

class BodyCompositionFeatureTest : public testing::Test
{
protected:
    explicit BodyCompositionFeatureTest() {}
    virtual ~BodyCompositionFeatureTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(BodyCompositionFeatureTest, FeaturesAll_WeightResNotSpec_HeightResNotSpec_ReservedEven)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b10101010), C(0b10101000), C(0b00000111), C(0b11111111) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeStampSupported());
    EXPECT_TRUE(result->isMultipleUsersSupported());
    EXPECT_TRUE(result->isBasalMetabolismSupported());
    EXPECT_TRUE(result->isMusclePercentageSupported());
    EXPECT_TRUE(result->isMuscleMassSupported());
    EXPECT_TRUE(result->isFatFreeMassSupported());
    EXPECT_TRUE(result->isSoftLeanMassSupported());
    EXPECT_TRUE(result->isBodyWaterMassSupported());
    EXPECT_TRUE(result->isImpedanceSupported());
    EXPECT_TRUE(result->isWeightSupported());
    EXPECT_TRUE(result->isHeightSupported());
    EXPECT_EQ(0, result->weightResolution());
    EXPECT_EQ(0, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2863138815, btSpecObj.flags);

    EXPECT_EQ("Features: { TimeStamp MultipleUsers BasalMetabolism MusclePercentage MuscleMass FatFreeMass SoftLeanMass BodyWaterMass Impedance Weight Height }, WeightResolution: 0kg, HeightResolution: 0m", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(0, result->weightResolution());
    EXPECT_EQ(0, result->heightResolution());
    EXPECT_EQ("Features: { TimeStamp MultipleUsers BasalMetabolism MusclePercentage MuscleMass FatFreeMass SoftLeanMass BodyWaterMass Impedance Weight Height }, WeightResolution: 0lb, HeightResolution: 0in", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesNone_WeightRes0500_HeightRes0010_ReservedOdd)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b01010101), C(0b01010100), C(0b10001000), C(0b00000000) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeStampSupported());
    EXPECT_FALSE(result->isMultipleUsersSupported());
    EXPECT_FALSE(result->isBasalMetabolismSupported());
    EXPECT_FALSE(result->isMusclePercentageSupported());
    EXPECT_FALSE(result->isMuscleMassSupported());
    EXPECT_FALSE(result->isFatFreeMassSupported());
    EXPECT_FALSE(result->isSoftLeanMassSupported());
    EXPECT_FALSE(result->isBodyWaterMassSupported());
    EXPECT_FALSE(result->isImpedanceSupported());
    EXPECT_FALSE(result->isWeightSupported());
    EXPECT_FALSE(result->isHeightSupported());
    EXPECT_EQ(500, result->weightResolution());
    EXPECT_EQ(10, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1431603200, btSpecObj.flags);

    EXPECT_EQ("Features: { }", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(1000, result->weightResolution());
    EXPECT_EQ(1000, result->heightResolution());
    EXPECT_EQ("Features: { }", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesEven_WeightRes0200_HeightRes0005_ReservedAll)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b11111111), C(0b11111101), C(0b00010010), C(0b10101010) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeStampSupported());
    EXPECT_TRUE(result->isMultipleUsersSupported());
    EXPECT_FALSE(result->isBasalMetabolismSupported());
    EXPECT_TRUE(result->isMusclePercentageSupported());
    EXPECT_FALSE(result->isMuscleMassSupported());
    EXPECT_TRUE(result->isFatFreeMassSupported());
    EXPECT_FALSE(result->isSoftLeanMassSupported());
    EXPECT_TRUE(result->isBodyWaterMassSupported());
    EXPECT_FALSE(result->isImpedanceSupported());
    EXPECT_TRUE(result->isWeightSupported());
    EXPECT_FALSE(result->isHeightSupported());
    EXPECT_EQ(200, result->weightResolution());
    EXPECT_EQ(5, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(4294775466, btSpecObj.flags);

    EXPECT_EQ("Features: { MultipleUsers MusclePercentage FatFreeMass BodyWaterMass Weight }, WeightResolution: 0.2kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(500, result->weightResolution());
    EXPECT_EQ(500, result->heightResolution());
    EXPECT_EQ("Features: { MultipleUsers MusclePercentage FatFreeMass BodyWaterMass Weight }, WeightResolution: 0.5lb", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesOdd_WeightRes0100_HeightRes0001_ReservedNone)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b00000000), C(0b00000001), C(0b10011101), C(0b01010101) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeStampSupported());
    EXPECT_FALSE(result->isMultipleUsersSupported());
    EXPECT_TRUE(result->isBasalMetabolismSupported());
    EXPECT_FALSE(result->isMusclePercentageSupported());
    EXPECT_TRUE(result->isMuscleMassSupported());
    EXPECT_FALSE(result->isFatFreeMassSupported());
    EXPECT_TRUE(result->isSoftLeanMassSupported());
    EXPECT_FALSE(result->isBodyWaterMassSupported());
    EXPECT_TRUE(result->isImpedanceSupported());
    EXPECT_FALSE(result->isWeightSupported());
    EXPECT_TRUE(result->isHeightSupported());
    EXPECT_EQ(100, result->weightResolution());
    EXPECT_EQ(1, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(105813, btSpecObj.flags);

    EXPECT_EQ("Features: { TimeStamp BasalMetabolism MuscleMass SoftLeanMass Impedance Height }, HeightResolution: 0.001m", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(200, result->weightResolution());
    EXPECT_EQ(100, result->heightResolution());
    EXPECT_EQ("Features: { TimeStamp BasalMetabolism MuscleMass SoftLeanMass Impedance Height }, HeightResolution: 0.1in", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesPat1_WeightRes0050_HeightResReserved_ReservedEven)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b10101010), C(0b10101010), C(0b00100110), C(0b11011011) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeStampSupported());
    EXPECT_TRUE(result->isMultipleUsersSupported());
    EXPECT_FALSE(result->isBasalMetabolismSupported());
    EXPECT_TRUE(result->isMusclePercentageSupported());
    EXPECT_TRUE(result->isMuscleMassSupported());
    EXPECT_FALSE(result->isFatFreeMassSupported());
    EXPECT_TRUE(result->isSoftLeanMassSupported());
    EXPECT_TRUE(result->isBodyWaterMassSupported());
    EXPECT_FALSE(result->isImpedanceSupported());
    EXPECT_TRUE(result->isWeightSupported());
    EXPECT_TRUE(result->isHeightSupported());
    EXPECT_EQ(50, result->weightResolution());
    EXPECT_EQ(0, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2863277787, btSpecObj.flags);

    EXPECT_EQ("Features: { TimeStamp MultipleUsers MusclePercentage MuscleMass SoftLeanMass BodyWaterMass Weight Height }, WeightResolution: 0.05kg, HeightResolution: 0m", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(100, result->weightResolution());
    EXPECT_EQ(0, result->heightResolution());
    EXPECT_EQ("Features: { TimeStamp MultipleUsers MusclePercentage MuscleMass SoftLeanMass BodyWaterMass Weight Height }, WeightResolution: 0.1lb, HeightResolution: 0in", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesPat2_WeightRes0020_HeightRes0001_ReservedOdd)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b01010101), C(0b01010101), C(0b10101001), C(0b00100100) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeStampSupported());
    EXPECT_FALSE(result->isMultipleUsersSupported());
    EXPECT_TRUE(result->isBasalMetabolismSupported());
    EXPECT_FALSE(result->isMusclePercentageSupported());
    EXPECT_FALSE(result->isMuscleMassSupported());
    EXPECT_TRUE(result->isFatFreeMassSupported());
    EXPECT_FALSE(result->isSoftLeanMassSupported());
    EXPECT_FALSE(result->isBodyWaterMassSupported());
    EXPECT_TRUE(result->isImpedanceSupported());
    EXPECT_FALSE(result->isWeightSupported());
    EXPECT_FALSE(result->isHeightSupported());
    EXPECT_EQ(20, result->weightResolution());
    EXPECT_EQ(1, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1431677220, btSpecObj.flags);

    EXPECT_EQ("Features: { BasalMetabolism FatFreeMass Impedance }", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(50, result->weightResolution());
    EXPECT_EQ(100, result->heightResolution());
    EXPECT_EQ("Features: { BasalMetabolism FatFreeMass Impedance }", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesPat3_WeightRes0010_HeightRes0005_ReservedAll)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b11111111), C(0b11111101), C(0b00110011), C(0b10110100) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeStampSupported());
    EXPECT_FALSE(result->isMultipleUsersSupported());
    EXPECT_TRUE(result->isBasalMetabolismSupported());
    EXPECT_FALSE(result->isMusclePercentageSupported());
    EXPECT_TRUE(result->isMuscleMassSupported());
    EXPECT_TRUE(result->isFatFreeMassSupported());
    EXPECT_FALSE(result->isSoftLeanMassSupported());
    EXPECT_TRUE(result->isBodyWaterMassSupported());
    EXPECT_TRUE(result->isImpedanceSupported());
    EXPECT_TRUE(result->isWeightSupported());
    EXPECT_FALSE(result->isHeightSupported());
    EXPECT_EQ(10, result->weightResolution());
    EXPECT_EQ(5, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(4294783924, btSpecObj.flags);

    EXPECT_EQ("Features: { BasalMetabolism MuscleMass FatFreeMass BodyWaterMass Impedance Weight }, WeightResolution: 0.01kg", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(20, result->weightResolution());
    EXPECT_EQ(500, result->heightResolution());
    EXPECT_EQ("Features: { BasalMetabolism MuscleMass FatFreeMass BodyWaterMass Impedance Weight }, WeightResolution: 0.02lb", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesPat4_WeightRes0005_HeightRes0010_ReservedNone)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b00000000), C(0b00000000), C(0b10111001), C(0b01101110) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isTimeStampSupported());
    EXPECT_TRUE(result->isMultipleUsersSupported());
    EXPECT_TRUE(result->isBasalMetabolismSupported());
    EXPECT_TRUE(result->isMusclePercentageSupported());
    EXPECT_FALSE(result->isMuscleMassSupported());
    EXPECT_TRUE(result->isFatFreeMassSupported());
    EXPECT_TRUE(result->isSoftLeanMassSupported());
    EXPECT_FALSE(result->isBodyWaterMassSupported());
    EXPECT_TRUE(result->isImpedanceSupported());
    EXPECT_FALSE(result->isWeightSupported());
    EXPECT_FALSE(result->isHeightSupported());
    EXPECT_EQ(5, result->weightResolution());
    EXPECT_EQ(10, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(47470, btSpecObj.flags);

    EXPECT_EQ("Features: { MultipleUsers BasalMetabolism MusclePercentage FatFreeMass SoftLeanMass Impedance }", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(10, result->weightResolution());
    EXPECT_EQ(1000, result->heightResolution());
    EXPECT_EQ("Features: { MultipleUsers BasalMetabolism MusclePercentage FatFreeMass SoftLeanMass Impedance }", result->toString());
}

TEST_F(BodyCompositionFeatureTest, FeaturesPat5_WeightResReserved_HeightResNotSpec_ReservedEven)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b10101010), C(0b10101000), C(0b01000001), C(0b10011001) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value<BodyCompositionFeature>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isTimeStampSupported());
    EXPECT_FALSE(result->isMultipleUsersSupported());
    EXPECT_FALSE(result->isBasalMetabolismSupported());
    EXPECT_TRUE(result->isMusclePercentageSupported());
    EXPECT_TRUE(result->isMuscleMassSupported());
    EXPECT_FALSE(result->isFatFreeMassSupported());
    EXPECT_FALSE(result->isSoftLeanMassSupported());
    EXPECT_TRUE(result->isBodyWaterMassSupported());
    EXPECT_TRUE(result->isImpedanceSupported());
    EXPECT_FALSE(result->isWeightSupported());
    EXPECT_FALSE(result->isHeightSupported());
    EXPECT_EQ(0, result->weightResolution());
    EXPECT_EQ(0, result->heightResolution());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(2863153561, btSpecObj.flags);

    EXPECT_EQ("Features: { TimeStamp MusclePercentage MuscleMass BodyWaterMass Impedance }", result->toString());

    result->configuration.measurementUnits = MeasurementUnitsEnum::Imperial;
    EXPECT_EQ(0, result->weightResolution());
    EXPECT_EQ(0, result->heightResolution());
    EXPECT_EQ("Features: { TimeStamp MusclePercentage MuscleMass BodyWaterMass Impedance }", result->toString());
}

TEST_F(BodyCompositionFeatureTest, ToString)
{
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b10101010), C(0b10101010), C(0b00100110), C(0b11011011) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    auto result = bleValueParser.make_value(CharacteristicType::BodyCompositionFeature,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Features: { TimeStamp MultipleUsers MusclePercentage MuscleMass SoftLeanMass BodyWaterMass Weight Height }, WeightResolution: 0.05kg, HeightResolution: 0m", result->toString());
}

}  // namespace bvp
