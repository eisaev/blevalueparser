#include "gtest/gtest.h"

#include "blevalueparser.h"


namespace bvp
{

class BodySensorLocationTest : public testing::Test
{
protected:
    explicit BodySensorLocationTest() {}
    virtual ~BodySensorLocationTest() {}

    BLEValueParser bleValueParser;

//    virtual void SetUp() {}
//    virtual void TearDown() {}
};

TEST_F(BodySensorLocationTest, Other)
{
    constexpr char data[] = { '\x00' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Other, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Other, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Other", result->toString());
}

TEST_F(BodySensorLocationTest, Chest)
{
    constexpr char data[] = { '\x01' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Chest, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Chest, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Chest", result->toString());
}

TEST_F(BodySensorLocationTest, Wrist)
{
    constexpr char data[] = { '\x02' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Wrist, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Wrist, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Wrist", result->toString());
}

TEST_F(BodySensorLocationTest, Finger)
{
    constexpr char data[] = { '\x03' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Finger, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Finger, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Finger", result->toString());
}

TEST_F(BodySensorLocationTest, Hand)
{
    constexpr char data[] = { '\x04' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Hand, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Hand, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Hand", result->toString());
}

TEST_F(BodySensorLocationTest, EarLobe)
{
    constexpr char data[] = { '\x05' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::EarLobe, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::EarLobe, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Ear Lobe", result->toString());
}

TEST_F(BodySensorLocationTest, Foot)
{
    constexpr char data[] = { '\x06' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Foot, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Foot, btSpecObj.bodySensorLocation);

    EXPECT_EQ("Foot", result->toString());
}

TEST_F(BodySensorLocationTest, Unknown)
{
    constexpr char data[] = { '\x07' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Unknown, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Unknown, btSpecObj.bodySensorLocation);

    EXPECT_EQ("<Unknown>", result->toString());
}

TEST_F(BodySensorLocationTest, Empty)
{
    constexpr char data[] = {};

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Unknown, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Unknown, btSpecObj.bodySensorLocation);

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BodySensorLocationTest, InvalidSize)
{
    constexpr char data[] = { '\x01', '\x02' };

    auto result = bleValueParser.make_value<BodySensorLocation>(data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_FALSE(result->isValid());
    EXPECT_EQ(BodySensorLocationEnum::Unknown, result->location());

    auto btSpecObj = result->getBtSpecObject();
    EXPECT_EQ(BodySensorLocationEnum::Unknown, btSpecObj.bodySensorLocation);

    EXPECT_EQ("<Invalid>", result->toString());
}

TEST_F(BodySensorLocationTest, ToString)
{
    constexpr char data[] = { '\x06' };

    auto result = bleValueParser.make_value(CharacteristicType::BodySensorLocation,
                                            data, sizeof(data));
    EXPECT_NE(nullptr, result);
    EXPECT_TRUE(result->isValid());

    EXPECT_EQ("Foot", result->toString());
}

}  // namespace bvp
