#pragma once

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.35.1 Body Sensor Location field
enum class BodySensorLocationEnum
{
    Unknown     = 0xFF,  // 0x07–0xFF - Reserved for Future Use
    Other       = 0,
    Chest       = 1,
    Wrist       = 2,
    Finger      = 3,
    Hand        = 4,
    EarLobe     = 5,
    Foot        = 6
};

// GATT_Specification_Supplement_v8.pdf
// 3.35 Body Sensor Location
struct BodySensorLocationStruct
{
    BodySensorLocationEnum bodySensorLocation = BodySensorLocationEnum::Unknown;
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.2 BodySensorLocation
class BodySensorLocation final : public BaseValue
{
public:
    BodySensorLocationStruct getBtSpecObject() const
    {
        return m_bodySensorLocation;
    }

    BodySensorLocationEnum location() const
    {
        return m_bodySensorLocation.bodySensorLocation;
    }

private:
    friend class BLEValueParser;

    explicit BodySensorLocation(Parser &parser, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(parser);
    }

    explicit BodySensorLocation(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit BodySensorLocation(const BodySensorLocationStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_bodySensorLocation{btSpecObject}
    {
        m_isValid = true;
    }

    BodySensorLocationStruct m_bodySensorLocation;

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        // GATT_Specification_Supplement_v8.pdf
        // 3.35 Body Sensor Location
        m_bodySensorLocation.bodySensorLocation = BodySensorLocationEnum(parser.parseUInt8());
        switch (m_bodySensorLocation.bodySensorLocation)
        {
            case BodySensorLocationEnum::Unknown:
            case BodySensorLocationEnum::Other:
            case BodySensorLocationEnum::Chest:
            case BodySensorLocationEnum::Wrist:
            case BodySensorLocationEnum::Finger:
            case BodySensorLocationEnum::Hand:
            case BodySensorLocationEnum::EarLobe:
            case BodySensorLocationEnum::Foot:
                break;
            default:
                m_bodySensorLocation.bodySensorLocation = BodySensorLocationEnum::Unknown;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_bodySensorLocation.bodySensorLocation)
        {
        case BodySensorLocationEnum::Unknown: ss << "<Unknown>"; break;
        case BodySensorLocationEnum::Other:   ss << "Other"; break;
        case BodySensorLocationEnum::Chest:   ss << "Chest"; break;
        case BodySensorLocationEnum::Wrist:   ss << "Wrist"; break;
        case BodySensorLocationEnum::Finger:  ss << "Finger"; break;
        case BodySensorLocationEnum::Hand:    ss << "Hand"; break;
        case BodySensorLocationEnum::EarLobe: ss << "Ear Lobe"; break;
        case BodySensorLocationEnum::Foot:    ss << "Foot"; break;
        }
    }
};

}  // namespace bvp
