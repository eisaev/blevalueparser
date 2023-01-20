#include "gtest/gtest.h"

#include "blevalueparser.h"


namespace bvp
{

class PnPIDTest : public testing::Test
{
protected:
    explicit PnPIDTest() {}
    virtual ~PnPIDTest() {}

    BLEValueParser bleValueParser;

    //    virtual void SetUp() {}
    //    virtual void TearDown() {}
};

TEST_F(PnPIDTest, Unknown)
{
    constexpr char data[] = { '\x2A', '\x12', '\x00', '\x23', '\x01', '\xBC', '\xAA' };
    auto result = bleValueParser.make_value<PnPID>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(VendorIDSourceEnum::Unknown, result->vendorIdSource());
    EXPECT_EQ(0x0012, result->vendorId());
    EXPECT_EQ(0x0123, result->productId());
    EXPECT_EQ(0xAA, result->majorVersion());
    EXPECT_EQ(0x0B, result->minorVersion());
    EXPECT_EQ(0x0C, result->subMinorVersion());
    EXPECT_EQ("(<Unknown>) VID: 0x0012, PID: 0x0123, Version: 170.11.12", result->toString());
}

TEST_F(PnPIDTest, BT)
{
    constexpr char data[] = { '\x01', '\x12', '\x00', '\x23', '\x01', '\xBC', '\xAA' };
    auto result = bleValueParser.make_value<PnPID>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(VendorIDSourceEnum::Bluetooth, result->vendorIdSource());
    EXPECT_EQ(0x0012, result->vendorId());
    EXPECT_EQ(0x0123, result->productId());
    EXPECT_EQ(0xAA, result->majorVersion());
    EXPECT_EQ(0x0B, result->minorVersion());
    EXPECT_EQ(0x0C, result->subMinorVersion());
    EXPECT_EQ("(Bluetooth) VID: 0x0012, PID: 0x0123, Version: 170.11.12", result->toString());
}

TEST_F(PnPIDTest, USB)
{
    constexpr char data[] = { '\x02', '\x12', '\x00', '\x23', '\x01', '\xBC', '\xAA' };
    auto result = bleValueParser.make_value<PnPID>(data, sizeof(data));
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(VendorIDSourceEnum::USB, result->vendorIdSource());
    EXPECT_EQ(0x0012, result->vendorId());
    EXPECT_EQ(0x0123, result->productId());
    EXPECT_EQ(0xAA, result->majorVersion());
    EXPECT_EQ(0x0B, result->minorVersion());
    EXPECT_EQ(0x0C, result->subMinorVersion());
    EXPECT_EQ("(USB) VID: 0x0012, PID: 0x0123, Version: 170.11.12", result->toString());
}

TEST_F(PnPIDTest, TooShort)
{
    constexpr char data[] = { '\x01', '\x02', '\x03', '\x04', '\x05', '\x06' };
    auto result = bleValueParser.make_value<PnPID>(data, sizeof(data));
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(PnPIDTest, TooLong)
{
    constexpr char data[] = { '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07', '\x08' };
    auto result = bleValueParser.make_value<PnPID>(data, sizeof(data));
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(PnPIDTest, ToString)
{
    constexpr char data[] = { '\x02', '\x12', '\x00', '\x23', '\x01', '\xBC', '\xAA' };
    auto result = bleValueParser.make_value(CharacteristicType::PnPID,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ("(USB) VID: 0x0012, PID: 0x0123, Version: 170.11.12", result->toString());
}

}  // namespace bvp
