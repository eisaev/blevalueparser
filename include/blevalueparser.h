#pragma once

#include <cstddef>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <locale>


namespace bvp
{

// Assigned_Numbers_Released-2022-12-20.pdf
// 3.8.1 Characteristics by Name
// 3.8.2 Characteristics by UUID
enum class CharacteristicType
{
    DeviceName = 0x2A00,
    Appearance = 0x2A01,
    PeripheralPrivacyFlag = 0x2A02,
    ReconnectionAddress = 0x2A03,
    PeripheralPreferredConnectionParameters = 0x2A04,
    ServiceChanged = 0x2A05,
    AlertLevel = 0x2A06,
    TxPowerLevel = 0x2A07,
    DateTime = 0x2A08,
    DayOfWeek = 0x2A09,
    DayDateTime = 0x2A0A,
    ExactTime256 = 0x2A0C,
    DSTOffset = 0x2A0D,
    TimeZone = 0x2A0E,
    LocalTimeInformation = 0x2A0F,
    TimewithDST = 0x2A11,
    TimeAccuracy = 0x2A12,
    TimeSource = 0x2A13,
    ReferenceTimeInformation = 0x2A14,
    TimeUpdateControlPoint = 0x2A16,
    TimeUpdateState = 0x2A17,
    GlucoseMeasurement = 0x2A18,
    BatteryLevel = 0x2A19,
    TemperatureMeasurement = 0x2A1C,
    TemperatureType = 0x2A1D,
    IntermediateTemperature = 0x2A1E,
    MeasurementInterval = 0x2A21,
    BootKeyboardInputReport = 0x2A22,
    SystemID = 0x2A23,
    ModelNumberString = 0x2A24,
    SerialNumberString = 0x2A25,
    FirmwareRevisionString = 0x2A26,
    HardwareRevisionString = 0x2A27,
    SoftwareRevisionString = 0x2A28,
    ManufacturerNameString = 0x2A29,
    IEEE1107320601RegulatoryCertificationDataList = 0x2A2A,
    CurrentTime = 0x2A2B,
    MagneticDeclination = 0x2A2C,
    ScanRefresh = 0x2A31,
    BootKeyboardOutputReport = 0x2A32,
    BootMouseInputReport = 0x2A33,
    GlucoseMeasurementContext = 0x2A34,
    BloodPressureMeasurement = 0x2A35,
    IntermediateCuffPressure = 0x2A36,
    HeartRateMeasurement = 0x2A37,
    BodySensorLocation = 0x2A38,
    HeartRateControlPoint = 0x2A39,
    AlertStatus = 0x2A3F,
    RingerControlPoint = 0x2A40,
    RingerSetting = 0x2A41,
    AlertCategoryIDBitMask = 0x2A42,
    AlertCategoryID = 0x2A43,
    AlertNotificationControlPoint = 0x2A44,
    UnreadAlertStatus = 0x2A45,
    NewAlert = 0x2A46,
    SupportedNewAlertCategory = 0x2A47,
    SupportedUnreadAlertCategory = 0x2A48,
    BloodPressureFeature = 0x2A49,
    HIDInformation = 0x2A4A,
    ReportMap = 0x2A4B,
    HIDControlPoint = 0x2A4C,
    Report = 0x2A4D,
    ProtocolMode = 0x2A4E,
    ScanIntervalWindow = 0x2A4F,
    PnPID = 0x2A50,
    GlucoseFeature = 0x2A51,
    RecordAccessControlPoint = 0x2A52,
    RSCMeasurement = 0x2A53,
    RSCFeature = 0x2A54,
    SCControlPoint = 0x2A55,
    Aggregate = 0x2A5A,
    CSCMeasurement = 0x2A5B,
    CSCFeature = 0x2A5C,
    SensorLocation = 0x2A5D,
    PLXSpotCheckMeasurement = 0x2A5E,
    PLXContinuousMeasurement = 0x2A5F,
    PLX = 0x2A60,
    CyclingPowerMeasurement = 0x2A63,
    CyclingPowerVector = 0x2A64,
    CyclingPowerFeature = 0x2A65,
    CyclingPowerControlPoint = 0x2A66,
    LocationandSpeed = 0x2A67,
    Navigation = 0x2A68,
    PositionQuality = 0x2A69,
    LNFeature = 0x2A6A,
    LNControlPoint = 0x2A6B,
    Elevation = 0x2A6C,
    Pressure = 0x2A6D,
    Temperature = 0x2A6E,
    Humidity = 0x2A6F,
    TrueWindSpeed = 0x2A70,
    TrueWindDirection = 0x2A71,
    ApparentWindSpeed = 0x2A72,
    ApparentWindDirection = 0x2A73,
    GustFactor = 0x2A74,
    PollenConcentration = 0x2A75,
    UVIndex = 0x2A76,
    Irradiance = 0x2A77,
    Rainfall = 0x2A78,
    WindChill = 0x2A79,
    HeatIndex = 0x2A7A,
    DewPoint = 0x2A7B,
    DescriptorValueChanged = 0x2A7D,
    AerobicHeartRateLowerLimit = 0x2A7E,
    AerobicThreshold = 0x2A7F,
    Age = 0x2A80,
    AnaerobicHeartRateLowerLimit = 0x2A81,
    AnaerobicHeartRateUpperLimit = 0x2A82,
    AnaerobicThreshold = 0x2A83,
    AerobicHeartRateUpperLimit = 0x2A84,
    DateofBirth = 0x2A85,
    DateofThresholdAssessment = 0x2A86,
    EmailAddress = 0x2A87,
    FatBurnHeartRateLowerLimit = 0x2A88,
    FatBurnHeartRateUpperLimit = 0x2A89,
    FirstName = 0x2A8A,
    FiveZoneHeartRateLimits = 0x2A8B,
    Gender = 0x2A8C,
    HeartRateMax = 0x2A8D,
    Height = 0x2A8E,
    HipCircumference = 0x2A8F,
    LastName = 0x2A90,
    MaximumRecommendedHeartRate = 0x2A91,
    RestingHeartRate = 0x2A92,
    SportTypeforAerobicandAnaerobicThresholds = 0x2A93,
    ThreeZoneHeartRateLimits = 0x2A94,
    TwoZoneHeartRateLimits = 0x2A95,
    VO2Max = 0x2A96,
    WaistCircumference = 0x2A97,
    Weight = 0x2A98,
    DatabaseChangeIncrement = 0x2A99,
    UserIndex = 0x2A9A,
    BodyCompositionFeature = 0x2A9B,
    BodyCompositionMeasurement = 0x2A9C,
    WeightMeasurement = 0x2A9D,
    WeightScaleFeature = 0x2A9E,
    UserControlPoint = 0x2A9F,
    MagneticFluxDensity2D = 0x2AA0,
    MagneticFluxDensity3D = 0x2AA1,
    Language = 0x2AA2,
    BarometricPressureTrend = 0x2AA3,
    BondManagementControlPoint = 0x2AA4,
    BondManagementFeature = 0x2AA5,
    CentralAddressResolution = 0x2AA6,
    CGMMeasurement = 0x2AA7,
    CGMFeature = 0x2AA8,
    CGMStatus = 0x2AA9,
    CGMSessionStartTime = 0x2AAA,
    CGMSessionRunTime = 0x2AAB,
    CGMSpecificOpsControlPoint = 0x2AAC,
    IndoorPositioningConfiguration = 0x2AAD,
    Latitude = 0x2AAE,
    Longitude = 0x2AAF,
    LocalNorthCoordinate = 0x2AB0,
    LocalEastCoordinate = 0x2AB1,
    FloorNumber = 0x2AB2,
    Altitude = 0x2AB3,
    Uncertainty = 0x2AB4,
    LocationName = 0x2AB5,
    URI = 0x2AB6,
    HTTPHeaders = 0x2AB7,
    HTTPStatusCode = 0x2AB8,
    HTTPEntityBody = 0x2AB9,
    HTTPControlPoint = 0x2ABA,
    HTTPSSecurity = 0x2ABB,
    TDSControlPoint = 0x2ABC,
    OTSFeature = 0x2ABD,
    ObjectName = 0x2ABE,
    ObjectType = 0x2ABF,
    ObjectSize = 0x2AC0,
    ObjectFirstCreated = 0x2AC1,
    ObjectLastModified = 0x2AC2,
    ObjectID = 0x2AC3,
    ObjectProperties = 0x2AC4,
    ObjectActionControlPoint = 0x2AC5,
    ObjectListControlPoint = 0x2AC6,
    ObjectListFilter = 0x2AC7,
    ObjectChanged = 0x2AC8,
    ResolvablePrivateAddressOnly = 0x2AC9,
    FitnessMachineFeature = 0x2ACC,
    TreadmillData = 0x2ACD,
    CrossTrainerData = 0x2ACE,
    StepClimberData = 0x2ACF,
    StairClimberData = 0x2AD0,
    RowerData = 0x2AD1,
    IndoorBikeData = 0x2AD2,
    TrainingStatus = 0x2AD3,
    SupportedSpeedRange = 0x2AD4,
    SupportedInclinationRange = 0x2AD5,
    SupportedResistanceLevelRange = 0x2AD6,
    SupportedHeartRateRange = 0x2AD7,
    SupportedPowerRange = 0x2AD8,
    FitnessMachineControlPoint = 0x2AD9,
    FitnessMachineStatus = 0x2ADA,
    MeshProvisioningDataIn = 0x2ADB,
    MeshProvisioningDataOut = 0x2ADC,
    MeshProxyDataIn = 0x2ADD,
    MeshProxyDataOut = 0x2ADE,
    AverageCurrent = 0x2AE0,
    AverageVoltage = 0x2AE1,
    Boolean = 0x2AE2,
    ChromaticDistancefromPlanckian = 0x2AE3,
    ChromaticityCoordinates = 0x2AE4,
    ChromaticityinCCTandDuvValues = 0x2AE5,
    ChromaticityTolerance = 0x2AE6,
    CIE13Dot31995ColorRenderingIndex = 0x2AE7,
    Coefficient = 0x2AE8,
    CorrelatedColorTemperature = 0x2AE9,
    Count16 = 0x2AEA,
    Count24 = 0x2AEB,
    CountryCode = 0x2AEC,
    DateUTC = 0x2AED,
    ElectricCurrent = 0x2AEE,
    ElectricCurrentRange = 0x2AEF,
    ElectricCurrentSpecification = 0x2AF0,
    ElectricCurrentStatistics = 0x2AF1,
    Energy = 0x2AF2,
    EnergyinaPeriodofDay = 0x2AF3,
    EventStatistics = 0x2AF4,
    FixedString16 = 0x2AF5,
    FixedString24 = 0x2AF6,
    FixedString36 = 0x2AF7,
    FixedString8 = 0x2AF8,
    GenericLevel = 0x2AF9,
    GlobalTradeItemNumber = 0x2AFA,
    Illuminance = 0x2AFB,
    LuminousEfficacy = 0x2AFC,
    LuminousEnergy = 0x2AFD,
    LuminousExposure = 0x2AFE,
    LuminousFlux = 0x2AFF,
    LuminousFluxRange = 0x2B00,
    LuminousIntensity = 0x2B01,
    MassFlow = 0x2B02,
    PerceivedLightness = 0x2B03,
    Percentage8 = 0x2B04,
    Power = 0x2B05,
    PowerSpecification = 0x2B06,
    RelativeRuntimeinaCurrentRange = 0x2B07,
    RelativeRuntimeinaGenericLevelRange = 0x2B08,
    RelativeValueinaVoltageRange = 0x2B09,
    RelativeValueinanIlluminanceRange = 0x2B0A,
    RelativeValueinaPeriodofDay = 0x2B0B,
    RelativeValueinaTemperatureRange = 0x2B0C,
    Temperature8 = 0x2B0D,
    Temperature8inaPeriodofDay = 0x2B0E,
    Temperature8Statistics = 0x2B0F,
    TemperatureRange = 0x2B10,
    TemperatureStatistics = 0x2B11,
    TimeDecihour8 = 0x2B12,
    TimeExponential8 = 0x2B13,
    TimeHour24 = 0x2B14,
    TimeMillisecond24 = 0x2B15,
    TimeSecond16 = 0x2B16,
    TimeSecond8 = 0x2B17,
    Voltage = 0x2B18,
    VoltageSpecification = 0x2B19,
    VoltageStatistics = 0x2B1A,
    VolumeFlow = 0x2B1B,
    ChromaticityCoordinate = 0x2B1C,
    RCFeature = 0x2B1D,
    RCSettings = 0x2B1E,
    ReconnectionConfigurationControlPoint = 0x2B1F,
    IDDStatusChanged = 0x2B20,
    IDDStatus = 0x2B21,
    IDDAnnunciationStatus = 0x2B22,
    IDD = 0x2B23,
    IDDStatusReaderControlPoint = 0x2B24,
    IDDCommandControlPoint = 0x2B25,
    IDDCommandData = 0x2B26,
    IDDRecordAccessControlPoint = 0x2B27,
    IDDHistoryData = 0x2B28,
    ClientSupported = 0x2B29,
    DatabaseHash = 0x2B2A,
    BSSControlPoint = 0x2B2B,
    BSSResponse = 0x2B2C,
    EmergencyID = 0x2B2D,
    EmergencyText = 0x2B2E,
    ACSStatus = 0x2B2F,
    ACSDataIn = 0x2B30,
    ACSDataOutNotify = 0x2B31,
    ACSDataOutIndicate = 0x2B32,
    ACSControlPoint = 0x2B33,
    EnhancedBloodPressureMeasurement = 0x2B34,
    EnhancedIntermediateCuffPressure = 0x2B35,
    BloodPressureRecord = 0x2B36,
    RegisteredUser = 0x2B37,
    BREDRHandoverData = 0x2B38,
    BluetoothSIGData = 0x2B39,
    ServerSupported = 0x2B3A,
    PhysicalActivityMonitor = 0x2B3B,
    GeneralActivityInstantaneousData = 0x2B3C,
    GeneralActivitySummaryData = 0x2B3D,
    CardioRespiratoryActivityInstantaneousData = 0x2B3E,
    CardioRespiratoryActivitySummaryData = 0x2B3F,
    StepCounterActivitySummaryData = 0x2B40,
    SleepActivityInstantaneousData = 0x2B41,
    SleepActivitySummaryData = 0x2B42,
    PhysicalActivityMonitorControlPoint = 0x2B43,
    ActivityCurrentSession = 0x2B44,
    PhysicalActivitySessionDescriptor = 0x2B45,
    PreferredUnits = 0x2B46,
    HighResolutionHeight = 0x2B47,
    MiddleName = 0x2B48,
    StrideLength = 0x2B49,
    Handedness = 0x2B4A,
    DeviceWearingPosition = 0x2B4B,
    FourZoneHeartRateLimits = 0x2B4C,
    HighIntensityExerciseThreshold = 0x2B4D,
    ActivityGoal = 0x2B4E,
    SedentaryIntervalNotification = 0x2B4F,
    CaloricIntake = 0x2B50,
    TMAPRole = 0x2B51,
    AudioInputState = 0x2B77,
    GainSettingsAttribute = 0x2B78,
    AudioInputType = 0x2B79,
    AudioInputStatus = 0x2B7A,
    AudioInputControlPoint = 0x2B7B,
    AudioInputDescription = 0x2B7C,
    VolumeState = 0x2B7D,
    VolumeControlPoint = 0x2B7E,
    VolumeFlags = 0x2B7F,
    VolumeOffsetState = 0x2B80,
    AudioLocation = 0x2B81,
    VolumeOffsetControlPoint = 0x2B82,
    AudioOutputDescription = 0x2B83,
    SetIdentityResolvingKey = 0x2B84,
    CoordinatedSetSize = 0x2B85,
    SetMemberLock = 0x2B86,
    SetMemberRank = 0x2B87,
    ApparentEnergy32 = 0x2B89,
    ApparentPower = 0x2B8A,
    CO2Concentration = 0x2B8C,
    CosineoftheAngle = 0x2B8D,
    DeviceTimeFeature = 0x2B8E,
    DeviceTimeParameters = 0x2B8F,
    DeviceTime = 0x2B90,
    DeviceTimeControlPoint = 0x2B91,
    TimeChangeLogData = 0x2B92,
    MediaPlayerName = 0x2B93,
    MediaPlayerIconObjectID = 0x2B94,
    MediaPlayerIconURL = 0x2B95,
    TrackChanged = 0x2B96,
    TrackTitle = 0x2B97,
    TrackDuration = 0x2B98,
    TrackPosition = 0x2B99,
    PlaybackSpeed = 0x2B9A,
    SeekingSpeed = 0x2B9B,
    CurrentTrackSegmentsObjectID = 0x2B9C,
    CurrentTrackObjectID = 0x2B9D,
    NextTrackObjectID = 0x2B9E,
    ParentGroupObjectID = 0x2B9F,
    CurrentGroupObjectID = 0x2BA0,
    PlayingOrder = 0x2BA1,
    PlayingOrdersSupported = 0x2BA2,
    MediaState = 0x2BA3,
    MediaControlPoint = 0x2BA4,
    MediaControlPointOpcodesSupported = 0x2BA5,
    SearchResultsObjectID = 0x2BA6,
    SearchControlPoint = 0x2BA7,
    Energy32 = 0x2BA8,
    MediaPlayerIconObjectType = 0x2BA9,
    TrackSegmentsObjectType = 0x2BAA,
    TrackObjectType = 0x2BAB,
    GroupObjectType = 0x2BAC,
    ConstantToneExtensionEnable = 0x2BAD,
    AdvertisingConstantToneExtensionMinimumLength = 0x2BAE,
    AdvertisingConstantToneExtensionMinimumTransmitCount = 0x2BAF,
    AdvertisingConstantToneExtensionTransmitDuration = 0x2BB0,
    AdvertisingConstantToneExtensionInterval = 0x2BB1,
    AdvertisingConstantToneExtensionPHY = 0x2BB2,
    BearerProviderName = 0x2BB3,
    BearerUCI = 0x2BB4,
    BearerTechnology = 0x2BB5,
    BearerURISchemesSupportedList = 0x2BB6,
    BearerSignalStrength = 0x2BB7,
    BearerSignalStrengthReportingInterval = 0x2BB8,
    BearerListCurrentCalls = 0x2BB9,
    ContentControlID = 0x2BBA,
    StatusFlags = 0x2BBB,
    IncomingCallTargetBearerURI = 0x2BBC,
    CallState = 0x2BBD,
    CallControlPoint = 0x2BBE,
    CallControlPointOptionalOpcodes = 0x2BBF,
    TerminationReason = 0x2BC0,
    IncomingCall = 0x2BC1,
    CallFriendlyName = 0x2BC2,
    Mute = 0x2BC3,
    SinkASE = 0x2BC4,
    SourceASE = 0x2BC5,
    ASEControlPoint = 0x2BC6,
    BroadcastAudioScanControlPoint = 0x2BC7,
    BroadcastReceiveState = 0x2BC8,
    SinkPAC = 0x2BC9,
    SinkAudioLocations = 0x2BCA,
    SourcePAC = 0x2BCB,
    SourceAudioLocations = 0x2BCC,
    AvailableAudioContexts = 0x2BCD,
    SupportedAudioContexts = 0x2BCE,
    AmmoniaConcentration = 0x2BCF,
    CarbonMonoxideConcentration = 0x2BD0,
    MethaneConcentration = 0x2BD1,
    NitrogenDioxideConcentration = 0x2BD2,
    NonMethaneVolatileOrganicCompoundsConcentration = 0x2BD3,
    OzoneConcentration = 0x2BD4,
    ParticulateMatterPM1Concentration = 0x2BD5,
    ParticulateMatterPM2Dot5Concentration = 0x2BD6,
    ParticulateMatterPM10Concentration = 0x2BD7,
    SulfurDioxideConcentration = 0x2BD8,
    SulfurHexafluorideConcentration = 0x2BD9,
    HearingAid = 0x2BDA,
    HearingAidPresetControlPoint = 0x2BDB,
    ActivePresetIndex = 0x2BDC,
    FixedString64 = 0x2BDE,
    HighTemperature = 0x2BDF,
    HighVoltage = 0x2BE0,
    LightDistribution = 0x2BE1,
    LightOutput = 0x2BE2,
    LightSourceType = 0x2BE3,
    Noise = 0x2BE4,
    RelativeRuntimeinaCorrelatedColorTemperatureRange = 0x2BE5,
    TimeSecond32 = 0x2BE6,
    VOCConcentration = 0x2BE7,
    VoltageFrequency = 0x2BE8,
    BatteryCriticalStatus = 0x2BE9,
    BatteryHealthStatus = 0x2BEA,
    BatteryHealthInformation = 0x2BEB,
    BatteryInformation = 0x2BEC,
    BatteryLevelStatus = 0x2BED,
    BatteryTimeStatus = 0x2BEE,
    EstimatedServiceDate = 0x2BEF,
    BatteryEnergyStatus = 0x2BF0
};


class BaseValue
{
public:
    virtual ~BaseValue() {}

    struct Configuration
    {
        std::string stringPrefix = "";
        std::string stringSuffix = "";
        std::string hexPrefix = "0x ";
        std::string hexSeparator = ":";
    };

    bool isValid() const
    {
        return m_isValid;
    }

    std::string toString() const
    {
        if (!m_isValid)
        {
            return "<Invalid>";
        }

        std::stringstream ss;
        ss << m_configuration.stringPrefix;
        toStringStream(ss);
        ss << m_configuration.stringSuffix;
        return ss.str();
    }

protected:
    explicit BaseValue() {}

    bool m_isValid = false;
    Configuration m_configuration;

    // For testing protected Parser class
    friend class InternalParserTest;
    friend class InternalParserTest_UInt8_Test;
    friend class InternalParserTest_UInt16_Test;
    friend class InternalParserTest_UInt32_Test;
    friend class InternalParserTest_UInt64_Test;
    friend class InternalParserTest_Int8_Test;
    friend class InternalParserTest_Int16_Test;
    friend class InternalParserTest_Int32_Test;
    friend class InternalParserTest_Int64_Test;
    friend class InternalParserTest_String_Test;

    class Parser
    {
    public:
        explicit Parser(const char* data, size_t size) :
            m_data{data},
            m_size{size},
            m_offset{0},
            m_outOfData{false}
        {}

        size_t offset() const
        {
            return m_offset;
        }

        bool atEnd() const
        {
            return m_offset >= m_size;
        }

        bool outOfData() const
        {
            return m_outOfData;
        }

        std::string parseString()
        {
            std::string result{m_data, m_size};
            m_offset += m_size;
            return result;
        }

        uint8_t parseUInt8()
        {
            return parseInt<uint8_t>();
        }

        uint16_t parseUInt16()
        {
            return parseInt<uint16_t>();
        }

        uint32_t parseUInt32()
        {
            return parseInt<uint32_t>();
        }

        uint64_t parseUInt64()
        {
            return parseInt<uint64_t>();
        }

        int8_t parseInt8()
        {
            return parseInt<int8_t>();
        }

        int16_t parseInt16()
        {
            return parseInt<int16_t>();
        }

        int32_t parseInt32()
        {
            return parseInt<int32_t>();
        }

        int64_t parseInt64()
        {
            return parseInt<int64_t>();
        }

    private:
        const char *m_data;
        size_t m_size;
        size_t m_offset;
        bool m_outOfData;

        template <typename T>
        T parseInt()
        {
            uint64_t result = 0;

            constexpr size_t offsetDiff = sizeof(T);
            m_outOfData = m_offset + offsetDiff > m_size;
            if (!m_outOfData)
            {
                for (size_t i = 0; i < offsetDiff; ++i)
                {
                    uint8_t b = m_data[m_offset];
                    result += static_cast<uint64_t>(b) << 8 * i;
                    ++m_offset;
                }
            }

            return static_cast<T>(result);
        }
    };

    void create(const char *data, size_t size)
    {
        if (!checkSize(size))
        {
            return;
        }

        Parser parser{data, size};
        m_isValid = parse(parser) && !parser.outOfData();
    }

    void create(const char *data, size_t size, const Configuration &configuration)
    {
        m_configuration = configuration;
        create(data, size);
    }

    virtual bool checkSize(size_t size) = 0;
    virtual bool parse(Parser &parser) = 0;
    virtual void toStringStream(std::stringstream &ss) const = 0;
};


class TextString final : public BaseValue
{
public:
    std::string textString() const
    {
        return m_textString;
    }

private:
    friend class BLEValueParser;
    explicit TextString(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    std::string m_textString;

    virtual bool checkSize(size_t size) override
    {
        return true;
    }

    virtual bool parse(Parser &parser) override
    {
        m_textString = parser.parseString();
        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_textString;
    }
};


class HexString final : public BaseValue
{
public:
    std::string hexString() const
    {
        return m_hexString;
    }

private:
    friend class BLEValueParser;
    explicit HexString(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    std::string m_hexString;

    virtual bool checkSize(size_t size) override
    {
        return true;
    }

    virtual bool parse(Parser &parser) override
    {
        std::stringstream ss;
        ss << m_configuration.hexPrefix;
        while (!parser.atEnd())
        {
            ss << std::uppercase
               << std::setfill('0')
               << std::setw(2)
               << std::hex
               << static_cast<int>(parser.parseUInt8())
               << m_configuration.hexSeparator;
        }
        m_hexString = ss.str();
        m_hexString.pop_back();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << m_hexString;
    }
};


/*
 * Battery Service
 * BAS_V1.1.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.27 Battery Level
struct BatteryLevelStruct
{
    uint8_t batteryLevel = 0;
};

// 3.1 Battery Level
class BatteryLevel final : public BaseValue
{
public:
    BatteryLevelStruct getBtSpecObject() const
    {
        return m_batteryLevel;
    }

    uint8_t level() const
    {
        return m_batteryLevel.batteryLevel;
    }

private:
    friend class BLEValueParser;
    explicit BatteryLevel(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    BatteryLevelStruct m_batteryLevel;

    virtual bool checkSize(size_t size) override
    {
        return size == 1;
    }

    virtual bool parse(Parser &parser) override
    {
        m_batteryLevel.batteryLevel = parser.parseUInt8();
        if (m_batteryLevel.batteryLevel > 100)
        {
            return false;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << static_cast<int>(m_batteryLevel.batteryLevel) << "%";
    }
};


/*
 * Device Information Service
 * DIS_SPEC_V11r00.pdf
 */

// 3.9.1.1 Vendor ID Source Field (Table 3.2)
// GATT_Specification_Supplement_v8.pdf
// 3.169.1 Vendor ID Source field (Table 3.267)
enum class VendorIdSourceEnum
{
    Unknown     = 0,  // 0, 3–255 - Reserved for Future Use
    Bluetooth   = 1,
    USB         = 2
};

// GATT_Specification_Supplement_v8.pdf
// 3.169.1 Vendor ID Source field
struct VendorIdSourceStruct
{
    VendorIdSourceEnum vendorIdSource = VendorIdSourceEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.169 PnP ID
struct PnPIDStruct
{
    VendorIdSourceStruct vendorIdSource;
    uint16_t vendorId = 0;
    uint16_t productId = 0;
    uint16_t productVersion = 0;
};

// 3.9 PnPID
class PnPID final : public BaseValue
{
public:
    PnPIDStruct getBtSpecObject() const
    {
        return m_pnpId;
    }

    VendorIdSourceEnum vendorIdSource() const
    {
        return m_pnpId.vendorIdSource.vendorIdSource;
    }

    uint16_t vendorId() const
    {
        return m_pnpId.vendorId;
    }

    uint16_t productId() const
    {
        return m_pnpId.productId;
    }

    uint8_t majorVersion() const
    {
        return m_pnpId.productVersion >> 8;
    }

    uint8_t minorVersion() const
    {
        return m_pnpId.productVersion >> 4 & 0b1111;
    }

    uint8_t subMinorVersion() const
    {
        return m_pnpId.productVersion & 0b1111;
    }

private:
    friend class BLEValueParser;
    explicit PnPID(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    PnPIDStruct m_pnpId;

    virtual bool checkSize(size_t size) override
    {
        return size == 7;
    }

    virtual bool parse(Parser &parser) override
    {
        // 3.9.1.1 Vendor ID Source Field
        m_pnpId.vendorIdSource.vendorIdSource = VendorIdSourceEnum(parser.parseUInt8());
        switch (m_pnpId.vendorIdSource.vendorIdSource)
        {
            case VendorIdSourceEnum::Unknown:
            case VendorIdSourceEnum::Bluetooth ... VendorIdSourceEnum::USB:
                break;
            default:
                m_pnpId.vendorIdSource.vendorIdSource = VendorIdSourceEnum::Unknown;
                break;
        }
        // 3.9.1.2 Vendor ID Field
        m_pnpId.vendorId = parser.parseUInt16();
        // 3.9.1.3 Product ID Field
        m_pnpId.productId = parser.parseUInt16();

        // 3.9.1.4 Product Version Field
        // The value of the field value is 0xJJMN for version JJ.M.N
        // (JJ – major version number, M – minor version number, N – sub-minor version number)
        m_pnpId.productVersion = parser.parseUInt16();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "(";
        switch (m_pnpId.vendorIdSource.vendorIdSource)
        {
        case VendorIdSourceEnum::Unknown:
                ss << "<Unknown>";
                break;
        case VendorIdSourceEnum::Bluetooth:
                ss << "Bluetooth";
                break;
        case VendorIdSourceEnum::USB:
                ss << "USB";
                break;
        }
        ss << ") ";
        auto originalFlags = ss.flags();
        ss << "VID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_pnpId.vendorId << ", ";
        ss << "PID: 0x" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << m_pnpId.productId << ", ";
        ss.flags(originalFlags);
        ss << "Version: " << static_cast<int>(majorVersion()) << "." << static_cast<int>(minorVersion()) << "." << static_cast<int>(subMinorVersion());
    }
};


/*
 * Current Time Service
 * CTS_SPEC_V1.1.0.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.73 Day of Week (Table 3.130)
enum class DayOfWeekEnum
{
    Unknown = 0,
    Monday = 1,
    Tuesday = 2,
    Wednesday = 3,
    Thursday = 4,
    Friday = 5,
    Saturday = 6,
    Sunday = 7
};

// GATT_Specification_Supplement_v8.pdf
// 3.73 Day of Week
struct DayOfWeekStruct
{
    DayOfWeekEnum dayOfWeek = DayOfWeekEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.70 Date Time
struct DateTimeStruct
{
    uint16_t year = 0;
    uint8_t month = 0;
    uint8_t day = 0;
    uint8_t hour = 0;
    uint8_t minute = 0;
    uint8_t seconds = 0;
};

// GATT_Specification_Supplement_v8.pdf
// 3.72 Day Date Time
struct DayDateTimeStruct
{
    DateTimeStruct dateTime;
    DayOfWeekStruct dayOfWeek;
};

// GATT_Specification_Supplement_v8.pdf
// 3.90 Exact Time 256
struct ExactTime256Struct
{
    DayDateTimeStruct dayDateTime;
    uint8_t fractions256 = 0;
};

// GATT_Specification_Supplement_v8.pdf
// 3.62 Current Time
// Table 3.106: Structure of the Current Time characteristic
// Adjust Reason
constexpr uint8_t CTS_FLAG_MANUAL      = 0b00000001;
constexpr uint8_t CTS_FLAG_EXTERNAL    = 0b00000010;
constexpr uint8_t CTS_FLAG_TZ_CHANGED  = 0b00000100;
constexpr uint8_t CTS_FLAG_DST_CHANGED = 0b00001000;
constexpr uint8_t CTS_FLAG_RESERVED1   = 0b00010000;
constexpr uint8_t CTS_FLAG_RESERVED2   = 0b00100000;
constexpr uint8_t CTS_FLAG_RESERVED3   = 0b01000000;
constexpr uint8_t CTS_FLAG_RESERVED4   = 0b10000000;

// GATT_Specification_Supplement_v8.pdf
// 3.62 Current Time
struct CurrentTimeStruct
{
    ExactTime256Struct exactTime256;
    // See CTS_FLAG_*
    uint8_t adjustReason = 0;
};

// GATT_Specification_Supplement_v8.pdf
// 3.232 Time Zone (Table 3.345)
enum class TimeZoneEnum
{
    Unknown = -128,
    Minus48 = -48,
    Minus47 = -47,
    Minus46 = -46,
    Minus45 = -45,
    Minus44 = -44,
    Minus43 = -43,
    Minus42 = -42,
    Minus41 = -41,
    Minus40 = -40,
    Minus39 = -39,
    Minus38 = -38,
    Minus37 = -37,
    Minus36 = -36,
    Minus35 = -35,
    Minus34 = -34,
    Minus33 = -33,
    Minus32 = -32,
    Minus31 = -31,
    Minus30 = -30,
    Minus29 = -29,
    Minus28 = -28,
    Minus27 = -27,
    Minus26 = -26,
    Minus25 = -25,
    Minus24 = -24,
    Minus23 = -23,
    Minus22 = -22,
    Minus21 = -21,
    Minus20 = -20,
    Minus19 = -19,
    Minus18 = -18,
    Minus17 = -17,
    Minus16 = -16,
    Minus15 = -15,
    Minus14 = -14,
    Minus13 = -13,
    Minus12 = -12,
    Minus11 = -11,
    Minus10 = -10,
    Minus9 = -9,
    Minus8 = -8,
    Minus7 = -7,
    Minus6 = -6,
    Minus5 = -5,
    Minus4 = -4,
    Minus3 = -3,
    Minus2 = -2,
    Minus1 = -1,
    Plus0 = 0,
    Plus1 = 1,
    Plus2 = 2,
    Plus3 = 3,
    Plus4 = 4,
    Plus5 = 5,
    Plus6 = 6,
    Plus7 = 7,
    Plus8 = 8,
    Plus9 = 9,
    Plus10 = 10,
    Plus11 = 11,
    Plus12 = 12,
    Plus13 = 13,
    Plus14 = 14,
    Plus15 = 15,
    Plus16 = 16,
    Plus17 = 17,
    Plus18 = 18,
    Plus19 = 19,
    Plus20 = 20,
    Plus21 = 21,
    Plus22 = 22,
    Plus23 = 23,
    Plus24 = 24,
    Plus25 = 25,
    Plus26 = 26,
    Plus27 = 27,
    Plus28 = 28,
    Plus29 = 29,
    Plus30 = 30,
    Plus31 = 31,
    Plus32 = 32,
    Plus33 = 33,
    Plus34 = 34,
    Plus35 = 35,
    Plus36 = 36,
    Plus37 = 37,
    Plus38 = 38,
    Plus39 = 39,
    Plus40 = 40,
    Plus41 = 41,
    Plus42 = 42,
    Plus43 = 43,
    Plus44 = 44,
    Plus45 = 45,
    Plus46 = 46,
    Plus47 = 47,
    Plus48 = 48,
    Plus49 = 49,
    Plus50 = 50,
    Plus51 = 51,
    Plus52 = 52,
    Plus53 = 53,
    Plus54 = 54,
    Plus55 = 55,
    Plus56 = 56
};

// GATT_Specification_Supplement_v8.pdf
// 3.232 Time Zone (Table 3.345)
struct TimeZoneStruct
{
    TimeZoneEnum timeZone = TimeZoneEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.76 DST Offset (Table 3.134)
enum class DSTOffsetEnum
{
    StandardTime = 0,
    HalfAnHourDaylightTime0_5h = 2,
    DaylightTime1h = 4,
    DoubleDaylightTime2h = 8,
    Unknown = 255
};

// GATT_Specification_Supplement_v8.pdf
// 3.76 DST Offset
struct DSTOffsetStruct
{
    DSTOffsetEnum dstOffset = DSTOffsetEnum::Unknown;
};

// GATT_Specification_Supplement_v8.pdf
// 3.135 Local Time Information
struct LocalTimeInformationStruct
{
    TimeZoneStruct timeZone;
    DSTOffsetStruct dstOffset;
};

// 3.1 Current Time
class CurrentTime final : public BaseValue
{
public:
    CurrentTimeStruct getBtSpecObject() const
    {
        return m_currentTime;
    }

    uint16_t year() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.year;
    }

    uint8_t month() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.month;
    }

    uint8_t day() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.day;
    }

    uint8_t hour() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.hour;
    }

    uint8_t minute() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.minute;
    }

    uint8_t seconds() const
    {
        return m_currentTime.exactTime256.dayDateTime.dateTime.seconds;
    }

    DayOfWeekEnum dayOfWeek() const
    {
        return m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek;
    }

    uint8_t fractionsOfSeconds() const
    {
        return m_currentTime.exactTime256.fractions256;
    }

    uint16_t milliseconds() const
    {
        return m_currentTime.exactTime256.fractions256 * 1000 / 256;
    }

    bool isManuallyAdjusted() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_MANUAL) != 0;
    }

    bool isExternalReference() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_EXTERNAL) != 0;
    }

    bool isTZChanged() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_TZ_CHANGED) != 0;
    }

    bool isDSTChanged() const
    {
        return (m_currentTime.adjustReason & CTS_FLAG_DST_CHANGED) != 0;
    }

private:
    friend class BLEValueParser;
    explicit CurrentTime(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    CurrentTimeStruct m_currentTime;

    virtual bool checkSize(size_t size) override
    {
        return size == 10;
    }

    virtual bool parse(Parser &parser) override
    {
        // Exact Time 256
        m_currentTime.exactTime256.dayDateTime.dateTime.year = parser.parseUInt16();
        m_currentTime.exactTime256.dayDateTime.dateTime.month = parser.parseUInt8();
        m_currentTime.exactTime256.dayDateTime.dateTime.day = parser.parseUInt8();
        m_currentTime.exactTime256.dayDateTime.dateTime.hour = parser.parseUInt8();
        m_currentTime.exactTime256.dayDateTime.dateTime.minute = parser.parseUInt8();
        m_currentTime.exactTime256.dayDateTime.dateTime.seconds = parser.parseUInt8();
        m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek = DayOfWeekEnum(parser.parseUInt8());
        switch (m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek)
        {
        case DayOfWeekEnum::Monday ... DayOfWeekEnum::Sunday:
        case DayOfWeekEnum::Unknown:
                break;
        default:
                m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek = DayOfWeekEnum::Unknown;
                break;
        }
        m_currentTime.exactTime256.fractions256 = parser.parseUInt8();

        // 3.1.2.1 Manual Time Update
        // 3.1.2.2 External Reference Time Update
        // 3.1.2.3 Change of Time Zone
        // 3.1.2.4 Change of DST Offset
        m_currentTime.adjustReason = parser.parseUInt8();

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        switch (m_currentTime.exactTime256.dayDateTime.dayOfWeek.dayOfWeek)
        {
            case DayOfWeekEnum::Monday:
                ss << "Mon ";
                break;
            case DayOfWeekEnum::Tuesday:
                ss << "Tue ";
                break;
            case DayOfWeekEnum::Wednesday:
                ss << "Wed ";
                break;
            case DayOfWeekEnum::Thursday:
                ss << "Thu ";
                break;
            case DayOfWeekEnum::Friday:
                ss << "Fri ";
                break;
            case DayOfWeekEnum::Saturday:
                ss << "Sat ";
                break;
            case DayOfWeekEnum::Sunday:
                ss << "Sun ";
                break;
            case DayOfWeekEnum::Unknown:
                break;
        }

        ss << std::setfill('0') << std::setw(2) << static_cast<int>(day()) << ".";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(month()) << ".";
        ss << std::setfill('0') << std::setw(4) << static_cast<int>(year()) << " ";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(hour()) << ":";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(minute()) << ":";
        ss << std::setfill('0') << std::setw(2) << static_cast<int>(seconds()) << ".";
        ss << std::setfill('0') << std::setw(3) << static_cast<int>(milliseconds()) << " ";
        ss << "(adjust reason:";
        if (isManuallyAdjusted())
        {
            ss << " ManuallyAdjusted";
        }
        if (isExternalReference())
        {
            ss << " ExternalReference";
        }
        if (isTZChanged())
        {
            ss << " TZChanged";
        }
        if (isDSTChanged())
        {
            ss << " DSTChanged";
        }
        ss << " )";
    }
};

// 3.2 Local Time Information
class LocalTimeInformation final : public BaseValue
{
public:
    LocalTimeInformationStruct getBtSpecObject() const
    {
        return m_localTimeInformation;
    }

    TimeZoneEnum timeZone() const
    {
        return m_localTimeInformation.timeZone.timeZone;
    }

    DSTOffsetEnum dstOffset() const
    {
        return m_localTimeInformation.dstOffset.dstOffset;
    }

private:
    friend class BLEValueParser;
    explicit LocalTimeInformation(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    LocalTimeInformationStruct m_localTimeInformation;

    virtual bool checkSize(size_t size) override
    {
        return size == 2;
    }

    virtual bool parse(Parser &parser) override
    {
        m_localTimeInformation.timeZone.timeZone = TimeZoneEnum(parser.parseInt8());
        switch (m_localTimeInformation.timeZone.timeZone)
        {
            case TimeZoneEnum::Minus48 ... TimeZoneEnum::Plus56:
            case TimeZoneEnum::Unknown:
                break;
            default:
                m_localTimeInformation.timeZone.timeZone = TimeZoneEnum::Unknown;
                break;
        }

        m_localTimeInformation.dstOffset.dstOffset = DSTOffsetEnum(parser.parseUInt8());
        switch (m_localTimeInformation.dstOffset.dstOffset)
        {
            case DSTOffsetEnum::StandardTime:
            case DSTOffsetEnum::HalfAnHourDaylightTime0_5h:
            case DSTOffsetEnum::DaylightTime1h:
            case DSTOffsetEnum::DoubleDaylightTime2h:
            case DSTOffsetEnum::Unknown:
                break;
            default:
                m_localTimeInformation.dstOffset.dstOffset = DSTOffsetEnum::Unknown;
                break;
        }

        return true;
    }

    virtual void toStringStream(std::stringstream &ss) const override
    {
        ss << "TZ: ";
        if (TimeZoneEnum::Unknown == m_localTimeInformation.timeZone.timeZone)
        {
            ss << "<Unknown>";
        }
        else
        {
            ss << static_cast<int>(m_localTimeInformation.timeZone.timeZone);
        }

        ss << ", DST: ";
        switch (m_localTimeInformation.dstOffset.dstOffset)
        {
            case DSTOffsetEnum::StandardTime:
                ss << "Standard Time";
                break;
            case DSTOffsetEnum::HalfAnHourDaylightTime0_5h:
                ss << "Half an Hour Daylight Time (+0.5h)";
                break;
            case DSTOffsetEnum::DaylightTime1h:
                ss << "Daylight Time (+1h)";
                break;
            case DSTOffsetEnum::DoubleDaylightTime2h:
                ss << "Double Daylight Time (+2h)";
                break;
            case DSTOffsetEnum::Unknown:
                ss << "<Unknown>";
                break;
        }
    }
};


/*
 * Heart Rate Service
 * HRS_SPEC_V10.pdf
 */

// GATT_Specification_Supplement_v8.pdf
// 3.35.1 Body Sensor Location field (Table 3.59)
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

// GATT_Specification_Supplement_v8.pdf
// 3.113 Heart Rate Measurement
struct HeartRateMeasurementStruct
{
    uint8_t flags = 0;
    uint16_t heartRate = 0;
    uint16_t energyExpended = 0;
    std::vector<uint16_t> rrIntervals;
};

// GATT_Specification_Supplement_v8.pdf
// 3.113.1 Flags field
constexpr uint8_t HRS_FLAG_VALUE_FORMAT    = 0b00000001;
constexpr uint8_t HRS_FLAG_CONTACT_STATUS  = 0b00000010;
constexpr uint8_t HRS_FLAG_CONTACT_SUPPORT = 0b00000100;
constexpr uint8_t HRS_FLAG_ENERGY_EXPENDED = 0b00001000;
constexpr uint8_t HRS_FLAG_RR_INTERVALS    = 0b00010000;
constexpr uint8_t HRS_FLAG_RESERVER1       = 0b00100000;
constexpr uint8_t HRS_FLAG_RESERVER2       = 0b01000000;
constexpr uint8_t HRS_FLAG_RESERVER3       = 0b10000000;

// 3.1 Heart Rate Measurement
class HeartRateMeasurement final : public BaseValue
{
public:
    HeartRateMeasurementStruct getBtSpecObject() const
    {
        return m_heartRateMeasurement;
    }

    bool isContactSupported() const
    {
        return (m_heartRateMeasurement.flags & HRS_FLAG_CONTACT_SUPPORT) != 0;
    }

    bool isContacted() const
    {
        return (m_heartRateMeasurement.flags & HRS_FLAG_CONTACT_STATUS) != 0;
    }

    uint16_t heartRate() const
    {
        return m_heartRateMeasurement.heartRate;
    }

    bool hasEnergyExpended() const
    {
        return (m_heartRateMeasurement.flags & HRS_FLAG_ENERGY_EXPENDED) != 0;
    }

    uint16_t energyExpended() const
    {
        return m_heartRateMeasurement.energyExpended;
    }

    std::vector<uint16_t> rrIntervals() const
    {
        std::vector<uint16_t> result;
        result.reserve(m_heartRateMeasurement.rrIntervals.size());
        // GATT_Specification_Supplement_v8.pdf
        // 3.113.2 RR-Interval field
        // Each RR-Interval value is represented by a uint16 with 1/1024 second as the unit.
        for (auto rrInterval : m_heartRateMeasurement.rrIntervals)
        {
            result.push_back(rrInterval * 1000 / 1024);
        }
        return result;
    }

private:
    friend class BLEValueParser;
    explicit HeartRateMeasurement(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, configuration);
    }

    HeartRateMeasurementStruct m_heartRateMeasurement;

    virtual bool checkSize(size_t size) override
    {
        // Minimal packet must contain flags(uint8_t)+heartRate(uint8_t)
        return size > 1 && size < 21;
    }

    virtual bool parse(Parser &parser) override
    {
        // 3.1.1.1 Flags Field
        m_heartRateMeasurement.flags = parser.parseUInt8();

        // 3.1.1.2 Heart Rate Measurement Value Field
        if (isWideFormat())
        {
            m_heartRateMeasurement.heartRate = parser.parseUInt16();
        }
        else
        {
            m_heartRateMeasurement.heartRate = parser.parseUInt8();
        }

        // 3.1.1.3 Energy Expended Field
        if (hasEnergyExpended())
        {
            m_heartRateMeasurement.energyExpended = parser.parseUInt16();
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
            m_heartRateMeasurement.rrIntervals.reserve(maxRRCount);

            for (uint8_t i = 0; i < maxRRCount && !parser.atEnd(); ++i)
            {
                m_heartRateMeasurement.rrIntervals.push_back(parser.parseUInt16());
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

        ss << "HR: " << m_heartRateMeasurement.heartRate << "bpm";

        if (hasEnergyExpended())
        {
            ss << ", EE: " << m_heartRateMeasurement.energyExpended << "kJ";
        }

        if (!m_heartRateMeasurement.rrIntervals.empty())
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
        return (m_heartRateMeasurement.flags & HRS_FLAG_VALUE_FORMAT) != 0;
    }

    bool hasRRIntervals() const
    {
        return (m_heartRateMeasurement.flags & HRS_FLAG_RR_INTERVALS) != 0;
    }
};

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
    explicit BodySensorLocation(const char *data, size_t size, const Configuration &configuration)
    {
        create(data, size, m_configuration);
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
            case BodySensorLocationEnum::Other ... BodySensorLocationEnum::Foot:
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


class BLEValueParser
{
public:
    explicit BLEValueParser() {}

    void setStringPrefix(const std::string &prefix)
    {
        m_configuration.stringPrefix = prefix;
    }

    void setStringSuffix(const std::string &suffix)
    {
        m_configuration.stringSuffix = suffix;
    }

    void setHexPrefix(const std::string &suffix)
    {
        m_configuration.hexPrefix = suffix;
    }

    void setHexSeparator(const std::string &separator)
    {
        m_configuration.hexSeparator = separator;
    }

    template <class T>
    std::unique_ptr<T> make_value(const char *data, size_t size) const
    {
        return std::unique_ptr<T>(new T(data, size, m_configuration));
    }

    std::unique_ptr<BaseValue> make_value(CharacteristicType characteristicType, const char *data, size_t size) const
    {
        switch (characteristicType)
        {
            // Device Information Service (DIS_SPEC_V11r00.pdf)
            // 3.1 Manufacturer Name String
            case CharacteristicType::ManufacturerNameString:
                return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
            // 3.2 Model Number String
            case CharacteristicType::ModelNumberString:
                return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
            // 3.3 Serial Number String
            case CharacteristicType::SerialNumberString:
                return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
            // 3.4 Hardware Revision String
            case CharacteristicType::HardwareRevisionString:
                return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
            // 3.5 Firmware Revision String
            case CharacteristicType::FirmwareRevisionString:
                return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
            // 3.6 Software Revision String
            case CharacteristicType::SoftwareRevisionString:
                return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
            // 3.7 System ID
            case CharacteristicType::SystemID:
                return std::unique_ptr<HexString>(new HexString(data, size, m_configuration));
            // 3.8 IEEE 11073-20601 Regulatory Certification Data List
            case CharacteristicType::IEEE1107320601RegulatoryCertificationDataList:
                // TODO:
                break;
            // 3.9 PnPID
            case CharacteristicType::PnPID:
                return std::unique_ptr<PnPID>(new PnPID(data, size, m_configuration));

            // Current Time Service (CTS_SPEC_V1.1.0.pdf)
            // 3.1 Current Time
            case CharacteristicType::CurrentTime:
                return std::unique_ptr<CurrentTime>(new CurrentTime(data, size, m_configuration));
            // 3.2 Local Time Information
            case CharacteristicType::LocalTimeInformation:
                return std::unique_ptr<LocalTimeInformation>(new LocalTimeInformation(data, size, m_configuration));
            // 3.3 Reference Time Information
            case CharacteristicType::ReferenceTimeInformation:
                // TODO:
                break;

            // Battery Service (BAS_V1.1.pdf)
            // 3.1 Battery Level
            case CharacteristicType::BatteryLevel:
                return std::unique_ptr<BatteryLevel>(new BatteryLevel(data, size, m_configuration));
            // 3.2 Battery Level Status
            case CharacteristicType::BatteryLevelStatus:
                // TODO:
                break;
            // 3.3 Estimated Service Date
            case CharacteristicType::EstimatedServiceDate:
                // TODO:
                break;
            // 3.4 Battery Critical Status
            case CharacteristicType::BatteryCriticalStatus:
                // TODO:
                break;
            // 3.5 Battery Energy Status
            case CharacteristicType::BatteryEnergyStatus:
                // TODO:
                break;
            // 3.6 Battery Time Status
            case CharacteristicType::BatteryTimeStatus:
                // TODO:
                break;
            // 3.7 Battery Health Status
            case CharacteristicType::BatteryHealthStatus:
                // TODO:
                break;
            // 3.8 Battery Health Information
            case CharacteristicType::BatteryHealthInformation:
                // TODO:
                break;
            // 3.9 Battery Information
            case CharacteristicType::BatteryInformation:
                // TODO:
                break;
            // 3.10 Manufacturer Name String
            // Implemented for Device Information Service (see ManufacturerNameString)
            // 3.11 Model Number String
            // Implemented for Device Information Service (ModelNumberString)
            // 3.12 Serial Number String
            // Implemented for Device Information Service (SerialNumberString)

            // Heart Rate Service (HRS_SPEC_V10.pdf)
            // 3.1 Heart Rate Measurement
            case CharacteristicType::HeartRateMeasurement:
                return std::unique_ptr<HeartRateMeasurement>(new HeartRateMeasurement(data, size, m_configuration));
            // 3.2 Body Sensor Location
            case CharacteristicType::BodySensorLocation:
                return std::unique_ptr<BodySensorLocation>(new BodySensorLocation(data, size, m_configuration));
            // 3.3 Heart Rate Control Point
            case CharacteristicType::HeartRateControlPoint:
                // TODO:
                break;

            // Other
            case CharacteristicType::DeviceName:
            case CharacteristicType::Appearance:
            case CharacteristicType::PeripheralPrivacyFlag:
            case CharacteristicType::ReconnectionAddress:
            case CharacteristicType::PeripheralPreferredConnectionParameters:
            case CharacteristicType::ServiceChanged:
            case CharacteristicType::AlertLevel:
            case CharacteristicType::TxPowerLevel:
            case CharacteristicType::DateTime:
            case CharacteristicType::DayOfWeek:
            case CharacteristicType::DayDateTime:
            case CharacteristicType::ExactTime256:
            case CharacteristicType::DSTOffset:
            case CharacteristicType::TimeZone:
            case CharacteristicType::TimewithDST:
            case CharacteristicType::TimeAccuracy:
            case CharacteristicType::TimeSource:
            case CharacteristicType::TimeUpdateControlPoint:
            case CharacteristicType::TimeUpdateState:
            case CharacteristicType::GlucoseMeasurement:
            case CharacteristicType::TemperatureMeasurement:
            case CharacteristicType::TemperatureType:
            case CharacteristicType::IntermediateTemperature:
            case CharacteristicType::MeasurementInterval:
            case CharacteristicType::BootKeyboardInputReport:
            case CharacteristicType::MagneticDeclination:
            case CharacteristicType::ScanRefresh:
            case CharacteristicType::BootKeyboardOutputReport:
            case CharacteristicType::BootMouseInputReport:
            case CharacteristicType::GlucoseMeasurementContext:
            case CharacteristicType::BloodPressureMeasurement:
            case CharacteristicType::IntermediateCuffPressure:
            case CharacteristicType::AlertStatus:
            case CharacteristicType::RingerControlPoint:
            case CharacteristicType::RingerSetting:
            case CharacteristicType::AlertCategoryIDBitMask:
            case CharacteristicType::AlertCategoryID:
            case CharacteristicType::AlertNotificationControlPoint:
            case CharacteristicType::UnreadAlertStatus:
            case CharacteristicType::NewAlert:
            case CharacteristicType::SupportedNewAlertCategory:
            case CharacteristicType::SupportedUnreadAlertCategory:
            case CharacteristicType::BloodPressureFeature:
            case CharacteristicType::HIDInformation:
            case CharacteristicType::ReportMap:
            case CharacteristicType::HIDControlPoint:
            case CharacteristicType::Report:
            case CharacteristicType::ProtocolMode:
            case CharacteristicType::ScanIntervalWindow:
            case CharacteristicType::GlucoseFeature:
            case CharacteristicType::RecordAccessControlPoint:
            case CharacteristicType::RSCMeasurement:
            case CharacteristicType::RSCFeature:
            case CharacteristicType::SCControlPoint:
            case CharacteristicType::Aggregate:
            case CharacteristicType::CSCMeasurement:
            case CharacteristicType::CSCFeature:
            case CharacteristicType::SensorLocation:
            case CharacteristicType::PLXSpotCheckMeasurement:
            case CharacteristicType::PLXContinuousMeasurement:
            case CharacteristicType::PLX:
            case CharacteristicType::CyclingPowerMeasurement:
            case CharacteristicType::CyclingPowerVector:
            case CharacteristicType::CyclingPowerFeature:
            case CharacteristicType::CyclingPowerControlPoint:
            case CharacteristicType::LocationandSpeed:
            case CharacteristicType::Navigation:
            case CharacteristicType::PositionQuality:
            case CharacteristicType::LNFeature:
            case CharacteristicType::LNControlPoint:
            case CharacteristicType::Elevation:
            case CharacteristicType::Pressure:
            case CharacteristicType::Temperature:
            case CharacteristicType::Humidity:
            case CharacteristicType::TrueWindSpeed:
            case CharacteristicType::TrueWindDirection:
            case CharacteristicType::ApparentWindSpeed:
            case CharacteristicType::ApparentWindDirection:
            case CharacteristicType::GustFactor:
            case CharacteristicType::PollenConcentration:
            case CharacteristicType::UVIndex:
            case CharacteristicType::Irradiance:
            case CharacteristicType::Rainfall:
            case CharacteristicType::WindChill:
            case CharacteristicType::HeatIndex:
            case CharacteristicType::DewPoint:
            case CharacteristicType::DescriptorValueChanged:
            case CharacteristicType::AerobicHeartRateLowerLimit:
            case CharacteristicType::AerobicThreshold:
            case CharacteristicType::Age:
            case CharacteristicType::AnaerobicHeartRateLowerLimit:
            case CharacteristicType::AnaerobicHeartRateUpperLimit:
            case CharacteristicType::AnaerobicThreshold:
            case CharacteristicType::AerobicHeartRateUpperLimit:
            case CharacteristicType::DateofBirth:
            case CharacteristicType::DateofThresholdAssessment:
            case CharacteristicType::EmailAddress:
            case CharacteristicType::FatBurnHeartRateLowerLimit:
            case CharacteristicType::FatBurnHeartRateUpperLimit:
            case CharacteristicType::FirstName:
            case CharacteristicType::FiveZoneHeartRateLimits:
            case CharacteristicType::Gender:
            case CharacteristicType::HeartRateMax:
            case CharacteristicType::Height:
            case CharacteristicType::HipCircumference:
            case CharacteristicType::LastName:
            case CharacteristicType::MaximumRecommendedHeartRate:
            case CharacteristicType::RestingHeartRate:
            case CharacteristicType::SportTypeforAerobicandAnaerobicThresholds:
            case CharacteristicType::ThreeZoneHeartRateLimits:
            case CharacteristicType::TwoZoneHeartRateLimits:
            case CharacteristicType::VO2Max:
            case CharacteristicType::WaistCircumference:
            case CharacteristicType::Weight:
            case CharacteristicType::DatabaseChangeIncrement:
            case CharacteristicType::UserIndex:
            case CharacteristicType::BodyCompositionFeature:
            case CharacteristicType::BodyCompositionMeasurement:
            case CharacteristicType::WeightMeasurement:
            case CharacteristicType::WeightScaleFeature:
            case CharacteristicType::UserControlPoint:
            case CharacteristicType::MagneticFluxDensity2D:
            case CharacteristicType::MagneticFluxDensity3D:
            case CharacteristicType::Language:
            case CharacteristicType::BarometricPressureTrend:
            case CharacteristicType::BondManagementControlPoint:
            case CharacteristicType::BondManagementFeature:
            case CharacteristicType::CentralAddressResolution:
            case CharacteristicType::CGMMeasurement:
            case CharacteristicType::CGMFeature:
            case CharacteristicType::CGMStatus:
            case CharacteristicType::CGMSessionStartTime:
            case CharacteristicType::CGMSessionRunTime:
            case CharacteristicType::CGMSpecificOpsControlPoint:
            case CharacteristicType::IndoorPositioningConfiguration:
            case CharacteristicType::Latitude:
            case CharacteristicType::Longitude:
            case CharacteristicType::LocalNorthCoordinate:
            case CharacteristicType::LocalEastCoordinate:
            case CharacteristicType::FloorNumber:
            case CharacteristicType::Altitude:
            case CharacteristicType::Uncertainty:
            case CharacteristicType::LocationName:
            case CharacteristicType::URI:
            case CharacteristicType::HTTPHeaders:
            case CharacteristicType::HTTPStatusCode:
            case CharacteristicType::HTTPEntityBody:
            case CharacteristicType::HTTPControlPoint:
            case CharacteristicType::HTTPSSecurity:
            case CharacteristicType::TDSControlPoint:
            case CharacteristicType::OTSFeature:
            case CharacteristicType::ObjectName:
            case CharacteristicType::ObjectType:
            case CharacteristicType::ObjectSize:
            case CharacteristicType::ObjectFirstCreated:
            case CharacteristicType::ObjectLastModified:
            case CharacteristicType::ObjectID:
            case CharacteristicType::ObjectProperties:
            case CharacteristicType::ObjectActionControlPoint:
            case CharacteristicType::ObjectListControlPoint:
            case CharacteristicType::ObjectListFilter:
            case CharacteristicType::ObjectChanged:
            case CharacteristicType::ResolvablePrivateAddressOnly:
            case CharacteristicType::FitnessMachineFeature:
            case CharacteristicType::TreadmillData:
            case CharacteristicType::CrossTrainerData:
            case CharacteristicType::StepClimberData:
            case CharacteristicType::StairClimberData:
            case CharacteristicType::RowerData:
            case CharacteristicType::IndoorBikeData:
            case CharacteristicType::TrainingStatus:
            case CharacteristicType::SupportedSpeedRange:
            case CharacteristicType::SupportedInclinationRange:
            case CharacteristicType::SupportedResistanceLevelRange:
            case CharacteristicType::SupportedHeartRateRange:
            case CharacteristicType::SupportedPowerRange:
            case CharacteristicType::FitnessMachineControlPoint:
            case CharacteristicType::FitnessMachineStatus:
            case CharacteristicType::MeshProvisioningDataIn:
            case CharacteristicType::MeshProvisioningDataOut:
            case CharacteristicType::MeshProxyDataIn:
            case CharacteristicType::MeshProxyDataOut:
            case CharacteristicType::AverageCurrent:
            case CharacteristicType::AverageVoltage:
            case CharacteristicType::Boolean:
            case CharacteristicType::ChromaticDistancefromPlanckian:
            case CharacteristicType::ChromaticityCoordinates:
            case CharacteristicType::ChromaticityinCCTandDuvValues:
            case CharacteristicType::ChromaticityTolerance:
            case CharacteristicType::CIE13Dot31995ColorRenderingIndex:
            case CharacteristicType::Coefficient:
            case CharacteristicType::CorrelatedColorTemperature:
            case CharacteristicType::Count16:
            case CharacteristicType::Count24:
            case CharacteristicType::CountryCode:
            case CharacteristicType::DateUTC:
            case CharacteristicType::ElectricCurrent:
            case CharacteristicType::ElectricCurrentRange:
            case CharacteristicType::ElectricCurrentSpecification:
            case CharacteristicType::ElectricCurrentStatistics:
            case CharacteristicType::Energy:
            case CharacteristicType::EnergyinaPeriodofDay:
            case CharacteristicType::EventStatistics:
            case CharacteristicType::FixedString16:
            case CharacteristicType::FixedString24:
            case CharacteristicType::FixedString36:
            case CharacteristicType::FixedString8:
            case CharacteristicType::GenericLevel:
            case CharacteristicType::GlobalTradeItemNumber:
            case CharacteristicType::Illuminance:
            case CharacteristicType::LuminousEfficacy:
            case CharacteristicType::LuminousEnergy:
            case CharacteristicType::LuminousExposure:
            case CharacteristicType::LuminousFlux:
            case CharacteristicType::LuminousFluxRange:
            case CharacteristicType::LuminousIntensity:
            case CharacteristicType::MassFlow:
            case CharacteristicType::PerceivedLightness:
            case CharacteristicType::Percentage8:
            case CharacteristicType::Power:
            case CharacteristicType::PowerSpecification:
            case CharacteristicType::RelativeRuntimeinaCurrentRange:
            case CharacteristicType::RelativeRuntimeinaGenericLevelRange:
            case CharacteristicType::RelativeValueinaVoltageRange:
            case CharacteristicType::RelativeValueinanIlluminanceRange:
            case CharacteristicType::RelativeValueinaPeriodofDay:
            case CharacteristicType::RelativeValueinaTemperatureRange:
            case CharacteristicType::Temperature8:
            case CharacteristicType::Temperature8inaPeriodofDay:
            case CharacteristicType::Temperature8Statistics:
            case CharacteristicType::TemperatureRange:
            case CharacteristicType::TemperatureStatistics:
            case CharacteristicType::TimeDecihour8:
            case CharacteristicType::TimeExponential8:
            case CharacteristicType::TimeHour24:
            case CharacteristicType::TimeMillisecond24:
            case CharacteristicType::TimeSecond16:
            case CharacteristicType::TimeSecond8:
            case CharacteristicType::Voltage:
            case CharacteristicType::VoltageSpecification:
            case CharacteristicType::VoltageStatistics:
            case CharacteristicType::VolumeFlow:
            case CharacteristicType::ChromaticityCoordinate:
            case CharacteristicType::RCFeature:
            case CharacteristicType::RCSettings:
            case CharacteristicType::ReconnectionConfigurationControlPoint:
            case CharacteristicType::IDDStatusChanged:
            case CharacteristicType::IDDStatus:
            case CharacteristicType::IDDAnnunciationStatus:
            case CharacteristicType::IDD:
            case CharacteristicType::IDDStatusReaderControlPoint:
            case CharacteristicType::IDDCommandControlPoint:
            case CharacteristicType::IDDCommandData:
            case CharacteristicType::IDDRecordAccessControlPoint:
            case CharacteristicType::IDDHistoryData:
            case CharacteristicType::ClientSupported:
            case CharacteristicType::DatabaseHash:
            case CharacteristicType::BSSControlPoint:
            case CharacteristicType::BSSResponse:
            case CharacteristicType::EmergencyID:
            case CharacteristicType::EmergencyText:
            case CharacteristicType::ACSStatus:
            case CharacteristicType::ACSDataIn:
            case CharacteristicType::ACSDataOutNotify:
            case CharacteristicType::ACSDataOutIndicate:
            case CharacteristicType::ACSControlPoint:
            case CharacteristicType::EnhancedBloodPressureMeasurement:
            case CharacteristicType::EnhancedIntermediateCuffPressure:
            case CharacteristicType::BloodPressureRecord:
            case CharacteristicType::RegisteredUser:
            case CharacteristicType::BREDRHandoverData:
            case CharacteristicType::BluetoothSIGData:
            case CharacteristicType::ServerSupported:
            case CharacteristicType::PhysicalActivityMonitor:
            case CharacteristicType::GeneralActivityInstantaneousData:
            case CharacteristicType::GeneralActivitySummaryData:
            case CharacteristicType::CardioRespiratoryActivityInstantaneousData:
            case CharacteristicType::CardioRespiratoryActivitySummaryData:
            case CharacteristicType::StepCounterActivitySummaryData:
            case CharacteristicType::SleepActivityInstantaneousData:
            case CharacteristicType::SleepActivitySummaryData:
            case CharacteristicType::PhysicalActivityMonitorControlPoint:
            case CharacteristicType::ActivityCurrentSession:
            case CharacteristicType::PhysicalActivitySessionDescriptor:
            case CharacteristicType::PreferredUnits:
            case CharacteristicType::HighResolutionHeight:
            case CharacteristicType::MiddleName:
            case CharacteristicType::StrideLength:
            case CharacteristicType::Handedness:
            case CharacteristicType::DeviceWearingPosition:
            case CharacteristicType::FourZoneHeartRateLimits:
            case CharacteristicType::HighIntensityExerciseThreshold:
            case CharacteristicType::ActivityGoal:
            case CharacteristicType::SedentaryIntervalNotification:
            case CharacteristicType::CaloricIntake:
            case CharacteristicType::TMAPRole:
            case CharacteristicType::AudioInputState:
            case CharacteristicType::GainSettingsAttribute:
            case CharacteristicType::AudioInputType:
            case CharacteristicType::AudioInputStatus:
            case CharacteristicType::AudioInputControlPoint:
            case CharacteristicType::AudioInputDescription:
            case CharacteristicType::VolumeState:
            case CharacteristicType::VolumeControlPoint:
            case CharacteristicType::VolumeFlags:
            case CharacteristicType::VolumeOffsetState:
            case CharacteristicType::AudioLocation:
            case CharacteristicType::VolumeOffsetControlPoint:
            case CharacteristicType::AudioOutputDescription:
            case CharacteristicType::SetIdentityResolvingKey:
            case CharacteristicType::CoordinatedSetSize:
            case CharacteristicType::SetMemberLock:
            case CharacteristicType::SetMemberRank:
            case CharacteristicType::ApparentEnergy32:
            case CharacteristicType::ApparentPower:
            case CharacteristicType::CO2Concentration:
            case CharacteristicType::CosineoftheAngle:
            case CharacteristicType::DeviceTimeFeature:
            case CharacteristicType::DeviceTimeParameters:
            case CharacteristicType::DeviceTime:
            case CharacteristicType::DeviceTimeControlPoint:
            case CharacteristicType::TimeChangeLogData:
            case CharacteristicType::MediaPlayerName:
            case CharacteristicType::MediaPlayerIconObjectID:
            case CharacteristicType::MediaPlayerIconURL:
            case CharacteristicType::TrackChanged:
            case CharacteristicType::TrackTitle:
            case CharacteristicType::TrackDuration:
            case CharacteristicType::TrackPosition:
            case CharacteristicType::PlaybackSpeed:
            case CharacteristicType::SeekingSpeed:
            case CharacteristicType::CurrentTrackSegmentsObjectID:
            case CharacteristicType::CurrentTrackObjectID:
            case CharacteristicType::NextTrackObjectID:
            case CharacteristicType::ParentGroupObjectID:
            case CharacteristicType::CurrentGroupObjectID:
            case CharacteristicType::PlayingOrder:
            case CharacteristicType::PlayingOrdersSupported:
            case CharacteristicType::MediaState:
            case CharacteristicType::MediaControlPoint:
            case CharacteristicType::MediaControlPointOpcodesSupported:
            case CharacteristicType::SearchResultsObjectID:
            case CharacteristicType::SearchControlPoint:
            case CharacteristicType::Energy32:
            case CharacteristicType::MediaPlayerIconObjectType:
            case CharacteristicType::TrackSegmentsObjectType:
            case CharacteristicType::TrackObjectType:
            case CharacteristicType::GroupObjectType:
            case CharacteristicType::ConstantToneExtensionEnable:
            case CharacteristicType::AdvertisingConstantToneExtensionMinimumLength:
            case CharacteristicType::AdvertisingConstantToneExtensionMinimumTransmitCount:
            case CharacteristicType::AdvertisingConstantToneExtensionTransmitDuration:
            case CharacteristicType::AdvertisingConstantToneExtensionInterval:
            case CharacteristicType::AdvertisingConstantToneExtensionPHY:
            case CharacteristicType::BearerProviderName:
            case CharacteristicType::BearerUCI:
            case CharacteristicType::BearerTechnology:
            case CharacteristicType::BearerURISchemesSupportedList:
            case CharacteristicType::BearerSignalStrength:
            case CharacteristicType::BearerSignalStrengthReportingInterval:
            case CharacteristicType::BearerListCurrentCalls:
            case CharacteristicType::ContentControlID:
            case CharacteristicType::StatusFlags:
            case CharacteristicType::IncomingCallTargetBearerURI:
            case CharacteristicType::CallState:
            case CharacteristicType::CallControlPoint:
            case CharacteristicType::CallControlPointOptionalOpcodes:
            case CharacteristicType::TerminationReason:
            case CharacteristicType::IncomingCall:
            case CharacteristicType::CallFriendlyName:
            case CharacteristicType::Mute:
            case CharacteristicType::SinkASE:
            case CharacteristicType::SourceASE:
            case CharacteristicType::ASEControlPoint:
            case CharacteristicType::BroadcastAudioScanControlPoint:
            case CharacteristicType::BroadcastReceiveState:
            case CharacteristicType::SinkPAC:
            case CharacteristicType::SinkAudioLocations:
            case CharacteristicType::SourcePAC:
            case CharacteristicType::SourceAudioLocations:
            case CharacteristicType::AvailableAudioContexts:
            case CharacteristicType::SupportedAudioContexts:
            case CharacteristicType::AmmoniaConcentration:
            case CharacteristicType::CarbonMonoxideConcentration:
            case CharacteristicType::MethaneConcentration:
            case CharacteristicType::NitrogenDioxideConcentration:
            case CharacteristicType::NonMethaneVolatileOrganicCompoundsConcentration:
            case CharacteristicType::OzoneConcentration:
            case CharacteristicType::ParticulateMatterPM1Concentration:
            case CharacteristicType::ParticulateMatterPM2Dot5Concentration:
            case CharacteristicType::ParticulateMatterPM10Concentration:
            case CharacteristicType::SulfurDioxideConcentration:
            case CharacteristicType::SulfurHexafluorideConcentration:
            case CharacteristicType::HearingAid:
            case CharacteristicType::HearingAidPresetControlPoint:
            case CharacteristicType::ActivePresetIndex:
            case CharacteristicType::FixedString64:
            case CharacteristicType::HighTemperature:
            case CharacteristicType::HighVoltage:
            case CharacteristicType::LightDistribution:
            case CharacteristicType::LightOutput:
            case CharacteristicType::LightSourceType:
            case CharacteristicType::Noise:
            case CharacteristicType::RelativeRuntimeinaCorrelatedColorTemperatureRange:
            case CharacteristicType::TimeSecond32:
            case CharacteristicType::VOCConcentration:
            case CharacteristicType::VoltageFrequency:
                break;
        }

        if (isPrintable(data, size))
        {
            return std::unique_ptr<TextString>(new TextString(data, size, m_configuration));
        }

        return std::unique_ptr<HexString>(new HexString(data, size, m_configuration));
    }

private:
    BaseValue::Configuration m_configuration;

    bool isPrintable(const char *data, size_t size) const
    {
        for (size_t i = 0; i < size; ++i)
        {
            if (!std::isprint(data[i]))
            {
                return false;
            }
        }

        return true;
    }
};

}  // namespace bvp
