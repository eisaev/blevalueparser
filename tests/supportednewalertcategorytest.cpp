#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct SupportedNewAlertCategoryTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(SupportedNewAlertCategoryTest, ReservedAll_CategoryNone)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b11111100), C(0b00000000) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<SupportedNewAlertCategory>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isSimpleAlertSupported());
    EXPECT_FALSE(result->isEmailSupported());
    EXPECT_FALSE(result->isNewsSupported());
    EXPECT_FALSE(result->isCallSupported());
    EXPECT_FALSE(result->isMissedCallSupported());
    EXPECT_FALSE(result->isSMSMMSSupported());
    EXPECT_FALSE(result->isVoiceMailSupported());
    EXPECT_FALSE(result->isScheduleSupported());
    EXPECT_FALSE(result->isHighPrioritizedAlertSupported());
    EXPECT_FALSE(result->isInstantMessageSupported());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(64512, btSpecObj.categoryIDBitMask.categoryIDBitMask);

    EXPECT_EQ("SupportedCategories: { }", result->toString());
}

TEST_F(SupportedNewAlertCategoryTest, ReservedEven_CategoryOdd)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b10101001), C(0b01010101) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<SupportedNewAlertCategory>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isSimpleAlertSupported());
    EXPECT_FALSE(result->isEmailSupported());
    EXPECT_TRUE(result->isNewsSupported());
    EXPECT_FALSE(result->isCallSupported());
    EXPECT_TRUE(result->isMissedCallSupported());
    EXPECT_FALSE(result->isSMSMMSSupported());
    EXPECT_TRUE(result->isVoiceMailSupported());
    EXPECT_FALSE(result->isScheduleSupported());
    EXPECT_TRUE(result->isHighPrioritizedAlertSupported());
    EXPECT_FALSE(result->isInstantMessageSupported());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(43349, btSpecObj.categoryIDBitMask.categoryIDBitMask);

    EXPECT_EQ("SupportedCategories: { SimpleAlert News MissedCall VoiceMail HighPrioritizedAlert }", result->toString());
}

TEST_F(SupportedNewAlertCategoryTest, ReservedOdd_CategoryEven)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b01010110), C(0b10101010) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<SupportedNewAlertCategory>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->isSimpleAlertSupported());
    EXPECT_TRUE(result->isEmailSupported());
    EXPECT_FALSE(result->isNewsSupported());
    EXPECT_TRUE(result->isCallSupported());
    EXPECT_FALSE(result->isMissedCallSupported());
    EXPECT_TRUE(result->isSMSMMSSupported());
    EXPECT_FALSE(result->isVoiceMailSupported());
    EXPECT_TRUE(result->isScheduleSupported());
    EXPECT_FALSE(result->isHighPrioritizedAlertSupported());
    EXPECT_TRUE(result->isInstantMessageSupported());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(22186, btSpecObj.categoryIDBitMask.categoryIDBitMask);

    EXPECT_EQ("SupportedCategories: { Email Call SMS/MMS Schedule InstantMessage }", result->toString());
}
TEST_F(SupportedNewAlertCategoryTest, ReservedNone_CategoryAll)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<SupportedNewAlertCategory>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->isSimpleAlertSupported());
    EXPECT_TRUE(result->isEmailSupported());
    EXPECT_TRUE(result->isNewsSupported());
    EXPECT_TRUE(result->isCallSupported());
    EXPECT_TRUE(result->isMissedCallSupported());
    EXPECT_TRUE(result->isSMSMMSSupported());
    EXPECT_TRUE(result->isVoiceMailSupported());
    EXPECT_TRUE(result->isScheduleSupported());
    EXPECT_TRUE(result->isHighPrioritizedAlertSupported());
    EXPECT_TRUE(result->isInstantMessageSupported());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1023, btSpecObj.categoryIDBitMask.categoryIDBitMask);

    EXPECT_EQ("SupportedCategories: { SimpleAlert Email News Call MissedCall SMS/MMS VoiceMail Schedule HighPrioritizedAlert InstantMessage }", result->toString());
}

TEST_F(SupportedNewAlertCategoryTest, TooShort)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<SupportedNewAlertCategory>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(SupportedNewAlertCategoryTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<SupportedNewAlertCategory>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(SupportedNewAlertCategoryTest, ToString)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value(CharacteristicType::SupportedNewAlertCategory,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("SupportedCategories: { SimpleAlert Email News Call MissedCall SMS/MMS VoiceMail Schedule HighPrioritizedAlert InstantMessage }", result->toString());
}

}  // namespace bvp
