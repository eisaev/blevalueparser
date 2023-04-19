#include <benchmark/benchmark.h>
#include <blevalueparser/bvp.h>

#include "datagenerator.h"

using namespace bvp;


template <class T>
static void String(benchmark::State& state)
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
        result->toString();
    }
}

BENCHMARK(String<AlertCategoryIDBitMask>);
BENCHMARK(String<AlertCategoryID>);
BENCHMARK(String<AlertNotificationControlPoint>);
BENCHMARK(String<BatteryCriticalStatus>);
BENCHMARK(String<BatteryEnergyStatus>);
BENCHMARK(String<BatteryHealthInformation>);
BENCHMARK(String<BatteryHealthStatus>);
BENCHMARK(String<BatteryInformation>);
BENCHMARK(String<BatteryLevelStatus>);
BENCHMARK(String<BatteryLevel>);
BENCHMARK(String<BatteryTimeStatus>);
BENCHMARK(String<BodyCompositionFeature>);
BENCHMARK(String<BodyCompositionMeasurementMIBFS>);
BENCHMARK(String<BodyCompositionMeasurement>);
BENCHMARK(String<BodySensorLocation>);
BENCHMARK(String<CurrentTime>);
BENCHMARK(String<DateTime>);
BENCHMARK(String<DateUTC>);
BENCHMARK(String<DayDateTime>);
BENCHMARK(String<DayOfWeek>);
BENCHMARK(String<DSTOffset>);
BENCHMARK(String<EstimatedServiceDate>);
BENCHMARK(String<ExactTime256>);
BENCHMARK(String<HeartRateControlPoint>);
BENCHMARK(String<HeartRateMeasurement>);
BENCHMARK(String<HexString>)->RangeMultiplier(8)->Range(1, 512);
BENCHMARK(String<LocalTimeInformation>);
BENCHMARK(String<NewAlert>);
BENCHMARK(String<PnPID>);
BENCHMARK(String<ReferenceTimeInformation>);
BENCHMARK(String<SupportedNewAlertCategory>);
BENCHMARK(String<SupportedUnreadAlertCategory>);
BENCHMARK(String<TextString>)->RangeMultiplier(8)->Range(1, 512);
BENCHMARK(String<TimeAccuracy>);
BENCHMARK(String<TimeSource>);
BENCHMARK(String<TimeZone>);
BENCHMARK(String<UnreadAlertStatus>);
BENCHMARK(String<UserIndex>);
