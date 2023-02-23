#pragma once

#include <vector>

#include "basevalue.h"


namespace bvp
{

// GATT_Specification_Supplement_v8.pdf
// 3.113.1 Flags field
constexpr uint8_t HRS_FLAG_VALUE_FORMAT    = 1 << 0;
constexpr uint8_t HRS_FLAG_CONTACT_STATUS  = 1 << 1;
constexpr uint8_t HRS_FLAG_CONTACT_SUPPORT = 1 << 2;
constexpr uint8_t HRS_FLAG_ENERGY_EXPENDED = 1 << 3;
constexpr uint8_t HRS_FLAG_RR_INTERVALS    = 1 << 4;
constexpr uint8_t HRS_FLAG_RESERVER1       = 1 << 5;
constexpr uint8_t HRS_FLAG_RESERVER2       = 1 << 6;
constexpr uint8_t HRS_FLAG_RESERVER3       = 1 << 7;

// GATT_Specification_Supplement_v8.pdf
// 3.113 Heart Rate Measurement
struct HeartRateMeasurementStruct
{
    uint8_t flags = 0;
    uint16_t heartRate = 0;
    uint16_t energyExpended = 0;
    std::vector<uint16_t> rrIntervals;
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.1 Heart Rate Measurement
class HeartRateMeasurement final : public BaseValueSpec<HeartRateMeasurementStruct>
{
public:
    bool isContactSupported() const
    {
        return (m_btSpecObject.flags & HRS_FLAG_CONTACT_SUPPORT) != 0;
    }

    bool isContacted() const
    {
        return (m_btSpecObject.flags & HRS_FLAG_CONTACT_STATUS) != 0;
    }

    uint16_t heartRate() const
    {
        return m_btSpecObject.heartRate;
    }

    bool hasEnergyExpended() const
    {
        return (m_btSpecObject.flags & HRS_FLAG_ENERGY_EXPENDED) != 0;
    }

    uint16_t energyExpended() const
    {
        return m_btSpecObject.energyExpended;
    }

    std::vector<uint16_t> rrIntervals() const
    {
        std::vector<uint16_t> result;
        result.reserve(m_btSpecObject.rrIntervals.size());
        // GATT_Specification_Supplement_v8.pdf
        // 3.113.2 RR-Interval field
        // Each RR-Interval value is represented by a uint16 with 1/1024 second as the unit.
        for (auto rrInterval : m_btSpecObject.rrIntervals)
        {
            result.push_back(rrInterval * 1000 / 1024);
        }
        return result;
    }

private:
    BVP_CTORS(BaseValueSpec, HeartRateMeasurement, HeartRateMeasurementStruct)

    virtual bool checkSize(size_t size) override
    {
        // Minimal packet must contain flags(uint8_t)+heartRate(uint8_t)
        return size > 1 && size < 21;
    }

    virtual bool parse(Parser &parser) override
    {
        // 3.1.1.1 Flags Field
        m_btSpecObject.flags = parser.parseUInt8();

        // 3.1.1.2 Heart Rate Measurement Value Field
        if (isWideFormat())
        {
            m_btSpecObject.heartRate = parser.parseUInt16();
        }
        else
        {
            m_btSpecObject.heartRate = parser.parseUInt8();
        }

        // 3.1.1.3 Energy Expended Field
        if (hasEnergyExpended())
        {
            m_btSpecObject.energyExpended = parser.parseUInt16();
        }

        // 3.1.1.4 RR-Interval Field
        if (hasRRIntervals())
        {
            uint8_t maxRRCount = 9;
            if (isWideFormat())
            {
                --maxRRCount;
            }
            if (hasEnergyExpended())
            {
                --maxRRCount;
            }
            m_btSpecObject.rrIntervals.reserve(maxRRCount);

            for (uint8_t i = 0; i < maxRRCount && !parser.atEnd(); ++i)
            {
                m_btSpecObject.rrIntervals.push_back(parser.parseUInt16());
            }
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        if (isContactSupported())
        {
            if (isContacted())
            {
                ss << "(connected) ";
            }
            else
            {
                ss << "(disconnected) ";
            }
        }

        ss << "HR: " << m_btSpecObject.heartRate << "bpm";

        if (hasEnergyExpended())
        {
            ss << ", EE: " << m_btSpecObject.energyExpended << "kJ";
        }

        if (!m_btSpecObject.rrIntervals.empty())
        {
            ss << ", RR: { ";
            for (auto rrInterval : rrIntervals())
            {
                ss << rrInterval << "ms; ";
            }
            ss << "}";
        }
    }

    bool isWideFormat() const
    {
        return (m_btSpecObject.flags & HRS_FLAG_VALUE_FORMAT) != 0;
    }

    bool hasRRIntervals() const
    {
        return (m_btSpecObject.flags & HRS_FLAG_RR_INTERVALS) != 0;
    }
};

}  // namespace bvp
