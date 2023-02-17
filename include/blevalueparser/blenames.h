#pragma once

#include <string>

#include "characteristictype.h"
#include "servicetype.h"


namespace bvp
{

static uint16_t uuidToUInt16(const std::string &uuid)
{
    if (uuid.length() != 36 ||
        uuid.substr(0, 4) != "0000" ||
        uuid.substr(8, 28) != "-0000-1000-8000-00805f9b34fb")
    {
        return 0;
    }

    const std::string uuidShort = uuid.substr(4, 4);
    try
    {
        const uint16_t result = std::stoul(uuidShort, nullptr, 16);
        return result;
    }
    catch (...)
    {
        //
    }

    return 0;
}

__attribute__ ((unused))
static CharacteristicType uuidToCharacteristicType(const std::string &uuid)
{
    CharacteristicType result = CharacteristicType(uuidToUInt16(uuid));
    switch (result)
    {
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
        case CharacteristicType::LocalTimeInformation:
        case CharacteristicType::TimewithDST:
        case CharacteristicType::TimeAccuracy:
        case CharacteristicType::TimeSource:
        case CharacteristicType::ReferenceTimeInformation:
        case CharacteristicType::TimeUpdateControlPoint:
        case CharacteristicType::TimeUpdateState:
        case CharacteristicType::GlucoseMeasurement:
        case CharacteristicType::BatteryLevel:
        case CharacteristicType::TemperatureMeasurement:
        case CharacteristicType::TemperatureType:
        case CharacteristicType::IntermediateTemperature:
        case CharacteristicType::MeasurementInterval:
        case CharacteristicType::BootKeyboardInputReport:
        case CharacteristicType::SystemID:
        case CharacteristicType::ModelNumberString:
        case CharacteristicType::SerialNumberString:
        case CharacteristicType::FirmwareRevisionString:
        case CharacteristicType::HardwareRevisionString:
        case CharacteristicType::SoftwareRevisionString:
        case CharacteristicType::ManufacturerNameString:
        case CharacteristicType::IEEE1107320601RegulatoryCertificationDataList:
        case CharacteristicType::CurrentTime:
        case CharacteristicType::MagneticDeclination:
        case CharacteristicType::ScanRefresh:
        case CharacteristicType::BootKeyboardOutputReport:
        case CharacteristicType::BootMouseInputReport:
        case CharacteristicType::GlucoseMeasurementContext:
        case CharacteristicType::BloodPressureMeasurement:
        case CharacteristicType::IntermediateCuffPressure:
        case CharacteristicType::HeartRateMeasurement:
        case CharacteristicType::BodySensorLocation:
        case CharacteristicType::HeartRateControlPoint:
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
        case CharacteristicType::PnPID:
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
        case CharacteristicType::BodyCompositionMeasurementMIBFS:
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
        case CharacteristicType::BatteryCriticalStatus:
        case CharacteristicType::BatteryHealthStatus:
        case CharacteristicType::BatteryHealthInformation:
        case CharacteristicType::BatteryInformation:
        case CharacteristicType::BatteryLevelStatus:
        case CharacteristicType::BatteryTimeStatus:
        case CharacteristicType::EstimatedServiceDate:
        case CharacteristicType::BatteryEnergyStatus:
        case CharacteristicType::Unknown:
            break;
        default:
            result = CharacteristicType::Unknown;
            break;
    }

    return result;
}

__attribute__ ((unused))
static std::string getBleName(const std::string &uuid)
{
    switch (CharacteristicType(uuidToUInt16(uuid)))
    {
        case CharacteristicType::DeviceName: return "DeviceName";
        case CharacteristicType::Appearance: return "Appearance";
        case CharacteristicType::PeripheralPrivacyFlag: return "PeripheralPrivacyFlag";
        case CharacteristicType::ReconnectionAddress: return "ReconnectionAddress";
        case CharacteristicType::PeripheralPreferredConnectionParameters: return "PeripheralPreferredConnectionParameters";
        case CharacteristicType::ServiceChanged: return "ServiceChanged";
        case CharacteristicType::AlertLevel: return "AlertLevel";
        case CharacteristicType::TxPowerLevel: return "TxPowerLevel";
        case CharacteristicType::DateTime: return "DateTime";
        case CharacteristicType::DayOfWeek: return "DayOfWeek";
        case CharacteristicType::DayDateTime: return "DayDateTime";
        case CharacteristicType::ExactTime256: return "ExactTime256";
        case CharacteristicType::DSTOffset: return "DSTOffset";
        case CharacteristicType::TimeZone: return "TimeZone";
        case CharacteristicType::LocalTimeInformation: return "LocalTimeInformation";
        case CharacteristicType::TimewithDST: return "TimewithDST";
        case CharacteristicType::TimeAccuracy: return "TimeAccuracy";
        case CharacteristicType::TimeSource: return "TimeSource";
        case CharacteristicType::ReferenceTimeInformation: return "ReferenceTimeInformation";
        case CharacteristicType::TimeUpdateControlPoint: return "TimeUpdateControlPoint";
        case CharacteristicType::TimeUpdateState: return "TimeUpdateState";
        case CharacteristicType::GlucoseMeasurement: return "GlucoseMeasurement";
        case CharacteristicType::BatteryLevel: return "BatteryLevel";
        case CharacteristicType::TemperatureMeasurement: return "TemperatureMeasurement";
        case CharacteristicType::TemperatureType: return "TemperatureType";
        case CharacteristicType::IntermediateTemperature: return "IntermediateTemperature";
        case CharacteristicType::MeasurementInterval: return "MeasurementInterval";
        case CharacteristicType::BootKeyboardInputReport: return "BootKeyboardInputReport";
        case CharacteristicType::SystemID: return "SystemID";
        case CharacteristicType::ModelNumberString: return "ModelNumberString";
        case CharacteristicType::SerialNumberString: return "SerialNumberString";
        case CharacteristicType::FirmwareRevisionString: return "FirmwareRevisionString";
        case CharacteristicType::HardwareRevisionString: return "HardwareRevisionString";
        case CharacteristicType::SoftwareRevisionString: return "SoftwareRevisionString";
        case CharacteristicType::ManufacturerNameString: return "ManufacturerNameString";
        case CharacteristicType::IEEE1107320601RegulatoryCertificationDataList: return "IEEE1107320601RegulatoryCertificationDataList";
        case CharacteristicType::CurrentTime: return "CurrentTime";
        case CharacteristicType::MagneticDeclination: return "MagneticDeclination";
        case CharacteristicType::ScanRefresh: return "ScanRefresh";
        case CharacteristicType::BootKeyboardOutputReport: return "BootKeyboardOutputReport";
        case CharacteristicType::BootMouseInputReport: return "BootMouseInputReport";
        case CharacteristicType::GlucoseMeasurementContext: return "GlucoseMeasurementContext";
        case CharacteristicType::BloodPressureMeasurement: return "BloodPressureMeasurement";
        case CharacteristicType::IntermediateCuffPressure: return "IntermediateCuffPressure";
        case CharacteristicType::HeartRateMeasurement: return "HeartRateMeasurement";
        case CharacteristicType::BodySensorLocation: return "BodySensorLocation";
        case CharacteristicType::HeartRateControlPoint: return "HeartRateControlPoint";
        case CharacteristicType::AlertStatus: return "AlertStatus";
        case CharacteristicType::RingerControlPoint: return "RingerControlPoint";
        case CharacteristicType::RingerSetting: return "RingerSetting";
        case CharacteristicType::AlertCategoryIDBitMask: return "AlertCategoryIDBitMask";
        case CharacteristicType::AlertCategoryID: return "AlertCategoryID";
        case CharacteristicType::AlertNotificationControlPoint: return "AlertNotificationControlPoint";
        case CharacteristicType::UnreadAlertStatus: return "UnreadAlertStatus";
        case CharacteristicType::NewAlert: return "NewAlert";
        case CharacteristicType::SupportedNewAlertCategory: return "SupportedNewAlertCategory";
        case CharacteristicType::SupportedUnreadAlertCategory: return "SupportedUnreadAlertCategory";
        case CharacteristicType::BloodPressureFeature: return "BloodPressureFeature";
        case CharacteristicType::HIDInformation: return "HIDInformation";
        case CharacteristicType::ReportMap: return "ReportMap";
        case CharacteristicType::HIDControlPoint: return "HIDControlPoint";
        case CharacteristicType::Report: return "Report";
        case CharacteristicType::ProtocolMode: return "ProtocolMode";
        case CharacteristicType::ScanIntervalWindow: return "ScanIntervalWindow";
        case CharacteristicType::PnPID: return "PnPID";
        case CharacteristicType::GlucoseFeature: return "GlucoseFeature";
        case CharacteristicType::RecordAccessControlPoint: return "RecordAccessControlPoint";
        case CharacteristicType::RSCMeasurement: return "RSCMeasurement";
        case CharacteristicType::RSCFeature: return "RSCFeature";
        case CharacteristicType::SCControlPoint: return "SCControlPoint";
        case CharacteristicType::Aggregate: return "Aggregate";
        case CharacteristicType::CSCMeasurement: return "CSCMeasurement";
        case CharacteristicType::CSCFeature: return "CSCFeature";
        case CharacteristicType::SensorLocation: return "SensorLocation";
        case CharacteristicType::PLXSpotCheckMeasurement: return "PLXSpotCheckMeasurement";
        case CharacteristicType::PLXContinuousMeasurement: return "PLXContinuousMeasurement";
        case CharacteristicType::PLX: return "PLX";
        case CharacteristicType::CyclingPowerMeasurement: return "CyclingPowerMeasurement";
        case CharacteristicType::CyclingPowerVector: return "CyclingPowerVector";
        case CharacteristicType::CyclingPowerFeature: return "CyclingPowerFeature";
        case CharacteristicType::CyclingPowerControlPoint: return "CyclingPowerControlPoint";
        case CharacteristicType::LocationandSpeed: return "LocationandSpeed";
        case CharacteristicType::Navigation: return "Navigation";
        case CharacteristicType::PositionQuality: return "PositionQuality";
        case CharacteristicType::LNFeature: return "LNFeature";
        case CharacteristicType::LNControlPoint: return "LNControlPoint";
        case CharacteristicType::Elevation: return "Elevation";
        case CharacteristicType::Pressure: return "Pressure";
        case CharacteristicType::Temperature: return "Temperature";
        case CharacteristicType::Humidity: return "Humidity";
        case CharacteristicType::TrueWindSpeed: return "TrueWindSpeed";
        case CharacteristicType::TrueWindDirection: return "TrueWindDirection";
        case CharacteristicType::ApparentWindSpeed: return "ApparentWindSpeed";
        case CharacteristicType::ApparentWindDirection: return "ApparentWindDirection";
        case CharacteristicType::GustFactor: return "GustFactor";
        case CharacteristicType::PollenConcentration: return "PollenConcentration";
        case CharacteristicType::UVIndex: return "UVIndex";
        case CharacteristicType::Irradiance: return "Irradiance";
        case CharacteristicType::Rainfall: return "Rainfall";
        case CharacteristicType::WindChill: return "WindChill";
        case CharacteristicType::HeatIndex: return "HeatIndex";
        case CharacteristicType::DewPoint: return "DewPoint";
        case CharacteristicType::DescriptorValueChanged: return "DescriptorValueChanged";
        case CharacteristicType::AerobicHeartRateLowerLimit: return "AerobicHeartRateLowerLimit";
        case CharacteristicType::AerobicThreshold: return "AerobicThreshold";
        case CharacteristicType::Age: return "Age";
        case CharacteristicType::AnaerobicHeartRateLowerLimit: return "AnaerobicHeartRateLowerLimit";
        case CharacteristicType::AnaerobicHeartRateUpperLimit: return "AnaerobicHeartRateUpperLimit";
        case CharacteristicType::AnaerobicThreshold: return "AnaerobicThreshold";
        case CharacteristicType::AerobicHeartRateUpperLimit: return "AerobicHeartRateUpperLimit";
        case CharacteristicType::DateofBirth: return "DateofBirth";
        case CharacteristicType::DateofThresholdAssessment: return "DateofThresholdAssessment";
        case CharacteristicType::EmailAddress: return "EmailAddress";
        case CharacteristicType::FatBurnHeartRateLowerLimit: return "FatBurnHeartRateLowerLimit";
        case CharacteristicType::FatBurnHeartRateUpperLimit: return "FatBurnHeartRateUpperLimit";
        case CharacteristicType::FirstName: return "FirstName";
        case CharacteristicType::FiveZoneHeartRateLimits: return "FiveZoneHeartRateLimits";
        case CharacteristicType::Gender: return "Gender";
        case CharacteristicType::HeartRateMax: return "HeartRateMax";
        case CharacteristicType::Height: return "Height";
        case CharacteristicType::HipCircumference: return "HipCircumference";
        case CharacteristicType::LastName: return "LastName";
        case CharacteristicType::MaximumRecommendedHeartRate: return "MaximumRecommendedHeartRate";
        case CharacteristicType::RestingHeartRate: return "RestingHeartRate";
        case CharacteristicType::SportTypeforAerobicandAnaerobicThresholds: return "SportTypeforAerobicandAnaerobicThresholds";
        case CharacteristicType::ThreeZoneHeartRateLimits: return "ThreeZoneHeartRateLimits";
        case CharacteristicType::TwoZoneHeartRateLimits: return "TwoZoneHeartRateLimits";
        case CharacteristicType::VO2Max: return "VO2Max";
        case CharacteristicType::WaistCircumference: return "WaistCircumference";
        case CharacteristicType::Weight: return "Weight";
        case CharacteristicType::DatabaseChangeIncrement: return "DatabaseChangeIncrement";
        case CharacteristicType::UserIndex: return "UserIndex";
        case CharacteristicType::BodyCompositionFeature: return "BodyCompositionFeature";
        case CharacteristicType::BodyCompositionMeasurement: return "BodyCompositionMeasurement";
        case CharacteristicType::BodyCompositionMeasurementMIBFS: return "BodyCompositionMeasurementMIBFS";
        case CharacteristicType::WeightMeasurement: return "WeightMeasurement";
        case CharacteristicType::WeightScaleFeature: return "WeightScaleFeature";
        case CharacteristicType::UserControlPoint: return "UserControlPoint";
        case CharacteristicType::MagneticFluxDensity2D: return "MagneticFluxDensity2D";
        case CharacteristicType::MagneticFluxDensity3D: return "MagneticFluxDensity3D";
        case CharacteristicType::Language: return "Language";
        case CharacteristicType::BarometricPressureTrend: return "BarometricPressureTrend";
        case CharacteristicType::BondManagementControlPoint: return "BondManagementControlPoint";
        case CharacteristicType::BondManagementFeature: return "BondManagementFeature";
        case CharacteristicType::CentralAddressResolution: return "CentralAddressResolution";
        case CharacteristicType::CGMMeasurement: return "CGMMeasurement";
        case CharacteristicType::CGMFeature: return "CGMFeature";
        case CharacteristicType::CGMStatus: return "CGMStatus";
        case CharacteristicType::CGMSessionStartTime: return "CGMSessionStartTime";
        case CharacteristicType::CGMSessionRunTime: return "CGMSessionRunTime";
        case CharacteristicType::CGMSpecificOpsControlPoint: return "CGMSpecificOpsControlPoint";
        case CharacteristicType::IndoorPositioningConfiguration: return "IndoorPositioningConfiguration";
        case CharacteristicType::Latitude: return "Latitude";
        case CharacteristicType::Longitude: return "Longitude";
        case CharacteristicType::LocalNorthCoordinate: return "LocalNorthCoordinate";
        case CharacteristicType::LocalEastCoordinate: return "LocalEastCoordinate";
        case CharacteristicType::FloorNumber: return "FloorNumber";
        case CharacteristicType::Altitude: return "Altitude";
        case CharacteristicType::Uncertainty: return "Uncertainty";
        case CharacteristicType::LocationName: return "LocationName";
        case CharacteristicType::URI: return "URI";
        case CharacteristicType::HTTPHeaders: return "HTTPHeaders";
        case CharacteristicType::HTTPStatusCode: return "HTTPStatusCode";
        case CharacteristicType::HTTPEntityBody: return "HTTPEntityBody";
        case CharacteristicType::HTTPControlPoint: return "HTTPControlPoint";
        case CharacteristicType::HTTPSSecurity: return "HTTPSSecurity";
        case CharacteristicType::TDSControlPoint: return "TDSControlPoint";
        case CharacteristicType::OTSFeature: return "OTSFeature";
        case CharacteristicType::ObjectName: return "ObjectName";
        case CharacteristicType::ObjectType: return "ObjectType";
        case CharacteristicType::ObjectSize: return "ObjectSize";
        case CharacteristicType::ObjectFirstCreated: return "ObjectFirstCreated";
        case CharacteristicType::ObjectLastModified: return "ObjectLastModified";
        case CharacteristicType::ObjectID: return "ObjectID";
        case CharacteristicType::ObjectProperties: return "ObjectProperties";
        case CharacteristicType::ObjectActionControlPoint: return "ObjectActionControlPoint";
        case CharacteristicType::ObjectListControlPoint: return "ObjectListControlPoint";
        case CharacteristicType::ObjectListFilter: return "ObjectListFilter";
        case CharacteristicType::ObjectChanged: return "ObjectChanged";
        case CharacteristicType::ResolvablePrivateAddressOnly: return "ResolvablePrivateAddressOnly";
        case CharacteristicType::FitnessMachineFeature: return "FitnessMachineFeature";
        case CharacteristicType::TreadmillData: return "TreadmillData";
        case CharacteristicType::CrossTrainerData: return "CrossTrainerData";
        case CharacteristicType::StepClimberData: return "StepClimberData";
        case CharacteristicType::StairClimberData: return "StairClimberData";
        case CharacteristicType::RowerData: return "RowerData";
        case CharacteristicType::IndoorBikeData: return "IndoorBikeData";
        case CharacteristicType::TrainingStatus: return "TrainingStatus";
        case CharacteristicType::SupportedSpeedRange: return "SupportedSpeedRange";
        case CharacteristicType::SupportedInclinationRange: return "SupportedInclinationRange";
        case CharacteristicType::SupportedResistanceLevelRange: return "SupportedResistanceLevelRange";
        case CharacteristicType::SupportedHeartRateRange: return "SupportedHeartRateRange";
        case CharacteristicType::SupportedPowerRange: return "SupportedPowerRange";
        case CharacteristicType::FitnessMachineControlPoint: return "FitnessMachineControlPoint";
        case CharacteristicType::FitnessMachineStatus: return "FitnessMachineStatus";
        case CharacteristicType::MeshProvisioningDataIn: return "MeshProvisioningDataIn";
        case CharacteristicType::MeshProvisioningDataOut: return "MeshProvisioningDataOut";
        case CharacteristicType::MeshProxyDataIn: return "MeshProxyDataIn";
        case CharacteristicType::MeshProxyDataOut: return "MeshProxyDataOut";
        case CharacteristicType::AverageCurrent: return "AverageCurrent";
        case CharacteristicType::AverageVoltage: return "AverageVoltage";
        case CharacteristicType::Boolean: return "Boolean";
        case CharacteristicType::ChromaticDistancefromPlanckian: return "ChromaticDistancefromPlanckian";
        case CharacteristicType::ChromaticityCoordinates: return "ChromaticityCoordinates";
        case CharacteristicType::ChromaticityinCCTandDuvValues: return "ChromaticityinCCTandDuvValues";
        case CharacteristicType::ChromaticityTolerance: return "ChromaticityTolerance";
        case CharacteristicType::CIE13Dot31995ColorRenderingIndex: return "CIE13Dot31995ColorRenderingIndex";
        case CharacteristicType::Coefficient: return "Coefficient";
        case CharacteristicType::CorrelatedColorTemperature: return "CorrelatedColorTemperature";
        case CharacteristicType::Count16: return "Count16";
        case CharacteristicType::Count24: return "Count24";
        case CharacteristicType::CountryCode: return "CountryCode";
        case CharacteristicType::DateUTC: return "DateUTC";
        case CharacteristicType::ElectricCurrent: return "ElectricCurrent";
        case CharacteristicType::ElectricCurrentRange: return "ElectricCurrentRange";
        case CharacteristicType::ElectricCurrentSpecification: return "ElectricCurrentSpecification";
        case CharacteristicType::ElectricCurrentStatistics: return "ElectricCurrentStatistics";
        case CharacteristicType::Energy: return "Energy";
        case CharacteristicType::EnergyinaPeriodofDay: return "EnergyinaPeriodofDay";
        case CharacteristicType::EventStatistics: return "EventStatistics";
        case CharacteristicType::FixedString16: return "FixedString16";
        case CharacteristicType::FixedString24: return "FixedString24";
        case CharacteristicType::FixedString36: return "FixedString36";
        case CharacteristicType::FixedString8: return "FixedString8";
        case CharacteristicType::GenericLevel: return "GenericLevel";
        case CharacteristicType::GlobalTradeItemNumber: return "GlobalTradeItemNumber";
        case CharacteristicType::Illuminance: return "Illuminance";
        case CharacteristicType::LuminousEfficacy: return "LuminousEfficacy";
        case CharacteristicType::LuminousEnergy: return "LuminousEnergy";
        case CharacteristicType::LuminousExposure: return "LuminousExposure";
        case CharacteristicType::LuminousFlux: return "LuminousFlux";
        case CharacteristicType::LuminousFluxRange: return "LuminousFluxRange";
        case CharacteristicType::LuminousIntensity: return "LuminousIntensity";
        case CharacteristicType::MassFlow: return "MassFlow";
        case CharacteristicType::PerceivedLightness: return "PerceivedLightness";
        case CharacteristicType::Percentage8: return "Percentage8";
        case CharacteristicType::Power: return "Power";
        case CharacteristicType::PowerSpecification: return "PowerSpecification";
        case CharacteristicType::RelativeRuntimeinaCurrentRange: return "RelativeRuntimeinaCurrentRange";
        case CharacteristicType::RelativeRuntimeinaGenericLevelRange: return "RelativeRuntimeinaGenericLevelRange";
        case CharacteristicType::RelativeValueinaVoltageRange: return "RelativeValueinaVoltageRange";
        case CharacteristicType::RelativeValueinanIlluminanceRange: return "RelativeValueinanIlluminanceRange";
        case CharacteristicType::RelativeValueinaPeriodofDay: return "RelativeValueinaPeriodofDay";
        case CharacteristicType::RelativeValueinaTemperatureRange: return "RelativeValueinaTemperatureRange";
        case CharacteristicType::Temperature8: return "Temperature8";
        case CharacteristicType::Temperature8inaPeriodofDay: return "Temperature8inaPeriodofDay";
        case CharacteristicType::Temperature8Statistics: return "Temperature8Statistics";
        case CharacteristicType::TemperatureRange: return "TemperatureRange";
        case CharacteristicType::TemperatureStatistics: return "TemperatureStatistics";
        case CharacteristicType::TimeDecihour8: return "TimeDecihour8";
        case CharacteristicType::TimeExponential8: return "TimeExponential8";
        case CharacteristicType::TimeHour24: return "TimeHour24";
        case CharacteristicType::TimeMillisecond24: return "TimeMillisecond24";
        case CharacteristicType::TimeSecond16: return "TimeSecond16";
        case CharacteristicType::TimeSecond8: return "TimeSecond8";
        case CharacteristicType::Voltage: return "Voltage";
        case CharacteristicType::VoltageSpecification: return "VoltageSpecification";
        case CharacteristicType::VoltageStatistics: return "VoltageStatistics";
        case CharacteristicType::VolumeFlow: return "VolumeFlow";
        case CharacteristicType::ChromaticityCoordinate: return "ChromaticityCoordinate";
        case CharacteristicType::RCFeature: return "RCFeature";
        case CharacteristicType::RCSettings: return "RCSettings";
        case CharacteristicType::ReconnectionConfigurationControlPoint: return "ReconnectionConfigurationControlPoint";
        case CharacteristicType::IDDStatusChanged: return "IDDStatusChanged";
        case CharacteristicType::IDDStatus: return "IDDStatus";
        case CharacteristicType::IDDAnnunciationStatus: return "IDDAnnunciationStatus";
        case CharacteristicType::IDD: return "IDD";
        case CharacteristicType::IDDStatusReaderControlPoint: return "IDDStatusReaderControlPoint";
        case CharacteristicType::IDDCommandControlPoint: return "IDDCommandControlPoint";
        case CharacteristicType::IDDCommandData: return "IDDCommandData";
        case CharacteristicType::IDDRecordAccessControlPoint: return "IDDRecordAccessControlPoint";
        case CharacteristicType::IDDHistoryData: return "IDDHistoryData";
        case CharacteristicType::ClientSupported: return "ClientSupported";
        case CharacteristicType::DatabaseHash: return "DatabaseHash";
        case CharacteristicType::BSSControlPoint: return "BSSControlPoint";
        case CharacteristicType::BSSResponse: return "BSSResponse";
        case CharacteristicType::EmergencyID: return "EmergencyID";
        case CharacteristicType::EmergencyText: return "EmergencyText";
        case CharacteristicType::ACSStatus: return "ACSStatus";
        case CharacteristicType::ACSDataIn: return "ACSDataIn";
        case CharacteristicType::ACSDataOutNotify: return "ACSDataOutNotify";
        case CharacteristicType::ACSDataOutIndicate: return "ACSDataOutIndicate";
        case CharacteristicType::ACSControlPoint: return "ACSControlPoint";
        case CharacteristicType::EnhancedBloodPressureMeasurement: return "EnhancedBloodPressureMeasurement";
        case CharacteristicType::EnhancedIntermediateCuffPressure: return "EnhancedIntermediateCuffPressure";
        case CharacteristicType::BloodPressureRecord: return "BloodPressureRecord";
        case CharacteristicType::RegisteredUser: return "RegisteredUser";
        case CharacteristicType::BREDRHandoverData: return "BREDRHandoverData";
        case CharacteristicType::BluetoothSIGData: return "BluetoothSIGData";
        case CharacteristicType::ServerSupported: return "ServerSupported";
        case CharacteristicType::PhysicalActivityMonitor: return "PhysicalActivityMonitor";
        case CharacteristicType::GeneralActivityInstantaneousData: return "GeneralActivityInstantaneousData";
        case CharacteristicType::GeneralActivitySummaryData: return "GeneralActivitySummaryData";
        case CharacteristicType::CardioRespiratoryActivityInstantaneousData: return "CardioRespiratoryActivityInstantaneousData";
        case CharacteristicType::CardioRespiratoryActivitySummaryData: return "CardioRespiratoryActivitySummaryData";
        case CharacteristicType::StepCounterActivitySummaryData: return "StepCounterActivitySummaryData";
        case CharacteristicType::SleepActivityInstantaneousData: return "SleepActivityInstantaneousData";
        case CharacteristicType::SleepActivitySummaryData: return "SleepActivitySummaryData";
        case CharacteristicType::PhysicalActivityMonitorControlPoint: return "PhysicalActivityMonitorControlPoint";
        case CharacteristicType::ActivityCurrentSession: return "ActivityCurrentSession";
        case CharacteristicType::PhysicalActivitySessionDescriptor: return "PhysicalActivitySessionDescriptor";
        case CharacteristicType::PreferredUnits: return "PreferredUnits";
        case CharacteristicType::HighResolutionHeight: return "HighResolutionHeight";
        case CharacteristicType::MiddleName: return "MiddleName";
        case CharacteristicType::StrideLength: return "StrideLength";
        case CharacteristicType::Handedness: return "Handedness";
        case CharacteristicType::DeviceWearingPosition: return "DeviceWearingPosition";
        case CharacteristicType::FourZoneHeartRateLimits: return "FourZoneHeartRateLimits";
        case CharacteristicType::HighIntensityExerciseThreshold: return "HighIntensityExerciseThreshold";
        case CharacteristicType::ActivityGoal: return "ActivityGoal";
        case CharacteristicType::SedentaryIntervalNotification: return "SedentaryIntervalNotification";
        case CharacteristicType::CaloricIntake: return "CaloricIntake";
        case CharacteristicType::TMAPRole: return "TMAPRole";
        case CharacteristicType::AudioInputState: return "AudioInputState";
        case CharacteristicType::GainSettingsAttribute: return "GainSettingsAttribute";
        case CharacteristicType::AudioInputType: return "AudioInputType";
        case CharacteristicType::AudioInputStatus: return "AudioInputStatus";
        case CharacteristicType::AudioInputControlPoint: return "AudioInputControlPoint";
        case CharacteristicType::AudioInputDescription: return "AudioInputDescription";
        case CharacteristicType::VolumeState: return "VolumeState";
        case CharacteristicType::VolumeControlPoint: return "VolumeControlPoint";
        case CharacteristicType::VolumeFlags: return "VolumeFlags";
        case CharacteristicType::VolumeOffsetState: return "VolumeOffsetState";
        case CharacteristicType::AudioLocation: return "AudioLocation";
        case CharacteristicType::VolumeOffsetControlPoint: return "VolumeOffsetControlPoint";
        case CharacteristicType::AudioOutputDescription: return "AudioOutputDescription";
        case CharacteristicType::SetIdentityResolvingKey: return "SetIdentityResolvingKey";
        case CharacteristicType::CoordinatedSetSize: return "CoordinatedSetSize";
        case CharacteristicType::SetMemberLock: return "SetMemberLock";
        case CharacteristicType::SetMemberRank: return "SetMemberRank";
        case CharacteristicType::ApparentEnergy32: return "ApparentEnergy32";
        case CharacteristicType::ApparentPower: return "ApparentPower";
        case CharacteristicType::CO2Concentration: return "CO2Concentration";
        case CharacteristicType::CosineoftheAngle: return "CosineoftheAngle";
        case CharacteristicType::DeviceTimeFeature: return "DeviceTimeFeature";
        case CharacteristicType::DeviceTimeParameters: return "DeviceTimeParameters";
        case CharacteristicType::DeviceTime: return "DeviceTime";
        case CharacteristicType::DeviceTimeControlPoint: return "DeviceTimeControlPoint";
        case CharacteristicType::TimeChangeLogData: return "TimeChangeLogData";
        case CharacteristicType::MediaPlayerName: return "MediaPlayerName";
        case CharacteristicType::MediaPlayerIconObjectID: return "MediaPlayerIconObjectID";
        case CharacteristicType::MediaPlayerIconURL: return "MediaPlayerIconURL";
        case CharacteristicType::TrackChanged: return "TrackChanged";
        case CharacteristicType::TrackTitle: return "TrackTitle";
        case CharacteristicType::TrackDuration: return "TrackDuration";
        case CharacteristicType::TrackPosition: return "TrackPosition";
        case CharacteristicType::PlaybackSpeed: return "PlaybackSpeed";
        case CharacteristicType::SeekingSpeed: return "SeekingSpeed";
        case CharacteristicType::CurrentTrackSegmentsObjectID: return "CurrentTrackSegmentsObjectID";
        case CharacteristicType::CurrentTrackObjectID: return "CurrentTrackObjectID";
        case CharacteristicType::NextTrackObjectID: return "NextTrackObjectID";
        case CharacteristicType::ParentGroupObjectID: return "ParentGroupObjectID";
        case CharacteristicType::CurrentGroupObjectID: return "CurrentGroupObjectID";
        case CharacteristicType::PlayingOrder: return "PlayingOrder";
        case CharacteristicType::PlayingOrdersSupported: return "PlayingOrdersSupported";
        case CharacteristicType::MediaState: return "MediaState";
        case CharacteristicType::MediaControlPoint: return "MediaControlPoint";
        case CharacteristicType::MediaControlPointOpcodesSupported: return "MediaControlPointOpcodesSupported";
        case CharacteristicType::SearchResultsObjectID: return "SearchResultsObjectID";
        case CharacteristicType::SearchControlPoint: return "SearchControlPoint";
        case CharacteristicType::Energy32: return "Energy32";
        case CharacteristicType::MediaPlayerIconObjectType: return "MediaPlayerIconObjectType";
        case CharacteristicType::TrackSegmentsObjectType: return "TrackSegmentsObjectType";
        case CharacteristicType::TrackObjectType: return "TrackObjectType";
        case CharacteristicType::GroupObjectType: return "GroupObjectType";
        case CharacteristicType::ConstantToneExtensionEnable: return "ConstantToneExtensionEnable";
        case CharacteristicType::AdvertisingConstantToneExtensionMinimumLength: return "AdvertisingConstantToneExtensionMinimumLength";
        case CharacteristicType::AdvertisingConstantToneExtensionMinimumTransmitCount: return "AdvertisingConstantToneExtensionMinimumTransmitCount";
        case CharacteristicType::AdvertisingConstantToneExtensionTransmitDuration: return "AdvertisingConstantToneExtensionTransmitDuration";
        case CharacteristicType::AdvertisingConstantToneExtensionInterval: return "AdvertisingConstantToneExtensionInterval";
        case CharacteristicType::AdvertisingConstantToneExtensionPHY: return "AdvertisingConstantToneExtensionPHY";
        case CharacteristicType::BearerProviderName: return "BearerProviderName";
        case CharacteristicType::BearerUCI: return "BearerUCI";
        case CharacteristicType::BearerTechnology: return "BearerTechnology";
        case CharacteristicType::BearerURISchemesSupportedList: return "BearerURISchemesSupportedList";
        case CharacteristicType::BearerSignalStrength: return "BearerSignalStrength";
        case CharacteristicType::BearerSignalStrengthReportingInterval: return "BearerSignalStrengthReportingInterval";
        case CharacteristicType::BearerListCurrentCalls: return "BearerListCurrentCalls";
        case CharacteristicType::ContentControlID: return "ContentControlID";
        case CharacteristicType::StatusFlags: return "StatusFlags";
        case CharacteristicType::IncomingCallTargetBearerURI: return "IncomingCallTargetBearerURI";
        case CharacteristicType::CallState: return "CallState";
        case CharacteristicType::CallControlPoint: return "CallControlPoint";
        case CharacteristicType::CallControlPointOptionalOpcodes: return "CallControlPointOptionalOpcodes";
        case CharacteristicType::TerminationReason: return "TerminationReason";
        case CharacteristicType::IncomingCall: return "IncomingCall";
        case CharacteristicType::CallFriendlyName: return "CallFriendlyName";
        case CharacteristicType::Mute: return "Mute";
        case CharacteristicType::SinkASE: return "SinkASE";
        case CharacteristicType::SourceASE: return "SourceASE";
        case CharacteristicType::ASEControlPoint: return "ASEControlPoint";
        case CharacteristicType::BroadcastAudioScanControlPoint: return "BroadcastAudioScanControlPoint";
        case CharacteristicType::BroadcastReceiveState: return "BroadcastReceiveState";
        case CharacteristicType::SinkPAC: return "SinkPAC";
        case CharacteristicType::SinkAudioLocations: return "SinkAudioLocations";
        case CharacteristicType::SourcePAC: return "SourcePAC";
        case CharacteristicType::SourceAudioLocations: return "SourceAudioLocations";
        case CharacteristicType::AvailableAudioContexts: return "AvailableAudioContexts";
        case CharacteristicType::SupportedAudioContexts: return "SupportedAudioContexts";
        case CharacteristicType::AmmoniaConcentration: return "AmmoniaConcentration";
        case CharacteristicType::CarbonMonoxideConcentration: return "CarbonMonoxideConcentration";
        case CharacteristicType::MethaneConcentration: return "MethaneConcentration";
        case CharacteristicType::NitrogenDioxideConcentration: return "NitrogenDioxideConcentration";
        case CharacteristicType::NonMethaneVolatileOrganicCompoundsConcentration: return "NonMethaneVolatileOrganicCompoundsConcentration";
        case CharacteristicType::OzoneConcentration: return "OzoneConcentration";
        case CharacteristicType::ParticulateMatterPM1Concentration: return "ParticulateMatterPM1Concentration";
        case CharacteristicType::ParticulateMatterPM2Dot5Concentration: return "ParticulateMatterPM2Dot5Concentration";
        case CharacteristicType::ParticulateMatterPM10Concentration: return "ParticulateMatterPM10Concentration";
        case CharacteristicType::SulfurDioxideConcentration: return "SulfurDioxideConcentration";
        case CharacteristicType::SulfurHexafluorideConcentration: return "SulfurHexafluorideConcentration";
        case CharacteristicType::HearingAid: return "HearingAid";
        case CharacteristicType::HearingAidPresetControlPoint: return "HearingAidPresetControlPoint";
        case CharacteristicType::ActivePresetIndex: return "ActivePresetIndex";
        case CharacteristicType::FixedString64: return "FixedString64";
        case CharacteristicType::HighTemperature: return "HighTemperature";
        case CharacteristicType::HighVoltage: return "HighVoltage";
        case CharacteristicType::LightDistribution: return "LightDistribution";
        case CharacteristicType::LightOutput: return "LightOutput";
        case CharacteristicType::LightSourceType: return "LightSourceType";
        case CharacteristicType::Noise: return "Noise";
        case CharacteristicType::RelativeRuntimeinaCorrelatedColorTemperatureRange: return "RelativeRuntimeinaCorrelatedColorTemperatureRange";
        case CharacteristicType::TimeSecond32: return "TimeSecond32";
        case CharacteristicType::VOCConcentration: return "VOCConcentration";
        case CharacteristicType::VoltageFrequency: return "VoltageFrequency";
        case CharacteristicType::BatteryCriticalStatus: return "BatteryCriticalStatus";
        case CharacteristicType::BatteryHealthStatus: return "BatteryHealthStatus";
        case CharacteristicType::BatteryHealthInformation: return "BatteryHealthInformation";
        case CharacteristicType::BatteryInformation: return "BatteryInformation";
        case CharacteristicType::BatteryLevelStatus: return "BatteryLevelStatus";
        case CharacteristicType::BatteryTimeStatus: return "BatteryTimeStatus";
        case CharacteristicType::EstimatedServiceDate: return "EstimatedServiceDate";
        case CharacteristicType::BatteryEnergyStatus: return "BatteryEnergyStatus";
        case CharacteristicType::Unknown: return "<Unknown>";
    }

    switch (ServiceType(uuidToUInt16(uuid)))
    {
        case ServiceType::AlertNotification: return "AlertNotification";
        case ServiceType::AudioInputControl: return "AudioInputControl";
        case ServiceType::AudioStreamControl: return "AudioStreamControl";
        case ServiceType::AuthorizationControl: return "AuthorizationControl";
        case ServiceType::AutomationIO: return "AutomationIO";
        case ServiceType::BasicAudioAnnouncement: return "BasicAudioAnnouncement";
        case ServiceType::Battery: return "Battery";
        case ServiceType::BinarySensor: return "BinarySensor";
        case ServiceType::BloodPressure: return "BloodPressure";
        case ServiceType::BodyComposition: return "BodyComposition";
        case ServiceType::BondManagement: return "BondManagement";
        case ServiceType::BroadcastAudioAnnouncement: return "BroadcastAudioAnnouncement";
        case ServiceType::BroadcastAudioScan: return "BroadcastAudioScan";
        case ServiceType::CommonAudio: return "CommonAudio";
        case ServiceType::ConstantToneExtension: return "ConstantToneExtension";
        case ServiceType::ContinuousGlucoseMonitoring: return "ContinuousGlucoseMonitoring";
        case ServiceType::CoordinatedSetIdentification: return "CoordinatedSetIdentification";
        case ServiceType::CurrentTime: return "CurrentTime";
        case ServiceType::CyclingPower: return "CyclingPower";
        case ServiceType::CyclingSpeedandCadence: return "CyclingSpeedandCadence";
        case ServiceType::DeviceInformation: return "DeviceInformation";
        case ServiceType::DeviceTime: return "DeviceTime";
        case ServiceType::EmergencyConfiguration: return "EmergencyConfiguration";
        case ServiceType::EnvironmentalSensing: return "EnvironmentalSensing";
        case ServiceType::FitnessMachine: return "FitnessMachine";
        case ServiceType::GenericAccess: return "GenericAccess";
        case ServiceType::GenericAttribute: return "GenericAttribute";
        case ServiceType::GenericMediaControl: return "GenericMediaControl";
        case ServiceType::GenericTelephoneBearer: return "GenericTelephoneBearer";
        case ServiceType::Glucose: return "Glucose";
        case ServiceType::HealthThermometer: return "HealthThermometer";
        case ServiceType::HearingAid: return "HearingAid";
        case ServiceType::HeartRate: return "HeartRate";
        case ServiceType::HTTPProxy: return "HTTPProxy";
        case ServiceType::HumanInterfaceDevice: return "HumanInterfaceDevice";
        case ServiceType::ImmediateAlert: return "ImmediateAlert";
        case ServiceType::IndoorPositioning: return "IndoorPositioning";
        case ServiceType::InsulinDelivery: return "InsulinDelivery";
        case ServiceType::InternetProtocolSupport: return "InternetProtocolSupport";
        case ServiceType::LinkLoss: return "LinkLoss";
        case ServiceType::LocationandNavigation: return "LocationandNavigation";
        case ServiceType::MediaControl: return "MediaControl";
        case ServiceType::MeshProvisioning: return "MeshProvisioning";
        case ServiceType::MeshProxy: return "MeshProxy";
        case ServiceType::MicrophoneControl: return "MicrophoneControl";
        case ServiceType::NextDSTChange: return "NextDSTChange";
        case ServiceType::ObjectTransfer: return "ObjectTransfer";
        case ServiceType::PhoneAlertStatus: return "PhoneAlertStatus";
        case ServiceType::PhysicalActivityMonitor: return "PhysicalActivityMonitor";
        case ServiceType::PublicBroadcastAnnouncement: return "PublicBroadcastAnnouncement";
        case ServiceType::PublishedAudioCapabilities: return "PublishedAudioCapabilities";
        case ServiceType::PulseOximeter: return "PulseOximeter";
        case ServiceType::ReconnectionConfiguration: return "ReconnectionConfiguration";
        case ServiceType::ReferenceTimeUpdate: return "ReferenceTimeUpdate";
        case ServiceType::RunningSpeedandCadence: return "RunningSpeedandCadence";
        case ServiceType::ScanParameters: return "ScanParameters";
        case ServiceType::TelephoneBearer: return "TelephoneBearer";
        case ServiceType::TMAS: return "TMAS";
        case ServiceType::TransportDiscovery: return "TransportDiscovery";
        case ServiceType::TxPower: return "TxPower";
        case ServiceType::UserData: return "UserData";
        case ServiceType::VolumeControl: return "VolumeControl";
        case ServiceType::VolumeOffsetControl: return "VolumeOffsetControl";
        case ServiceType::WeightScale: return "WeightScale";
        case ServiceType::Unknown: return "<Unknown>";
    }

    return "<Unknown>";
}

}  // namespace bvp
