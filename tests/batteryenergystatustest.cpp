#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct BatteryEnergyStatusTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(BatteryEnergyStatusTest, InfoNone_ReservedAll)
{
    //                         RRLRCEVS
    constexpr char flags = C(0b11000000);
    constexpr char data[] = {
        flags
    };

    auto result = bleValueParser.make_value<BatteryEnergyStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isExternalSourcePowerPresent());
    EXPECT_FALSE(result->isPresentVoltagePresent());
    EXPECT_FALSE(result->isAvailableEnergyPresent());
    EXPECT_FALSE(result->isAvailableBatteryCapacityPresent());
    EXPECT_FALSE(result->isChargeRatePresent());
    EXPECT_FALSE(result->isAvailableEnergyAtLastChargePresent());
    EXPECT_TRUE(result->externalSourcePower().isNaN());
    EXPECT_TRUE(result->presentVoltage().isNaN());
    EXPECT_TRUE(result->availableEnergy().isNaN());
    EXPECT_TRUE(result->availableBatteryCapacity().isNaN());
    EXPECT_TRUE(result->chargeRate().isNaN());
    EXPECT_TRUE(result->availableEnergyAtLastCharge().isNaN());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(192, btSpecObj.flags);
    EXPECT_EQ(2047, btSpecObj.externalSourcePower.mantissa());
    EXPECT_EQ(0, btSpecObj.externalSourcePower.exponent());
    EXPECT_EQ(2047, btSpecObj.presentVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.presentVoltage.exponent());
    EXPECT_EQ(2047, btSpecObj.availableEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.availableEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.availableBatteryCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.availableBatteryCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.chargeRate.mantissa());
    EXPECT_EQ(0, btSpecObj.chargeRate.exponent());
    EXPECT_EQ(2047, btSpecObj.availableEnergyAtLastCharge.mantissa());
    EXPECT_EQ(0, btSpecObj.availableEnergyAtLastCharge.exponent());

    EXPECT_EQ("<NoData>", result->toString());
}

TEST_F(BatteryEnergyStatusTest, InfoEven_ReservedNone)
{
    //                         RRLRCEVS
    constexpr char flags = C(0b00101010);
    constexpr char data[] = {
        flags,
        C(0b00001111), C(0b11111111),   // presentVoltage
        C(0b11111111), C(0b11111111),   // availableBatteryCapacity
        C(0b10001111), C(0b11111111)    // availableEnergyAtLastCharge
    };

    auto result = bleValueParser.make_value<BatteryEnergyStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isExternalSourcePowerPresent());
    EXPECT_TRUE(result->isPresentVoltagePresent());
    EXPECT_FALSE(result->isAvailableEnergyPresent());
    EXPECT_TRUE(result->isAvailableBatteryCapacityPresent());
    EXPECT_FALSE(result->isChargeRatePresent());
    EXPECT_TRUE(result->isAvailableEnergyAtLastChargePresent());
    float absError;
    EXPECT_TRUE(result->externalSourcePower().isNaN());
    absError = std::pow(10, result->presentVoltage().exponent());
    EXPECT_NEAR(-1.0, result->presentVoltage().toFloat(), absError);
    EXPECT_TRUE(result->availableEnergy().isNaN());
    absError = std::pow(10, result->availableBatteryCapacity().exponent());
    EXPECT_NEAR(-0.1, result->availableBatteryCapacity().toFloat(), absError);
    EXPECT_TRUE(result->chargeRate().isNaN());
    absError = std::pow(10, result->availableEnergyAtLastCharge().exponent());
    EXPECT_NEAR(-0.00000001, result->availableEnergyAtLastCharge().toFloat(), absError);

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(42, btSpecObj.flags);
    EXPECT_EQ(2047, btSpecObj.externalSourcePower.mantissa());
    EXPECT_EQ(0, btSpecObj.externalSourcePower.exponent());
    EXPECT_EQ(-1, btSpecObj.presentVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.presentVoltage.exponent());
    EXPECT_EQ(2047, btSpecObj.availableEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.availableEnergy.exponent());
    EXPECT_EQ(-1, btSpecObj.availableBatteryCapacity.mantissa());
    EXPECT_EQ(-1, btSpecObj.availableBatteryCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.chargeRate.mantissa());
    EXPECT_EQ(0, btSpecObj.chargeRate.exponent());
    EXPECT_EQ(-1, btSpecObj.availableEnergyAtLastCharge.mantissa());
    EXPECT_EQ(-8, btSpecObj.availableEnergyAtLastCharge.exponent());

    EXPECT_EQ("PresentVoltage: -1V, AvailableBatteryCapacity: -0.1kWh, AvailableEnergyAtLastCharge: -1e-08kWh", result->toString());
}

TEST_F(BatteryEnergyStatusTest, InfoOdd_ReservedAll)
{
    //                         RRLRCEVS
    constexpr char flags = C(0b11010101);
    constexpr char data[] = {
        flags,
        C(0b00000111), C(0b11111101),   // externalSourcePower
        C(0b01110111), C(0b11111111),   // availableEnergy
        C(0b11110111), C(0b11111111),   // chargeRate
    };

    auto result = bleValueParser.make_value<BatteryEnergyStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isExternalSourcePowerPresent());
    EXPECT_FALSE(result->isPresentVoltagePresent());
    EXPECT_TRUE(result->isAvailableEnergyPresent());
    EXPECT_FALSE(result->isAvailableBatteryCapacityPresent());
    EXPECT_TRUE(result->isChargeRatePresent());
    EXPECT_FALSE(result->isAvailableEnergyAtLastChargePresent());
    float absError;
    absError = std::pow(10, result->externalSourcePower().exponent());
    EXPECT_NEAR(2045.0, result->externalSourcePower().toFloat(), absError);
    EXPECT_TRUE(result->presentVoltage().isNaN());
    absError = std::pow(10, result->availableEnergy().exponent());
    EXPECT_NEAR(20470000000.0, result->availableEnergy().toFloat(), absError);
    EXPECT_TRUE(result->availableBatteryCapacity().isNaN());
    absError = std::pow(10, result->chargeRate().exponent());
    EXPECT_NEAR(204.7, result->chargeRate().toFloat(), absError);
    EXPECT_TRUE(result->availableEnergyAtLastCharge().isNaN());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(213, btSpecObj.flags);
    EXPECT_EQ(2045, btSpecObj.externalSourcePower.mantissa());
    EXPECT_EQ(0, btSpecObj.externalSourcePower.exponent());
    EXPECT_EQ(2047, btSpecObj.presentVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.presentVoltage.exponent());
    EXPECT_EQ(2047, btSpecObj.availableEnergy.mantissa());
    EXPECT_EQ(7, btSpecObj.availableEnergy.exponent());
    EXPECT_EQ(2047, btSpecObj.availableBatteryCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.availableBatteryCapacity.exponent());
    EXPECT_EQ(2047, btSpecObj.chargeRate.mantissa());
    EXPECT_EQ(-1, btSpecObj.chargeRate.exponent());
    EXPECT_EQ(2047, btSpecObj.availableEnergyAtLastCharge.mantissa());
    EXPECT_EQ(0, btSpecObj.availableEnergyAtLastCharge.exponent());

    EXPECT_EQ("ExternalSourcePower: 2045W, AvailableEnergy: 2.047e+10kWh, ChargeRate: 204.7W", result->toString());
}

TEST_F(BatteryEnergyStatusTest, InfoAll_ReservedNone)
{
    //                         RRLRCEVS
    constexpr char flags = C(0b00111111);
    constexpr char data[] = {
        flags,
        C(0b10000111), C(0b11111111),   // externalSourcePower
        C(0b00000111), C(0b11111111),   // presentVoltage
        C(0b00000111), C(0b11111110),   // availableEnergy
        C(0b00001000), C(0b00000010),   // availableBatteryCapacity
        C(0b00001000), C(0b00000001),   // chargeRate
        C(0b00001000), C(0b00000000)    // availableEnergyAtLastCharge
    };

    auto result = bleValueParser.make_value<BatteryEnergyStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isExternalSourcePowerPresent());
    EXPECT_TRUE(result->isPresentVoltagePresent());
    EXPECT_TRUE(result->isAvailableEnergyPresent());
    EXPECT_TRUE(result->isAvailableBatteryCapacityPresent());
    EXPECT_TRUE(result->isChargeRatePresent());
    EXPECT_TRUE(result->isAvailableEnergyAtLastChargePresent());
    float absError;
    absError = std::pow(10, result->externalSourcePower().exponent());
    EXPECT_NEAR(0.00002047, result->externalSourcePower().toFloat(), absError);
    EXPECT_TRUE(result->presentVoltage().isNaN());
    EXPECT_TRUE(result->availableEnergy().isPlusInfinity());
    EXPECT_TRUE(result->availableBatteryCapacity().isMinusInfinity());
    EXPECT_TRUE(result->chargeRate().isReserved());
    EXPECT_TRUE(result->availableEnergyAtLastCharge().isNres());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(63, btSpecObj.flags);
    EXPECT_EQ(2047, btSpecObj.externalSourcePower.mantissa());
    EXPECT_EQ(-8, btSpecObj.externalSourcePower.exponent());
    EXPECT_EQ(2047, btSpecObj.presentVoltage.mantissa());
    EXPECT_EQ(0, btSpecObj.presentVoltage.exponent());
    EXPECT_EQ(2046, btSpecObj.availableEnergy.mantissa());
    EXPECT_EQ(0, btSpecObj.availableEnergy.exponent());
    EXPECT_EQ(-2046, btSpecObj.availableBatteryCapacity.mantissa());
    EXPECT_EQ(0, btSpecObj.availableBatteryCapacity.exponent());
    EXPECT_EQ(-2047, btSpecObj.chargeRate.mantissa());
    EXPECT_EQ(0, btSpecObj.chargeRate.exponent());
    EXPECT_EQ(-2048, btSpecObj.availableEnergyAtLastCharge.mantissa());
    EXPECT_EQ(0, btSpecObj.availableEnergyAtLastCharge.exponent());

    EXPECT_EQ("ExternalSourcePower: 2.047e-05W, PresentVoltage: <NaN>V, AvailableEnergy: <+Inf>kWh, AvailableBatteryCapacity: <-Inf>kWh, ChargeRate: <Reserved>W, AvailableEnergyAtLastCharge: <Nres>kWh", result->toString());
}

TEST_F(BatteryEnergyStatusTest, TooShort)
{
    auto result = bleValueParser.make_value<BatteryEnergyStatus>({}, 0);
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryEnergyStatusTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryEnergyStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryEnergyStatusTest, ToString)
{
    //                         RRLRCEVS
    constexpr char flags = C(0b00111111);
    constexpr char data[] = {
        flags,
        C(0b01111000), C(0b00000000),   // externalSourcePower
        C(0b11111000), C(0b00000000),   // presentVoltage
        C(0b10001000), C(0b00000000),   // availableEnergy
        C(0b00001000), C(0b00000011),   // availableBatteryCapacity
        C(0b10000000), C(0b00000000),   // chargeRate
        C(0b01111111), C(0b11111111)    // availableEnergyAtLastCharge
    };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryEnergyStatus,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("ExternalSourcePower: -2.048e+10W, PresentVoltage: -204.8V, AvailableEnergy: -2.048e-05kWh, AvailableBatteryCapacity: -2045kWh, ChargeRate: 0W, AvailableEnergyAtLastCharge: -1e+07kWh", result->toString());
}

}  // namespace bvp
