#include <blevalueparser/bvp.h>

#include "datagenerator.h"

#define C(x) static_cast<char>(x)

using namespace bvp;


template<>
std::string DataGenerator::make_data<AlertCategoryIDBitMask>(const benchmark::State& state)
{
    (void)state;

           //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<AlertCategoryID>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x00' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<AlertNotificationControlPoint>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = {
        '\x05', // commandID
        '\x00'  // categoryID
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryCriticalStatus>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { C(0b00000011) };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryEnergyStatus>(const benchmark::State& state)
{
    (void)state;

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

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryHealthInformation>(const benchmark::State& state)
{
    (void)state;

           //                         RRRRRRTC
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', // cycleCountDesignedLifetime
        '\x81',         // minDesignedOperatingTemperature
        '\x7E'          // maxDesignedOperatingTemperature
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryHealthStatus>(const benchmark::State& state)
{
    (void)state;

           //                         RRRRDTCS
    constexpr char flags = C(0b00001111);
    constexpr char data[] = {
        flags,
        '\x00',         // batteryHealthSummary
        '\x00', '\x2A', // cycleCount
        '\x00',         // currentTemperature
        '\xFF', '\xFF'  // deepDischargeCount
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryInformation>(const benchmark::State& state)
{
    (void)state;

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

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryLevelStatus>(const benchmark::State& state)
{
    (void)state;

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

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryLevel>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x64' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BatteryTimeStatus>(const benchmark::State& state)
{
    (void)state;

           //                         RRRRRRCS
    constexpr char flags = C(0b00000011);
    constexpr char data[] = {
        flags,
        '\x00', '\x2A', '\x2A', // timeUntilDischarged
        '\xFD', '\xFF', '\xFF', // timeUntilDischargedOnStandby
        '\xFF', '\xFF', '\xFF'  // timeUntilRecharged
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BodyCompositionFeature>(const benchmark::State& state)
{
    (void)state;

           //                             RRRRRRRR       RRRRRRHH       HWWWWFFF       FFFFFFFF
    constexpr char flags[] = { C(0b10101010), C(0b10101000), C(0b00000111), C(0b11111111) };
    constexpr char data[] = { flags[3], flags[2], flags[1], flags[0] };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BodyCompositionMeasurementMIBFS>(const benchmark::State& state)
{
    (void)state;

           //                             RRRMFFFF       FFFFFFFU
    constexpr char flags[] = { C(0b10100110), C(0b00000010) };
    constexpr char data[] = {
        flags[1], flags[0],
        '\xE7', '\x07', '\x02', '\x06', '\x12', '\x1C', '\x00', // timeStamp
        '\x12', '\x34',                                         // impedance
        '\x56', '\x78'                                          // weight
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BodyCompositionMeasurement>(const benchmark::State& state)
{
    (void)state;

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

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<BodySensorLocation>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<CurrentTime>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xE6', '\x07', '\x0C', '\x1F', '\x17', '\x3B', '\x3B', '\x07', '\xFF', '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<DateTime>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<DateUTC>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xD8', '\x4B', '\x00' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<DayDateTime>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x02', '\x14', '\x16', '\x07', '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<DayOfWeek>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<DSTOffset>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x04' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<EstimatedServiceDate>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xD8', '\x4B', '\x00' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<ExactTime256>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xE7', '\x07', '\x01', '\x05', '\x14', '\x16', '\x07', '\x04', '\x80' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<HeartRateControlPoint>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<HeartRateMeasurement>(const benchmark::State& state)
{
    (void)state;

    constexpr char flags = C(0b00011001);
    constexpr char data[] = { flags, '\xAA', '\x01', '\xBB', '\x01', '\xA1', '\x01', '\xA2', '\x01', '\xA3', '\x01', '\xA4', '\x01', '\xA5', '\x01', '\xA6', '\x01', '\xA7', '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<HexString>(const benchmark::State& state)
{
    size_t size = static_cast<size_t>(state.range(0));
    std::string data;
    data.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        data.push_back(size & 0xFF);
    }

    return data;
}

template<>
std::string DataGenerator::make_data<LocalTimeInformation>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\xD0', '\x02' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<NewAlert>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = {
        '\x05',                         // categoryID
        '\x2A',                         // numberOfNewAlert
        'D', 'o', 'n', '\'', 't', ' ',
        'p', 'a', 'n', 'i', 'c', '!'    // textStringInformation
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<PnPID>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x02', '\x12', '\x00', '\x23', '\x01', '\xBC', '\xAA' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<ReferenceTimeInformation>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x01', '\xAA', '\x2A', '\x0F' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<SupportedNewAlertCategory>(const benchmark::State& state)
{
    (void)state;

           //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<SupportedUnreadAlertCategory>(const benchmark::State& state)
{
    (void)state;

           //                             RRRRRRIH       SVXMCNEA
    constexpr char flags[] = { C(0b00000011), C(0b11111111) };
    constexpr char data[] = { flags[1], flags[0] };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<TextString>(const benchmark::State& state)
{
    size_t size = static_cast<size_t>(state.range(0));
    std::string data;
    data.reserve(size);
    for (size_t i = 0; i < size; ++i) {
        data.push_back((size & 0x3F) + 0x3F);
    }

    return data;
}

template<>
std::string DataGenerator::make_data<TimeAccuracy>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x2A' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<TimeSource>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x01' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<TimeZone>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x38' };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<UnreadAlertStatus>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = {
        '\x02', // categoryID
        '\x2A'  // unreadCount
    };

    return std::string(data, sizeof(data));
}

template<>
std::string DataGenerator::make_data<UserIndex>(const benchmark::State& state)
{
    (void)state;

    constexpr char data[] = { '\x2A' };

    return std::string(data, sizeof(data));
}
