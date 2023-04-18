#include <benchmark/benchmark.h>
#include <blevalueparser/bvp.h>

#include "datagenerator.h"

using namespace bvp;

#include <iostream>
template <class T>
static void Parser(benchmark::State& state)
{
    std::string data = DataGenerator::make_data<T>(state);
    bvp::BLEValueParser bleValueParser;
    auto result = bleValueParser.make_value<T>(data.c_str(), data.size());
    if (!result->isValid())
    {
        state.SkipWithError("Invalid object");
    }

    for (auto _ : state)
    {
        result = bleValueParser.make_value<T>(data.c_str(), data.size());
    }
}

BENCHMARK(Parser<AlertCategoryIDBitMask>);
BENCHMARK(Parser<AlertCategoryID>);
BENCHMARK(Parser<AlertNotificationControlPoint>);
BENCHMARK(Parser<BatteryCriticalStatus>);
BENCHMARK(Parser<BatteryEnergyStatus>);
BENCHMARK(Parser<BatteryHealthInformation>);
BENCHMARK(Parser<BatteryHealthStatus>);
BENCHMARK(Parser<BatteryInformation>);
BENCHMARK(Parser<BatteryLevelStatus>);
BENCHMARK(Parser<BatteryLevel>);
BENCHMARK(Parser<BatteryTimeStatus>);
BENCHMARK(Parser<BodyCompositionFeature>);
BENCHMARK(Parser<BodyCompositionMeasurementMIBFS>);
BENCHMARK(Parser<BodyCompositionMeasurement>);
BENCHMARK(Parser<BodySensorLocation>);
BENCHMARK(Parser<CurrentTime>);
BENCHMARK(Parser<DateTime>);
BENCHMARK(Parser<DateUTC>);
BENCHMARK(Parser<DayDateTime>);
BENCHMARK(Parser<DayOfWeek>);
BENCHMARK(Parser<DSTOffset>);
BENCHMARK(Parser<EstimatedServiceDate>);
BENCHMARK(Parser<ExactTime256>);
BENCHMARK(Parser<HeartRateControlPoint>);
BENCHMARK(Parser<HeartRateMeasurement>);
BENCHMARK(Parser<HexString>)->RangeMultiplier(8)->Range(1, 512);
BENCHMARK(Parser<LocalTimeInformation>);
BENCHMARK(Parser<NewAlert>);
BENCHMARK(Parser<PnPID>);
BENCHMARK(Parser<ReferenceTimeInformation>);
BENCHMARK(Parser<SupportedNewAlertCategory>);
BENCHMARK(Parser<SupportedUnreadAlertCategory>);
BENCHMARK(Parser<TextString>)->RangeMultiplier(8)->Range(1, 512);
BENCHMARK(Parser<TimeAccuracy>);
BENCHMARK(Parser<TimeSource>);
BENCHMARK(Parser<TimeZone>);
BENCHMARK(Parser<UnreadAlertStatus>);
BENCHMARK(Parser<UserIndex>);
