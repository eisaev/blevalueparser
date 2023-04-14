#include <benchmark/benchmark.h>

#include "blevalueparser/bvp.h"

#define C(x) static_cast<char>(x)


static void AlertCategoryIDBitMask(benchmark::State& state) {
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::AlertCategoryIDBitMask>(data, sizeof(data));
    }
}
BENCHMARK(AlertCategoryIDBitMask);

static void AlertCategoryID(benchmark::State& state) {
    constexpr char data[] = { '\x00' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::AlertCategoryID>(data, sizeof(data));
    }
}
BENCHMARK(AlertCategoryID);

static void AlertNotificationControlPoint(benchmark::State& state) {
    constexpr char data[] = {
        '\x05', // commandID
        '\x00'  // categoryID
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::AlertNotificationControlPoint>(data, sizeof(data));
    }
}
BENCHMARK(AlertNotificationControlPoint);

static void BatteryCriticalStatus(benchmark::State& state) {
    constexpr char data[] = { C(0b00000011) };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryCriticalStatus>(data, sizeof(data));
    }
}
BENCHMARK(BatteryCriticalStatus);

static void BatteryEnergyStatus(benchmark::State& state) {
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

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryEnergyStatus>(data, sizeof(data));
    }
}
BENCHMARK(BatteryEnergyStatus);

static void BatteryHealthInformation(benchmark::State& state) {
    //                         RRRRRRTC
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCountDesignedLifetime
        '\x81',         // minDesignedOperatingTemperature
        '\x7E'          // maxDesignedOperatingTemperature
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryHealthInformation>(data, sizeof(data));
    }
}
BENCHMARK(BatteryHealthInformation);

static void BatteryHealthStatus(benchmark::State& state) {
    //                         RRRRDTCS
    constexpr char flags = C(0b00001111);
    constexpr char data[] = {
        flags,
        '\x00',         // batteryHealthSummary
        '\x00', '\x2A', // cycleCount
        '\x00',         // currentTemperature
        '\xFF', '\xFF'  // deepDischargeCount
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryHealthStatus>(data, sizeof(data));
    }
}
BENCHMARK(BatteryHealthStatus);

static void BatteryInformation(benchmark::State& state) {
    //                             RRRRRRRR       GVHCLDEM
    constexpr char flags[] = { C(0b00000000), C(0b11111111) };
    //                            RRRRRRCP
    constexpr char features = C(0b00000011);
    constexpr char data[] = {
        flags[1], flags[0],
        features,                        // batteryFeatures
        '\xD8', '\x3B', '\x00',          // batteryManufactureDate
        '\xD8', '\x5B', '\x00',          // batteryExpirationDate
        C(0b11100010), C(0b00001000),    // batteryDesignedCapacity
        C(0b11110000), C(0b00000011),    // batteryLowEnergy
        C(0b11110000), C(0b00000001),    // batteryCriticalEnergy
        '\x05',                          // batteryChemistry
        C(0b11110000), C(0b00101010),    // nominalVoltage
        '\x01'                           // batteryAggregationGroup
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryInformation>(data, sizeof(data));
    }
}
BENCHMARK(BatteryInformation);

static void BatteryLevelStatus(benchmark::State& state) {
    //                         RRRRRALI
    constexpr char flags = C(0b00000111);
    //                                  RFFFTTTL       LSSWWEEB
    constexpr char powerState[] = { C(0b01110001), C(0b10011001) };
    //                                    RRRRRFSS
    constexpr char additionalStatus = C(0b11111100);
    constexpr char data[] = {
        flags,
        powerState[1], powerState[0],   // powerState
        '\x0A', '\x0B',                 // identifier
        '\x2A',                         // batteryLevel
        additionalStatus                // additionalStatus
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryLevelStatus>(data, sizeof(data));
    }
}
BENCHMARK(BatteryLevelStatus);

static void BatteryLevel(benchmark::State& state) {
    constexpr char data[] = { '\x64' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryLevel>(data, sizeof(data));
    }
}
BENCHMARK(BatteryLevel);

static void BatteryTimeStatus(benchmark::State& state) {
    //                         RRRRRRCS
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', '\x2A', // timeUntilDischarged
        '\xFD', '\xFF', '\xFF', // timeUntilDischargedOnStandby
        '\xFF', '\xFF', '\xFF'  // timeUntilRecharged
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BatteryTimeStatus>(data, sizeof(data));
    }
}
BENCHMARK(BatteryTimeStatus);

static void BodyCompositionFeature(benchmark::State& state) {
    //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b10101010), C(0b10101000), C(0b00000111), C(0b11111111) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BodyCompositionFeature>(data, sizeof(data));
    }
}
BENCHMARK(BodyCompositionFeature);

static void BodyCompositionMeasurementMIBFS(benchmark::State& state) {
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10100110), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BodyCompositionMeasurementMIBFS>(data, sizeof(data));
    }
}
BENCHMARK(BodyCompositionMeasurementMIBFS);

static void BodyCompositionMeasurement(benchmark::State& state) {
    //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10101111), C(0b11111111) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\x12', '\x34',                                         // bodyFatPercentage
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x2A',                                                 // userID
        '\x23', '\x45',                                         // basalMetabolism
        '\x34', '\x56',                                         // musclePercentage
        '\x45', '\x67',                                         // muscleMass
        '\x56', '\x78',                                         // fatFreeMass
        '\x67', '\x89',                                         // softLeanMass
        '\x78', '\x9A',                                         // bodyWaterMass
        '\x89', '\xAB',                                         // impedance
        '\x9A', '\xBC',                                         // weight
        '\xAB', '\xCD'                                          // height
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BodyCompositionMeasurement>(data, sizeof(data));
    }
}
BENCHMARK(BodyCompositionMeasurement);

static void BodySensorLocation(benchmark::State& state) {
    constexpr char data[] = { '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::BodySensorLocation>(data, sizeof(data));
    }
}
BENCHMARK(BodySensorLocation);

static void CurrentTime(benchmark::State& state) {
    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\x07', '\xFF', '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::CurrentTime>(data, sizeof(data));
    }
}
BENCHMARK(CurrentTime);

static void DateTime(benchmark::State& state) {
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::DateTime>(data, sizeof(data));
    }
}
BENCHMARK(DateTime);

static void DateUTC(benchmark::State& state) {
    constexpr char data[] = { '\xD8', '\x4B', '\x00' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::DateUTC>(data, sizeof(data));
    }
}
BENCHMARK(DateUTC);

// TODO: ~50ns!
static void DayDateTime(benchmark::State& state) {
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07', '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::DayDateTime>(data, sizeof(data));
    }
}
BENCHMARK(DayDateTime);

static void DayOfWeek(benchmark::State& state) {
    constexpr char data[] = { '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::DayOfWeek>(data, sizeof(data));
    }
}
BENCHMARK(DayOfWeek);

static void DSTOffset(benchmark::State& state) {
    constexpr char data[] = { '\x04' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::DSTOffset>(data, sizeof(data));
    }
}
BENCHMARK(DSTOffset);

static void EstimatedServiceDate(benchmark::State& state) {
    constexpr char data[] = { '\xD8', '\x4B', '\x00' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::EstimatedServiceDate>(data, sizeof(data));
    }
}
BENCHMARK(EstimatedServiceDate);

static void ExactTime256(benchmark::State& state) {
    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x05', '\x14', '\x16', '\x07', '\x04', '\x80' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::ExactTime256>(data, sizeof(data));
    }
}
BENCHMARK(ExactTime256);

static void HeartRateControlPoint(benchmark::State& state) {
    constexpr char data[] = { '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::HeartRateControlPoint>(data, sizeof(data));
    }
}
BENCHMARK(HeartRateControlPoint);

static void HeartRateMeasurement(benchmark::State& state) {
    constexpr char flags = C(0b00011001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::HeartRateMeasurement>(data, sizeof(data));
    }
}
BENCHMARK(HeartRateMeasurement);

static void HexString(benchmark::State& state) {
    size_t size = static_cast<size_t>(state.range(0));
    std::string data;
    data.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        data.push_back(size & 0xFF);
    }

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::HexString>(data.c_str(), data.size());
    }
}
BENCHMARK(HexString)->RangeMultiplier(8)->Range(1, 512);

static void LocalTimeInformation(benchmark::State& state) {
    constexpr char data[] = { '\xD0', '\x02' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::LocalTimeInformation>(data, sizeof(data));
    }
}
BENCHMARK(LocalTimeInformation);

static void NewAlert(benchmark::State& state) {
    constexpr char data[] = {
        '\x05',                         // categoryID
        '\x2A',                         // numberOfNewAlert
        'D', 'o', 'n', '\'', 't', ' ',
        'p', 'a', 'n', 'i', 'c', '!'    // textStringInformation
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::NewAlert>(data, sizeof(data));
    }
}
BENCHMARK(NewAlert);

static void PnPID(benchmark::State& state) {
    constexpr char data[] = { '\x02', '\x12', '\x00', '\x23', '\x01', '\xBC', '\xAA' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::PnPID>(data, sizeof(data));
    }
}
BENCHMARK(PnPID);

static void ReferenceTimeInformation(benchmark::State& state) {
    constexpr char data[] = { '\x01', '\xAA', '\x2A', '\x0F' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::ReferenceTimeInformation>(data, sizeof(data));
    }
}
BENCHMARK(ReferenceTimeInformation);

static void SupportedNewAlertCategory(benchmark::State& state) {
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::SupportedNewAlertCategory>(data, sizeof(data));
    }
}
BENCHMARK(SupportedNewAlertCategory);

static void SupportedUnreadAlertCategory(benchmark::State& state) {
    //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::SupportedUnreadAlertCategory>(data, sizeof(data));
    }
}
BENCHMARK(SupportedUnreadAlertCategory);

static void TextString(benchmark::State& state) {
    constexpr char data[] = { 'a', 'B', 'c', 'X', 'y', 'Z' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::TextString>(data, sizeof(data));
    }
}
BENCHMARK(TextString);

static void TimeAccuracy(benchmark::State& state) {
    constexpr char data[] = { '\x2A' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::TimeAccuracy>(data, sizeof(data));
    }
}
BENCHMARK(TimeAccuracy);

static void TimeSource(benchmark::State& state) {
    constexpr char data[] = { '\x01' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::TimeSource>(data, sizeof(data));
    }
}
BENCHMARK(TimeSource);

static void TimeZone(benchmark::State& state) {
    constexpr char data[] = { '\x38' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::TimeZone>(data, sizeof(data));
    }
}
BENCHMARK(TimeZone);

static void UnreadAlertStatus(benchmark::State& state) {
    constexpr char data[] = {
        '\x02', // categoryID
        '\x2A'  // unreadCount
    };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::UnreadAlertStatus>(data, sizeof(data));
    }
}
BENCHMARK(UnreadAlertStatus);

static void UserIndex(benchmark::State& state) {
    constexpr char data[] = { '\x2A' };

    bvp::BLEValueParser bleValueParser;

    for (auto _ : state)
    {
        auto result = bleValueParser.make_value<bvp::UserIndex>(data, sizeof(data));
    }
}
BENCHMARK(UserIndex);

BENCHMARK_MAIN();
