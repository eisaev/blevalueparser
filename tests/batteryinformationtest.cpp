#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BatteryInformationTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BatteryInformationTest, ReplNo_RechNo_ManNo_ExpNo_CapNo_LowNo_CritNo_ChemNo_VoltNo_AggGrpNo_ResAll)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b11111111), C(0b00000000) };
    //                            RRRRRRCP
    constexpr char features = C(0b11111100);
    constexpr char data[] = {
        flags[1], flags[0],
        features            // batteryFeatures
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_FALSE(result->isBatteryDesignedCapacityPresent());
    EXPECT_FALSE(result->isBatteryLowEnergyPresent());
    EXPECT_FALSE(result->isBatteryCriticalEnergyPresent());
    EXPECT_FALSE(result->isBatteryChemistryPresent());
    EXPECT_FALSE(result->isNominalVoltagePresent());
    EXPECT_FALSE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    EXPECT_TRUE(result->batteryDesignedCapacity().isNaN());
    EXPECT_TRUE(result->batteryLowEnergy().isNaN());
    EXPECT_TRUE(result->batteryCriticalEnergy().isNaN());
    EXPECT_EQ(BatteryChemistryEnum::Unknown, result->batteryChemistry());
    EXPECT_TRUE(result->nominalVoltage().isNaN());
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(65280, btSpecObj.flags);
    EXPECT_EQ(252, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::Unknown, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: No", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechNo_ManDate_ExpNo_CapMax_LowNo_CritNormal_ChemNo_Volt0_AggGrpNo_ResAll)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b11111111), C(0b01010101) };
    //                            RRRRRRCP
    constexpr char features = C(0b11111101);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        C(0b01110111), C(0b11111111),    // batteryDesignedCapacity
        C(0b11110000), C(0b10101010),    // batteryCriticalEnergy
        C(0b00000000), C(0b00000000)     // nominalVoltage
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_FALSE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_FALSE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_FALSE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryDesignedCapacity().toFloat(), absError);
    EXPECT_TRUE(result->batteryLowEnergy().isNaN());
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::Unknown, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(0.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(65365, btSpecObj.flags);
    EXPECT_EQ(253, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(170, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::Unknown, btSpecObj.batteryChemistry);
    EXPECT_EQ(0, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: No, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 2.047e+10kWh, BatteryCriticalEnergy: 17kWh, NominalVoltage: 0V", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechYes_ManNo_ExpDate_CapNo_LowMax_CritNo_ChemUnknown_VoltNo_AggGrpNotIn_ResAll)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b11111111), C(0b10101010) };
    //                            RRRRRRCP
    constexpr char features = C(0b11111110);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b01110111), C(0b11111111),    // batteryLowEnergy
        '\x00',                          // batteryChemistry
        '\x00'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_FALSE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_FALSE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_FALSE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    EXPECT_TRUE(result->batteryDesignedCapacity().isNaN());
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryLowEnergy().toFloat(), absError);
    EXPECT_TRUE(result->batteryCriticalEnergy().isNaN());
    EXPECT_EQ(BatteryChemistryEnum::Unknown, result->batteryChemistry());
    EXPECT_TRUE(result->nominalVoltage().isNaN());
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(65450, btSpecObj.flags);
    EXPECT_EQ(254, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::Unknown, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: Yes, BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryLowEnergy: 2.047e+10kWh, BatteryChemistry: <Unknown>, BatteryAggregationGroup: <NotInGroup>", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechNo_ManDate_ExpDate_CapNo_LowNo_CritMax_ChemAlkaline_VoltNo_AggGrpNo_ResAll)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b11111111), C(0b00110011) };
    //                            RRRRRRCP
    constexpr char features = C(0b11111100);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b01110111), C(0b11111111),    // batteryCriticalEnergy
        '\x01'                           // batteryChemistry
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_FALSE(result->isBatteryDesignedCapacityPresent());
    EXPECT_FALSE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_FALSE(result->isNominalVoltagePresent());
    EXPECT_FALSE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    EXPECT_TRUE(result->batteryDesignedCapacity().isNaN());
    EXPECT_TRUE(result->batteryLowEnergy().isNaN());
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::Alkaline, result->batteryChemistry());
    EXPECT_TRUE(result->nominalVoltage().isNaN());
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(65331, btSpecObj.flags);
    EXPECT_EQ(252, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::Alkaline, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: No, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryCriticalEnergy: 2.047e+10kWh, BatteryChemistry: Alkaline", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechYes_ManNo_ExpNo_CapNormal_Low0_Crit0_ChemLeadAcid_VoltNormal_AggGrpNormal_ResNone)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b00000000), C(0b11111100) };
    //                            RRRRRRCP
    constexpr char features = C(0b00000011);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        C(0b11110000), C(0b10101010),    // batteryDesignedCapacity
        C(0b00000000), C(0b00000000),    // batteryLowEnergy
        C(0b00000000), C(0b00000000),    // batteryCriticalEnergy
        '\x02',                          // batteryChemistry
        C(0b11110000), C(0b10101010),    // nominalVoltage
        '\x2A',                          // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(17.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::LeadAcid, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(17.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(42, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(252, btSpecObj.flags);
    EXPECT_EQ(3, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(170, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::LeadAcid, btSpecObj.batteryChemistry);
    EXPECT_EQ(170, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(-1, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(42, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: Yes, BatteryDesignedCapacity: 17kWh, BatteryLowEnergy: 0kWh, BatteryCriticalEnergy: 0kWh, BatteryChemistry: LeadAcid, NominalVoltage: 17V, BatteryAggregationGroup: 42", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechYes_ManDate_ExpNo_Cap0_LowNormal_CritMax_ChemLiFeS2_VoltMax_AggGrpReserved_ResNone)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b00000000), C(0b11111101) };
    //                            RRRRRRCP
    constexpr char features = C(0b00000011);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        C(0b00000000), C(0b00000000),    // batteryDesignedCapacity
        C(0b11110000), C(0b10101010),    // batteryLowEnergy
        C(0b01110111), C(0b11111111),    // batteryCriticalEnergy
        '\x03',                          // batteryChemistry
        C(0b01110111), C(0b11111111),    // nominalVoltage
        '\xFF',                          // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(0.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::LiFeS2, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(20470000000.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(255, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(253, btSpecObj.flags);
    EXPECT_EQ(3, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(170, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::LiFeS2, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(7, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(255, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: Yes, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 0kWh, BatteryLowEnergy: 17kWh, BatteryCriticalEnergy: 2.047e+10kWh, BatteryChemistry: LiFeS2, NominalVoltage: 2.047e+10V, BatteryAggregationGroup: <Reserved>", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechNo_ManNo_ExpDate_CapMax_LowNormal_CritNormal_ChemLiMnO2_Volt0_AggGrpNotIn_ResOdd)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b01010101), C(0b11111110) };
    //                            RRRRRRCP
    constexpr char features = C(0b01010100);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b01110111), C(0b11111111),    // batteryDesignedCapacity
        C(0b11110000), C(0b10101010),    // batteryLowEnergy
        C(0b11110000), C(0b10101010),    // batteryCriticalEnergy
        '\x04',                          // batteryChemistry
        C(0b00000000), C(0b00000000),    // nominalVoltage
        '\x00'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::LiMnO2, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(0.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(22014, btSpecObj.flags);
    EXPECT_EQ(84, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(170, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(170, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::LiMnO2, btSpecObj.batteryChemistry);
    EXPECT_EQ(0, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: No, BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 2.047e+10kWh, BatteryLowEnergy: 17kWh, BatteryCriticalEnergy: 17kWh, BatteryChemistry: LiMnO2, NominalVoltage: 0V, BatteryAggregationGroup: <NotInGroup>", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechYes_ManDate_ExpDate_CapNormal_Low0_CritMax_ChemLiIon_VoltNormal_AggGrpNormal_ResEven)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b10101010), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b10101010);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b11110000), C(0b10101010),    // batteryDesignedCapacity
        C(0b00000000), C(0b00000000),    // batteryLowEnergy
        C(0b01110111), C(0b11111111),    // batteryCriticalEnergy
        '\x05',                          // batteryChemistry
        C(0b11110000), C(0b10101010),    // nominalVoltage
        '\x2A'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(17.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::LiIon, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(17.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(42, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(43775, btSpecObj.flags);
    EXPECT_EQ(170, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(170, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::LiIon, btSpecObj.batteryChemistry);
    EXPECT_EQ(170, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(-1, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(42, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: Yes, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 17kWh, BatteryLowEnergy: 0kWh, BatteryCriticalEnergy: 2.047e+10kWh, BatteryChemistry: LiIon, NominalVoltage: 17V, BatteryAggregationGroup: 42", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechNo_ManNo_ExpNo_Cap0_LowMax_Crit0_ChemLiPo_VoltMax_AggGrpReservedResOdd)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b01010101), C(0b11111100) };
    //                            RRRRRRCP
    constexpr char features = C(0b01010101);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        C(0b00000000), C(0b00000000),    // batteryDesignedCapacity
        C(0b01110111), C(0b11111111),    // batteryLowEnergy
        C(0b00000000), C(0b00000000),    // batteryCriticalEnergy
        '\x06',                          // batteryChemistry
        C(0b01110111), C(0b11111111),    // nominalVoltage
        '\xFF'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(0.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::LiPo, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(20470000000.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(255, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(22012, btSpecObj.flags);
    EXPECT_EQ(85, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::LiPo, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(7, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(255, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: No, BatteryDesignedCapacity: 0kWh, BatteryLowEnergy: 2.047e+10kWh, BatteryCriticalEnergy: 0kWh, BatteryChemistry: LiPo, NominalVoltage: 2.047e+10V, BatteryAggregationGroup: <Reserved>", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechNo_ManDate_ExpDate_CapMax_LowMax_CritNormal_ChemNiOx_Volt0_AggGrpNotIn_ResOdd)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b01010101), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b01010101);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b01110111), C(0b11111111),    // batteryDesignedCapacity
        C(0b01110111), C(0b11111111),    // batteryLowEnergy
        C(0b11110000), C(0b10101010),    // batteryCriticalEnergy
        '\x07',                          // batteryChemistry
        C(0b00000000), C(0b00000000),    // nominalVoltage
        '\x00'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::NiOx, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(0.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(22015, btSpecObj.flags);
    EXPECT_EQ(85, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(170, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::NiOx, btSpecObj.batteryChemistry);
    EXPECT_EQ(0, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: No, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 2.047e+10kWh, BatteryLowEnergy: 2.047e+10kWh, BatteryCriticalEnergy: 17kWh, BatteryChemistry: NiOx, NominalVoltage: 0V, BatteryAggregationGroup: <NotInGroup>", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechYes_ManDate_ExpDate_CapNormal_Low0_CritMax_ChemNiCd_VoltMax_AggGrpNormal_ResEven)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b10101010), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b10101010);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b11110000), C(0b10101010),    // batteryDesignedCapacity
        C(0b00000000), C(0b00000000),    // batteryLowEnergy
        C(0b01110111), C(0b11111111),    // batteryCriticalEnergy
        '\x08',                          // batteryChemistry
        C(0b01110111), C(0b11111111),    // nominalVoltage
        '\x2A'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(17.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::NiCd, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(20470000000.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(42, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(43775, btSpecObj.flags);
    EXPECT_EQ(170, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(170, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::NiCd, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(7, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(42, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: Yes, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 17kWh, BatteryLowEnergy: 0kWh, BatteryCriticalEnergy: 2.047e+10kWh, BatteryChemistry: NiCd, NominalVoltage: 2.047e+10V, BatteryAggregationGroup: 42", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechNo_ManNo_ExpNo_Cap0_LowNormal_CritNormal_ChemNiMH_VoltNormal_AggGrpReserved_ResPat1)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b10000100), C(0b11111100) };
    //                            RRRRRRCP
    constexpr char features = C(0b10000100);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        C(0b00000000), C(0b00000000),    // batteryDesignedCapacity
        C(0b11110000), C(0b10101010),    // batteryLowEnergy
        C(0b11110000), C(0b10101010),    // batteryCriticalEnergy
        '\x09',                          // batteryChemistry
        C(0b11110000), C(0b10101010),    // nominalVoltage
        '\xFF'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(0.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::NiMH, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(17.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(255, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(34044, btSpecObj.flags);
    EXPECT_EQ(132, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(170, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(170, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::NiMH, btSpecObj.batteryChemistry);
    EXPECT_EQ(170, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(-1, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(255, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: No, BatteryDesignedCapacity: 0kWh, BatteryLowEnergy: 17kWh, BatteryCriticalEnergy: 17kWh, BatteryChemistry: NiMH, NominalVoltage: 17V, BatteryAggregationGroup: <Reserved>", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechYes_ManDate_ExpNo_CapMax_LowNormal_Crit0_ChemAgZn_Volt0_AggGrpNotIn_ResPat2)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b01111011), C(0b11111101) };
    //                            RRRRRRCP
    constexpr char features = C(0b01111011);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        C(0b01110111), C(0b11111111),    // batteryDesignedCapacity
        C(0b11110000), C(0b10101010),    // batteryLowEnergy
        C(0b00000000), C(0b00000000),    // batteryCriticalEnergy
        '\x0A',                          // batteryChemistry
        C(0b00000000), C(0b00000000),    // nominalVoltage
        '\x00'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::AgZn, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(0.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(31741, btSpecObj.flags);
    EXPECT_EQ(123, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(170, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::AgZn, btSpecObj.batteryChemistry);
    EXPECT_EQ(0, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: Yes, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 2.047e+10kWh, BatteryLowEnergy: 17kWh, BatteryCriticalEnergy: 0kWh, BatteryChemistry: AgZn, NominalVoltage: 0V, BatteryAggregationGroup: <NotInGroup>", result->toString());
}

TEST_F(BatteryInformationTest, ReplYes_RechYes_ManNo_ExpDate_CapNormal_Low0_CritMax_ChemZnChloride_VoltNormal_AggGrpNormal_ResPat3)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b01001001), C(0b11111110) };
    //                            RRRRRRCP
    constexpr char features = C(0b01001011);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b11110000), C(0b10101010),    // batteryDesignedCapacity
        C(0b00000000), C(0b00000000),    // batteryLowEnergy
        C(0b01110111), C(0b11111111),    // batteryCriticalEnergy
        '\x0B',                          // batteryChemistry
        C(0b11110000), C(0b10101010),    // nominalVoltage
        '\x2A'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(17.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::ZnChloride, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(17.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(42, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(18942, btSpecObj.flags);
    EXPECT_EQ(75, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(170, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::ZnChloride, btSpecObj.batteryChemistry);
    EXPECT_EQ(170, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(-1, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(42, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: Yes, BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 17kWh, BatteryLowEnergy: 0kWh, BatteryCriticalEnergy: 2.047e+10kWh, BatteryChemistry: ZnChloride, NominalVoltage: 17V, BatteryAggregationGroup: 42", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechNo_ManDate_ExpDate_Cap0_LowMax_CritNormal_ChemZnAir_VoltMax_AggGrpReserved_ResPat4)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b10110110), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b10110100);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b00000000), C(0b00000000),    // batteryDesignedCapacity
        C(0b01110111), C(0b11111111),    // batteryLowEnergy
        C(0b11110000), C(0b10101010),    // batteryCriticalEnergy
        '\x0C',                          // batteryChemistry
        C(0b01110111), C(0b11111111),    // nominalVoltage
        '\xFF'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(0.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::ZnAir, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(20470000000.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(255, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(46847, btSpecObj.flags);
    EXPECT_EQ(180, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(170, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::ZnAir, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(7, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(255, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: No, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 0kWh, BatteryLowEnergy: 2.047e+10kWh, BatteryCriticalEnergy: 17kWh, BatteryChemistry: ZnAir, NominalVoltage: 2.047e+10V, BatteryAggregationGroup: <Reserved>", result->toString());
}

TEST_F(BatteryInformationTest, ReplNo_RechYes_ManNo_ExpNo_CapMax_LowMax_CritMax_ChemZnCarbon_Volt0_AggGrpNotIn_ResPat5)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b11011011), C(0b11111100) };
    //                            RRRRRRCP
    constexpr char features = C(0b11011010);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        C(0b01110111), C(0b11111111),    // batteryDesignedCapacity
        C(0b01110111), C(0b11111111),    // batteryLowEnergy
        C(0b01110111), C(0b11111111),    // batteryCriticalEnergy
        '\x0D',                          // batteryChemistry
        C(0b00000000), C(0b00000000),    // nominalVoltage
        '\x00'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_FALSE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_FALSE(result->isBatteryReplaceable());
    EXPECT_TRUE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(0, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::ZnCarbon, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(0.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(0, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(56316, btSpecObj.flags);
    EXPECT_EQ(218, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(0, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(2047, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::ZnCarbon, btSpecObj.batteryChemistry);
    EXPECT_EQ(0, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(0, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: No, BatteryRechargeable: Yes, BatteryDesignedCapacity: 2.047e+10kWh, BatteryLowEnergy: 2.047e+10kWh, BatteryCriticalEnergy: 2.047e+10kWh, BatteryChemistry: ZnCarbon, NominalVoltage: 0V, BatteryAggregationGroup: <NotInGroup>", result->toString());
}

TEST_F(BatteryInformationTest, ReprYes_RechNo_ManDate_ExpDate_CapNormal_Low0_Crit0_ChemReserved_VoltMax_AggGrpNormal_ResPat6)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b01101101), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b01101101);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryManufactureDate
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b11110000), C(0b10101010),    // batteryDesignedCapacity
        C(0b00000000), C(0b00000000),    // batteryLowEnergy
        C(0b00000000), C(0b00000000),    // batteryCriticalEnergy
        '\x0E',                          // batteryChemistry
        C(0b01110111), C(0b11111111),    // nominalVoltage
        '\x2A'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(19416, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(17.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(0.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::Unknown, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(20470000000.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(42, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(28159, btSpecObj.flags);
    EXPECT_EQ(109, btSpecObj.batteryFeatures);
    EXPECT_EQ(19416, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(170, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::Unknown, btSpecObj.batteryChemistry);
    EXPECT_EQ(2047, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(7, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(42, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: No, BatteryManufactureDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 17kWh, BatteryLowEnergy: 0kWh, BatteryCriticalEnergy: 0kWh, BatteryChemistry: <Unknown>, NominalVoltage: 2.047e+10V, BatteryAggregationGroup: 42", result->toString());
}

TEST_F(BatteryInformationTest, ReprYes_RechNo_ManNo_ExpDate_Cap0_LowNormal_CritNormal_ChemOther_VoltNormal_AggGrpReserved_ResPat7)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b00100100), C(0b11111110) };
    //                            RRRRRRCP
    constexpr char features = C(0b00100101);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x4B', '\x00',          // batteryExpirationDate
        C(0b00000000), C(0b00000000),    // batteryDesignedCapacity
        C(0b11110000), C(0b10101010),    // batteryLowEnergy
        C(0b11110000), C(0b10101010),    // batteryCriticalEnergy
        '\xFF',                          // batteryChemistry
        C(0b11110000), C(0b10101010),    // nominalVoltage
        '\xFF'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isBatteryManufactureDatePresent());
    EXPECT_TRUE(result->isBatteryExpirationDatePresent());
    EXPECT_TRUE(result->isBatteryDesignedCapacityPresent());
    EXPECT_TRUE(result->isBatteryLowEnergyPresent());
    EXPECT_TRUE(result->isBatteryCriticalEnergyPresent());
    EXPECT_TRUE(result->isBatteryChemistryPresent());
    EXPECT_TRUE(result->isNominalVoltagePresent());
    EXPECT_TRUE(result->isBatteryAggregationGroupPresent());
    EXPECT_TRUE(result->isBatteryReplaceable());
    EXPECT_FALSE(result->isBatteryRechargeable());
    EXPECT_EQ(0, result->batteryManufactureDate().date);
    EXPECT_EQ(19416, result->batteryExpirationDate().date);
    float absError;
    absError = std::pow(10, result->batteryDesignedCapacity().exponent());
    EXPECT_NEAR(0.0, result->batteryDesignedCapacity().toFloat(), absError);
    absError = std::pow(10, result->batteryLowEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryLowEnergy().toFloat(), absError);
    absError = std::pow(10, result->batteryCriticalEnergy().exponent());
    EXPECT_NEAR(17.0, result->batteryCriticalEnergy().toFloat(), absError);
    EXPECT_EQ(BatteryChemistryEnum::Other, result->batteryChemistry());
    absError = std::pow(10, result->nominalVoltage().exponent());
    EXPECT_NEAR(17.0, result->nominalVoltage().toFloat(), absError);
    EXPECT_EQ(255, result->batteryAggregationGroup());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(9470, btSpecObj.flags);
    EXPECT_EQ(37, btSpecObj.batteryFeatures);
    EXPECT_EQ(0, btSpecObj.batteryManufactureDate.date);
    EXPECT_EQ(19416, btSpecObj.batteryExpirationDate.date);
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.batteryDesignedCapacity.exponent());
    EXPECT_EQ(170, btSpecObj.batteryLowEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryLowEnergy.exponent());
    EXPECT_EQ(170, btSpecObj.batteryCriticalEnergy.mantissa());
    EXPECT_EQ(-1, btSpecObj.batteryCriticalEnergy.exponent());
    EXPECT_EQ(BatteryChemistryEnum::Other, btSpecObj.batteryChemistry);
    EXPECT_EQ(170, btSpecObj.nominalVoltage.mantissa());
    EXPECT_EQ(-1, btSpecObj.nominalVoltage.exponent());
    EXPECT_EQ(255, btSpecObj.batteryAggregationGroup);

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: No, BatteryExpirationDate: 28.02.2023 (1677542400 seconds since 1 Jan 1970), BatteryDesignedCapacity: 0kWh, BatteryLowEnergy: 17kWh, BatteryCriticalEnergy: 17kWh, BatteryChemistry: <Other>, NominalVoltage: 17V, BatteryAggregationGroup: <Reserved>", result->toString());
}

TEST_F(BatteryInformationTest, TooShort)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryInformationTest, TooLong)
{
    constexpr char data[] = {
        '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A',
        '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A'
    };

    auto result = bleValueParser.make_value<BatteryInformation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryInformationTest, ToString)
{
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b00000000), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b00000011);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x3B', '\x00',          // batteryManufactureDate
        '\xD8', '\x5B', '\x00',          // batteryExpirationDate
        C(0b11100010), C(0b00001000),    // batteryDesignedCapacity
        C(0b11110000), C(0b00000011),    // batteryLowEnergy
        C(0b11110000), C(0b00000001),    // batteryCriticalEnergy
        '\x05',                          // batteryChemistry
        C(0b11110000), C(0b00101010),    // nominalVoltage
        '\x01'                           // batteryAggregationGroup
    };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryInformation,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("BatteryReplaceable: Yes, BatteryRechargeable: Yes, BatteryManufactureDate: 12.12.2011 (1323648000 seconds since 1 Jan 1970), BatteryExpirationDate: 17.05.2034 (2031436800 seconds since 1 Jan 1970), BatteryDesignedCapacity: 5.2kWh, BatteryLowEnergy: 0.3kWh, BatteryCriticalEnergy: 0.1kWh, BatteryChemistry: LiIon, NominalVoltage: 4.2V, BatteryAggregationGroup: 1", result->toString());
}

}  // namespace bvp
