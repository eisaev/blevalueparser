#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

class BatteryLevelStatusTest : public testing::Test
{
protected:
    explicit BatteryLevelStatusTest() {}
    virtual ~BatteryLevelStatusTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(BatteryLevelStatusTest, ResNone_AS0_BL0_Id0_Res1_FBat1_FExt1_FOther1_CT7_BCL3_BCS3_WlExt3_WdExt3_Bat1)
{
    //                         RRRRRALI
    constexpr char flags = C(0b00000000);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b11111111), C(0b11111111) };
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0]    // powerState
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isIdentifierPresent());
    EXPECT_FALSE(result->isBatteryLevelPresent());
    EXPECT_FALSE(result->isAdditionalStatusPresent());
    EXPECT_TRUE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Reserved, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Reserved, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::DischargingInactive, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Critical, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::Reserved3, result->chargingType());
    EXPECT_TRUE(result->isChargingFaultReasonBattery());
    EXPECT_TRUE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_TRUE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0000, result->identifier());
    EXPECT_EQ(0, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(0, btSpecObj.flags);
    EXPECT_EQ(65535, btSpecObj.powerState);
    EXPECT_EQ(0x0000, btSpecObj.identifier);
    EXPECT_EQ(0, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(0, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: <Reserved>, WirelessExternalPowerSourceConnected: <Reserved>, BatteryChargeState: DischargingInactive, BatteryChargeLevel: Critical, ChargingType: <Reserved3>, ChargingFaultReason: { Battery ExternalPowerSource Other }, BatteryPresent", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResAll__AS0_BL0_Id0_Res1_FBat0_FExt0_FOther0_CT7_BCL0_BCS3_WlExt0_WdExt3_Bat0)
{
    //                         RRRRRALI
    constexpr char flags = C(0b11111000);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b10001110), C(0b01100110) };
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0]    // powerState
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isIdentifierPresent());
    EXPECT_FALSE(result->isBatteryLevelPresent());
    EXPECT_FALSE(result->isAdditionalStatusPresent());
    EXPECT_FALSE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Reserved, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::No, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::DischargingInactive, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Unknown, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::Reserved3, result->chargingType());
    EXPECT_FALSE(result->isChargingFaultReasonBattery());
    EXPECT_FALSE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_FALSE(result->isChargingFaultReasonOther());
    EXPECT_FALSE(result->hasChargingFault());
    EXPECT_EQ(0x0000, result->identifier());
    EXPECT_EQ(0, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(248, btSpecObj.flags);
    EXPECT_EQ(36454, btSpecObj.powerState);
    EXPECT_EQ(0x0000, btSpecObj.identifier);
    EXPECT_EQ(0, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(0, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: <Reserved>, WirelessExternalPowerSourceConnected: No, BatteryChargeState: DischargingInactive, BatteryChargeLevel: <Unknown>, ChargingType: <Reserved3>", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResPat1_AS0_BL0_Id1_Res0_FBat0_FExt0_FOther1_CT6_BCL1_BCS2_WlExt1_WdExt2_Bat1)
{
    //                         RRRRRALI
    constexpr char flags = C(0b01110001);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b00011100), C(0b11001101) };
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B'                  // identifier
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isIdentifierPresent());
    EXPECT_FALSE(result->isBatteryLevelPresent());
    EXPECT_FALSE(result->isAdditionalStatusPresent());
    EXPECT_TRUE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Unknown, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Yes, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::DischargingActive, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Good, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::Reserved2, result->chargingType());
    EXPECT_TRUE(result->isChargingFaultReasonBattery());
    EXPECT_FALSE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_FALSE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0B0A, result->identifier());
    EXPECT_EQ(0, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(113, btSpecObj.flags);
    EXPECT_EQ(7373, btSpecObj.powerState);
    EXPECT_EQ(0x0B0A, btSpecObj.identifier);
    EXPECT_EQ(0, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(0, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: <Unknown>, WirelessExternalPowerSourceConnected: Yes, BatteryChargeState: DischargingActive, BatteryChargeLevel: Good, ChargingType: <Reserved2>, ChargingFaultReason: { Battery }, ID: 0x0B0A, BatteryPresent", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResPat2_AS0_BL1_Id0_Res1_FBat0_FExt1_FOther0_CT5_BCL2_BCS1_WlExt2_WdExt1_Bat0)
{
    //                         RRRRRALI
    constexpr char flags = C(0b10001010);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b10101011), C(0b00110010) };
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x2A'                          // batteryLevel
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isIdentifierPresent());
    EXPECT_TRUE(result->isBatteryLevelPresent());
    EXPECT_FALSE(result->isAdditionalStatusPresent());
    EXPECT_FALSE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Yes, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Unknown, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::Charging, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Low, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::Reserved1, result->chargingType());
    EXPECT_FALSE(result->isChargingFaultReasonBattery());
    EXPECT_TRUE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_FALSE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0000, result->identifier());
    EXPECT_EQ(42, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(138, btSpecObj.flags);
    EXPECT_EQ(43826, btSpecObj.powerState);
    EXPECT_EQ(0x0000, btSpecObj.identifier);
    EXPECT_EQ(42, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(0, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: Yes, WirelessExternalPowerSourceConnected: <Unknown>, BatteryChargeState: Charging, BatteryChargeLevel: Low, ChargingType: <Reserved1>, ChargingFaultReason: { ExternalPowerSource }, BatteryLevel: 42%", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResPat3_AS0_BL1_Id1_Res0_FBat0_FExt1_FOther1_CT4_BCL3_BCS0_WlExt3_WdExt0_Bat1)
{
    //                         RRRRRALI
    constexpr char flags = C(0b00100011);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b00111001), C(0b10011001) };
    //                                  RRRRRFSS
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B',                 // identifier
        '\x2A'                          // batteryLevel
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isIdentifierPresent());
    EXPECT_TRUE(result->isBatteryLevelPresent());
    EXPECT_FALSE(result->isAdditionalStatusPresent());
    EXPECT_TRUE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::No, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Reserved, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::Unknown, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Critical, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::Float, result->chargingType());
    EXPECT_TRUE(result->isChargingFaultReasonBattery());
    EXPECT_TRUE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_FALSE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0B0A, result->identifier());
    EXPECT_EQ(42, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(35, btSpecObj.flags);
    EXPECT_EQ(14745, btSpecObj.powerState);
    EXPECT_EQ(0x0B0A, btSpecObj.identifier);
    EXPECT_EQ(42, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(0, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: No, WirelessExternalPowerSourceConnected: <Reserved>, BatteryChargeState: <Unknown>, BatteryChargeLevel: Critical, ChargingType: Float, ChargingFaultReason: { Battery ExternalPowerSource }, ID: 0x0B0A, BatteryLevel: 42%, BatteryPresent", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResPat4_AS1_BL0_Id0_Res1_FBat1_FExt0_FOther0_CT3_BCL0_BCS3_WlExt0_WdExt3_Bat0_ResPat3_BF0_SR3)
{
    //                         RRRRRALI
    constexpr char flags = C(0b11011100);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b11000110), C(0b01100110) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b00100011);
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        additionalStatus                // additionalStatus
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isIdentifierPresent());
    EXPECT_FALSE(result->isBatteryLevelPresent());
    EXPECT_TRUE(result->isAdditionalStatusPresent());
    EXPECT_FALSE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Reserved, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::No, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::DischargingInactive, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Unknown, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::Trickle, result->chargingType());
    EXPECT_FALSE(result->isChargingFaultReasonBattery());
    EXPECT_FALSE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_TRUE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0000, result->identifier());
    EXPECT_EQ(0, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::Reserved, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(220, btSpecObj.flags);
    EXPECT_EQ(50790, btSpecObj.powerState);
    EXPECT_EQ(0x0000, btSpecObj.identifier);
    EXPECT_EQ(0, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(35, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: <Reserved>, WirelessExternalPowerSourceConnected: No, BatteryChargeState: DischargingInactive, BatteryChargeLevel: <Unknown>, ChargingType: Trickle, ChargingFaultReason: { Other }, ServiceRequired: <Reserved>", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResPat5_AS1_BL0_Id1_Res0_FBat1_FExt0_FOther1_CT2_BCL1_BCS2_WlExt1_WdExt2_Bat1_ResPat2_BF1_SR2)
{
    //                         RRRRRALI
    constexpr char flags = C(0b10101101);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b01010100), C(0b11001101) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b10001110);
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B',                 // identifier
        additionalStatus                // additionalStatus
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isIdentifierPresent());
    EXPECT_FALSE(result->isBatteryLevelPresent());
    EXPECT_TRUE(result->isAdditionalStatusPresent());
    EXPECT_TRUE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Unknown, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Yes, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::DischargingActive, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Good, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::ConstantVoltage, result->chargingType());
    EXPECT_TRUE(result->isChargingFaultReasonBattery());
    EXPECT_FALSE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_TRUE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0B0A, result->identifier());
    EXPECT_EQ(0, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::Unknown, result->serviceRequired());
    EXPECT_TRUE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(173, btSpecObj.flags);
    EXPECT_EQ(21709, btSpecObj.powerState);
    EXPECT_EQ(0x0B0A, btSpecObj.identifier);
    EXPECT_EQ(0, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(142, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: <Unknown>, WirelessExternalPowerSourceConnected: Yes, BatteryChargeState: DischargingActive, BatteryChargeLevel: Good, ChargingType: ConstantVoltage, ChargingFaultReason: { Battery Other }, ID: 0x0B0A, ServiceRequired: <Unknown>, BatteryFailed, BatteryPresent", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResPat6_AS1_BL1_Id0_Res1_FBat1_FExt1_FOther0_CT1_BCL2_BCS1_WlExt2_WdExt1_Bat0_ResPat1_BF0_SR1)
{
    //                         RRRRRALI
    constexpr char flags = C(0b01010110);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b11100011), C(0b00110010) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b01110001);
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x2A',                         // batteryLevel
        additionalStatus                // additionalStatus
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isIdentifierPresent());
    EXPECT_TRUE(result->isBatteryLevelPresent());
    EXPECT_TRUE(result->isAdditionalStatusPresent());
    EXPECT_FALSE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Yes, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Unknown, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::Charging, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Low, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::ConstantCurrent, result->chargingType());
    EXPECT_FALSE(result->isChargingFaultReasonBattery());
    EXPECT_TRUE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_TRUE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0000, result->identifier());
    EXPECT_EQ(42, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::True, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(86, btSpecObj.flags);
    EXPECT_EQ(58162, btSpecObj.powerState);
    EXPECT_EQ(0x0000, btSpecObj.identifier);
    EXPECT_EQ(42, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(113, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: Yes, WirelessExternalPowerSourceConnected: <Unknown>, BatteryChargeState: Charging, BatteryChargeLevel: Low, ChargingType: ConstantCurrent, ChargingFaultReason: { ExternalPowerSource Other }, BatteryLevel: 42%, ServiceRequired: True", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResNone_AS1_BL1_Id1_Res0_FBat1_FExt1_FOther1_CT0_BCL3_BCS0_WlExt3_WdExt0_Bat1_ResAll__BF1_SR0)
{
    //                         RRRRRALI
    constexpr char flags = C(0b00000111);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b01110001), C(0b10011001) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b11111100);
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B',                 // identifier
        '\x2A',                         // batteryLevel
        additionalStatus                // additionalStatus
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isIdentifierPresent());
    EXPECT_TRUE(result->isBatteryLevelPresent());
    EXPECT_TRUE(result->isAdditionalStatusPresent());
    EXPECT_TRUE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::No, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::Reserved, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::Unknown, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Critical, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::UnknownOrNotCharging, result->chargingType());
    EXPECT_TRUE(result->isChargingFaultReasonBattery());
    EXPECT_TRUE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_TRUE(result->isChargingFaultReasonOther());
    EXPECT_TRUE(result->hasChargingFault());
    EXPECT_EQ(0x0B0A, result->identifier());
    EXPECT_EQ(42, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_TRUE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(7, btSpecObj.flags);
    EXPECT_EQ(29081, btSpecObj.powerState);
    EXPECT_EQ(0x0B0A, btSpecObj.identifier);
    EXPECT_EQ(42, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(252, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: No, WirelessExternalPowerSourceConnected: <Reserved>, BatteryChargeState: <Unknown>, BatteryChargeLevel: Critical, ChargingType: UnknownOrNotCharging, ChargingFaultReason: { Battery ExternalPowerSource Other }, ID: 0x0B0A, BatteryLevel: 42%, ServiceRequired: False, BatteryFailed, BatteryPresent", result->toString());
}

TEST_F(BatteryLevelStatusTest, ResAll__AS1_BL1_Id1_Res0_FBat0_FExt0_FOther0_CT0_BCL0_BCS0_WlExt0_WdExt0_Bat0_ResNone_BF0_SR0)
{
    //                         RRRRRALI
    constexpr char flags = C(0b11111111);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b00000000), C(0b00000000) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b00000000);
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B',                 // identifier
        '\x2A',                         // batteryLevel
        additionalStatus                // additionalStatus
    };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isIdentifierPresent());
    EXPECT_TRUE(result->isBatteryLevelPresent());
    EXPECT_TRUE(result->isAdditionalStatusPresent());
    EXPECT_FALSE(result->isBatteryPresent());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::No, result->wiredExternalPowerSourceConnected());
    EXPECT_EQ(ExternalPowerSourceConnectedEnum::No, result->wirelessExternalPowerSourceConnected());
    EXPECT_EQ(BatteryChargeStateEnum::Unknown, result->batteryChargeState());
    EXPECT_EQ(BatteryChargeLevelEnum::Unknown, result->batteryChargeLevel());
    EXPECT_EQ(ChargingTypeEnum::UnknownOrNotCharging, result->chargingType());
    EXPECT_FALSE(result->isChargingFaultReasonBattery());
    EXPECT_FALSE(result->isChargingFaultReasonExternalPowerSource());
    EXPECT_FALSE(result->isChargingFaultReasonOther());
    EXPECT_FALSE(result->hasChargingFault());
    EXPECT_EQ(0x0B0A, result->identifier());
    EXPECT_EQ(42, result->batteryLevel());
    EXPECT_EQ(ServiceRequiredEnum::False, result->serviceRequired());
    EXPECT_FALSE(result->hasBatteryFault());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(255, btSpecObj.flags);
    EXPECT_EQ(0, btSpecObj.powerState);
    EXPECT_EQ(0x0B0A, btSpecObj.identifier);
    EXPECT_EQ(42, btSpecObj.batteryLevel.batteryLevel);
    EXPECT_EQ(0, btSpecObj.additionalStatus);

    EXPECT_EQ("WiredExternalPowerSourceConnected: No, WirelessExternalPowerSourceConnected: No, BatteryChargeState: <Unknown>, BatteryChargeLevel: <Unknown>, ChargingType: UnknownOrNotCharging, ID: 0x0B0A, BatteryLevel: 42%, ServiceRequired: False", result->toString());
}

TEST_F(BatteryLevelStatusTest, TooShort)
{
    constexpr char data[] = { '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryLevelStatusTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<BatteryLevelStatus>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BatteryLevelStatusTest, ToString)
{
    //                         RRRRRALI
    constexpr char flags = C(0b00000111);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b01110001), C(0b10011001) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b11111100);
    constexpr char data[] = {
        flags,                          // flags
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B',                 // identifier
        '\x2A',                         // batteryLevel
        additionalStatus                // additionalStatus
    };

    auto result = bleValueParser.make_value(CharacteristicType::BatteryLevelStatus,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("WiredExternalPowerSourceConnected: No, WirelessExternalPowerSourceConnected: <Reserved>, BatteryChargeState: <Unknown>, BatteryChargeLevel: Critical, ChargingType: UnknownOrNotCharging, ChargingFaultReason: { Battery ExternalPowerSource Other }, ID: 0x0B0A, BatteryLevel: 42%, ServiceRequired: False, BatteryFailed, BatteryPresent", result->toString());
}

}  // namespace bvp
