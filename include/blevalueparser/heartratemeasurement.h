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
    uint8_t flags{0};
    uint16_t heartRate{0};  // org.bluetooth.unit.period.beats_per_minute
    uint16_t energyExpended{0};  // org.bluetooth.unit.energy.joule * 1000
    std::vector<uint16_t> rrIntervals;
};

// HRS_SPEC_V10.pdf
// Heart Rate Service v10r00
// 3.1 Heart Rate Measurement
class HeartRateMeasurement final : public BaseValueSpec<HeartRateMeasurementStruct>
{
public:
    BVP_GETTER(bool, isContactSupported, HeartRateMeasurementStruct)
    {
        return (btSpecObject.flags & HRS_FLAG_CONTACT_SUPPORT) != 0;
    }

    BVP_GETTER(bool, isContacted, HeartRateMeasurementStruct)
    {
        return (btSpecObject.flags & HRS_FLAG_CONTACT_STATUS) != 0;
    }

    BVP_GETTER(bool, isWideFormat, HeartRateMeasurementStruct)
    {
        return (btSpecObject.flags & HRS_FLAG_VALUE_FORMAT) != 0;
    }

    BVP_GETTER(uint16_t, heartRate, HeartRateMeasurementStruct)
    {
        return btSpecObject.heartRate;
    }

    BVP_GETTER(bool, hasEnergyExpended, HeartRateMeasurementStruct)
    {
        return (btSpecObject.flags & HRS_FLAG_ENERGY_EXPENDED) != 0;
    }

    BVP_GETTER(uint16_t, energyExpended, HeartRateMeasurementStruct)
    {
        return btSpecObject.energyExpended;
    }

    BVP_GETTER(bool, hasRRIntervals, HeartRateMeasurementStruct)
    {
        return (btSpecObject.flags & HRS_FLAG_RR_INTERVALS) != 0;
    }

    BVP_GETTER(std::vector<uint16_t>, rrIntervals, HeartRateMeasurementStruct)
    {
        std::vector<uint16_t> result;
        result.reserve(btSpecObject.rrIntervals.size());
        // GATT_Specification_Supplement_v8.pdf
        // 3.113.2 RR-Interval field
        // Each RR-Interval value is represented by a uint16 with 1/1024 second as the unit.
        for (auto rrInterval : btSpecObject.rrIntervals)
        {
            result.push_back(rrInterval * 1000 / 1024);
        }
        return result;
    }

private:
    BVP_CTORS(BaseValueSpec, HeartRateMeasurement, HeartRateMeasurementStruct)

    BVP_PARSE(HeartRateMeasurementStruct)
    {
        bool result{true};

        // 3.1.1.1 Flags Field
        btSpecObject.flags = parser.parseUInt8();

        // 3.1.1.2 Heart Rate Measurement Value Field
        if (isWideFormat(btSpecObject))
        {
            btSpecObject.heartRate = parser.parseUInt16();
        }
        else
        {
            btSpecObject.heartRate = parser.parseUInt8();
        }

        // 3.1.1.3 Energy Expended Field
        if (hasEnergyExpended(btSpecObject))
        {
            btSpecObject.energyExpended = parser.parseUInt16();
        }

        // 3.1.1.4 RR-Interval Field
        if (hasRRIntervals(btSpecObject))
        {
            uint8_t maxRRCount = 9;
            if (isWideFormat(btSpecObject))
            {
                --maxRRCount;
            }
            if (hasEnergyExpended(btSpecObject))
            {
                --maxRRCount;
            }
            btSpecObject.rrIntervals.reserve(maxRRCount);

            for (uint8_t i = 0; i < maxRRCount && !parser.atEnd(); ++i)
            {
                btSpecObject.rrIntervals.push_back(parser.parseUInt16());
            }
        }

        return result;
    }

    BVP_TO_STRING(HeartRateMeasurementStruct)
    {
        std::string str;

        if (isContactSupported(btSpecObject))
        {
            if (isContacted(btSpecObject))
            {
                str.append("(connected) ");
            }
            else
            {
                str.append("(disconnected) ");
            }
        }

        fmt::format_to(
            std::back_inserter(str),
            "HR: {}bpm",
            btSpecObject.heartRate
        );

        if (hasEnergyExpended(btSpecObject))
        {
            fmt::format_to(
                std::back_inserter(str),
                ", EE: {}kJ",
                btSpecObject.energyExpended
            );
        }

        if (!btSpecObject.rrIntervals.empty())
        {
            str.append(", RR: { ");
            for (auto rrInterval : rrIntervals(btSpecObject))
            {
                fmt::format_to(
                    std::back_inserter(str),
                    "{}ms; ",
                    rrInterval
                );
            }
            str.append("}");
        }

        return str;
    }

    virtual bool checkSize(size_t size) override
    {
        // Minimal packet must contain flags(uint8_t)+heartRate(uint8_t)
        return size > 1 && size < 21;
    }
};

}  // namespace bvp
