#include <gtest/gtest.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


namespace bvp
{

struct AlertCategoryIDBitMaskTest : public testing::Test
{
    BLEValueParser bleValueParser;
};

TEST_F(AlertCategoryIDBitMaskTest, ReservedAll_CategoryNone)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b11111100), C(0b00000000) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<AlertCategoryIDBitMask>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->hasSimpleAlert());
    EXPECT_FALSE(result->hasEmail());
    EXPECT_FALSE(result->hasNews());
    EXPECT_FALSE(result->hasCall());
    EXPECT_FALSE(result->hasMissedCall());
    EXPECT_FALSE(result->hasSMSMMS());
    EXPECT_FALSE(result->hasVoiceMail());
    EXPECT_FALSE(result->hasSchedule());
    EXPECT_FALSE(result->hasHighPrioritizedAlert());
    EXPECT_FALSE(result->hasInstantMessage());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(64512, btSpecObj.categoryIDBitMask);

    EXPECT_EQ("{ }", result->toString());
}

TEST_F(AlertCategoryIDBitMaskTest, ReservedEven_CategoryOdd)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b10101001), C(0b01010101) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<AlertCategoryIDBitMask>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->hasSimpleAlert());
    EXPECT_FALSE(result->hasEmail());
    EXPECT_TRUE(result->hasNews());
    EXPECT_FALSE(result->hasCall());
    EXPECT_TRUE(result->hasMissedCall());
    EXPECT_FALSE(result->hasSMSMMS());
    EXPECT_TRUE(result->hasVoiceMail());
    EXPECT_FALSE(result->hasSchedule());
    EXPECT_TRUE(result->hasHighPrioritizedAlert());
    EXPECT_FALSE(result->hasInstantMessage());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(43349, btSpecObj.categoryIDBitMask);

    EXPECT_EQ("{ SimpleAlert News MissedCall VoiceMail HighPrioritizedAlert }", result->toString());
}

TEST_F(AlertCategoryIDBitMaskTest, ReservedOdd_CategoryEven)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b01010110), C(0b10101010) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<AlertCategoryIDBitMask>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_FALSE(result->hasSimpleAlert());
    EXPECT_TRUE(result->hasEmail());
    EXPECT_FALSE(result->hasNews());
    EXPECT_TRUE(result->hasCall());
    EXPECT_FALSE(result->hasMissedCall());
    EXPECT_TRUE(result->hasSMSMMS());
    EXPECT_FALSE(result->hasVoiceMail());
    EXPECT_TRUE(result->hasSchedule());
    EXPECT_FALSE(result->hasHighPrioritizedAlert());
    EXPECT_TRUE(result->hasInstantMessage());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(22186, btSpecObj.categoryIDBitMask);

    EXPECT_EQ("{ Email Call SMS/MMS Schedule InstantMessage }", result->toString());
}
TEST_F(AlertCategoryIDBitMaskTest, ReservedNone_CategoryAll)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value<AlertCategoryIDBitMask>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_TRUE(result->hasSimpleAlert());
    EXPECT_TRUE(result->hasEmail());
    EXPECT_TRUE(result->hasNews());
    EXPECT_TRUE(result->hasCall());
    EXPECT_TRUE(result->hasMissedCall());
    EXPECT_TRUE(result->hasSMSMMS());
    EXPECT_TRUE(result->hasVoiceMail());
    EXPECT_TRUE(result->hasSchedule());
    EXPECT_TRUE(result->hasHighPrioritizedAlert());
    EXPECT_TRUE(result->hasInstantMessage());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(1023, btSpecObj.categoryIDBitMask);

    EXPECT_EQ("{ SimpleAlert Email News Call MissedCall SMS/MMS VoiceMail Schedule HighPrioritizedAlert InstantMessage }", result->toString());
}

TEST_F(AlertCategoryIDBitMaskTest, TooShort)
{
    constexpr char data[] = { '\x2A' };

    auto result = bleValueParser.make_value<AlertCategoryIDBitMask>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(AlertCategoryIDBitMaskTest, TooLong)
{
    constexpr char data[] = { '\x2A', '\x2A', '\x2A' };

    auto result = bleValueParser.make_value<AlertCategoryIDBitMask>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(AlertCategoryIDBitMaskTest, ToString)
{
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    auto result = bleValueParser.make_value(CharacteristicType::AlertCategoryIDBitMask,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("{ SimpleAlert Email News Call MissedCall SMS/MMS VoiceMail Schedule HighPrioritizedAlert InstantMessage }", result->toString());
}

}  // namespace bvp
