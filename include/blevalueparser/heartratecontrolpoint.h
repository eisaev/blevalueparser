#pragma once

#include "basevalue.h"


namespace bvp
{

/*
 * Heart Rate Service
 * HRS_SPEC_V10.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.111.1 Heart Rate Control Point field (Table 3.191)
enum class HeartRateControlPointEnum : uint8_t
{
    Reserved            = 0,  // 0, 2–255 - Reserved for Future Use
    ResetEnergyExpended = 1
};

// GATT_Specification_Supplement_v8.pdf
// 3.111 Heart Rate Control Point
struct HeartRateControlPointStruct
{
    HeartRateControlPointEnum heartRateControlPoint = HeartRateControlPointEnum::Reserved;
};

// 3.3 Heart Rate Control Point
class HeartRateControlPoint final : public BaseValue
{
public:
    HeartRateControlPointStruct getBtSpecObject() const
    {
        return m_heartRateControlPoint;
    }

    HeartRateControlPointEnum controlPointType() const
    {
        return m_heartRateControlPoint.heartRateControlPoint;
    }

private:
    friend class BLEValueParser;
    explicit HeartRateControlPoint(const char *data, size_t size, const Configuration &configuration) :
        BaseValue{configuration}
    {
        create(data, size);
    }

    explicit HeartRateControlPoint(const HeartRateControlPointStruct &btSpecObject, const Configuration &configuration) :
        BaseValue{configuration},
        m_heartRateControlPoint{btSpecObject}
    {
        m_isValid = true;
    }

    HeartRateControlPointStruct m_heartRateControlPoint;

    static size_t expectedSize()
    {
        return 1;
    }

    virtual bool checkSize(size_t size) override
    {
        return size == expectedSize();
    }

    virtual bool parse(Parser &parser) override
    {
        // 3.111.1 Heart Rate Control Point field
        m_heartRateControlPoint.heartRateControlPoint = HeartRateControlPointEnum(parser.parseUInt8());
        switch (m_heartRateControlPoint.heartRateControlPoint)
        {
            case HeartRateControlPointEnum::Reserved:
            case HeartRateControlPointEnum::ResetEnergyExpended:
                break;
            default:
                m_heartRateControlPoint.heartRateControlPoint = HeartRateControlPointEnum::Reserved;
                break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_heartRateControlPoint.heartRateControlPoint)
        {
            case HeartRateControlPointEnum::Reserved:
                ss << "<Reserved>";
                break;
            case HeartRateControlPointEnum::ResetEnergyExpended:
                ss << "ResetEnergyExpended";
                break;
        }
    }
};

}  // namespace bvp
