#pragma once


namespace bvp
{

// Assigned_Numbers_Released-2022-12-20.pdf
// 3.4.1 Services by Name
// 3.4.2 Services by UUID
enum class ServiceType
{
    AlertNotification = 0x1811,
    AudioInputControl = 0x1843,
    AudioStreamControl = 0x184E,
    AuthorizationControl = 0x183D,
    AutomationIO = 0x1815,
    BasicAudioAnnouncement = 0x1851,
    Battery = 0x180F,
    BinarySensor = 0x183B,
    BloodPressure = 0x1810,
    BodyComposition = 0x181B,
    BondManagement = 0x181E,
    BroadcastAudioAnnouncement = 0x1852,
    BroadcastAudioScan = 0x184F,
    CommonAudio = 0x1853,
    ConstantToneExtension = 0x184A,
    ContinuousGlucoseMonitoring = 0x181F,
    CoordinatedSetIdentification = 0x1846,
    CurrentTime = 0x1805,
    CyclingPower = 0x1818,
    CyclingSpeedandCadence = 0x1816,
    DeviceInformation = 0x180A,
    DeviceTime = 0x1847,
    EmergencyConfiguration = 0x183C,
    EnvironmentalSensing = 0x181A,
    FitnessMachine = 0x1826,
    GenericAccess = 0x1800,
    GenericAttribute = 0x1801,
    GenericMediaControl = 0x1849,
    GenericTelephoneBearer = 0x184C,
    Glucose = 0x1808,
    HealthThermometer = 0x1809,
    HearingAid = 0x1854,
    HeartRate = 0x180D,
    HTTPProxy = 0x1823,
    HumanInterfaceDevice = 0x1812,
    ImmediateAlert = 0x1802,
    IndoorPositioning = 0x1821,
    InsulinDelivery = 0x183A,
    InternetProtocolSupport = 0x1820,
    LinkLoss = 0x1803,
    LocationandNavigation = 0x1819,
    MediaControl = 0x1848,
    MeshProvisioning = 0x1827,
    MeshProxy = 0x1828,
    MicrophoneControl = 0x184D,
    NextDSTChange = 0x1807,
    ObjectTransfer = 0x1825,
    PhoneAlertStatus = 0x180E,
    PhysicalActivityMonitor = 0x183E,
    PublicBroadcastAnnouncement = 0x1856,
    PublishedAudioCapabilities = 0x1850,
    PulseOximeter = 0x1822,
    ReconnectionConfiguration = 0x1829,
    ReferenceTimeUpdate = 0x1806,
    RunningSpeedandCadence = 0x1814,
    ScanParameters = 0x1813,
    TelephoneBearer = 0x184B,
    TMAS = 0x1855,
    TransportDiscovery = 0x1824,
    TxPower = 0x1804,
    UserData = 0x181C,
    VolumeControl = 0x1844,
    VolumeOffsetControl = 0x1845,
    WeightScale = 0x181D,
    Unknown = 0xFFFF
};

}  // namespace bvp
