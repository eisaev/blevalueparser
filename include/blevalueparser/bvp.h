#pragma once

#include "characteristictype.h"
#include "basevalue.h"
#include "batterylevel.h"
#include "bodycompositionfeature.h"
#include "bodycompositionmeasurement.h"
#include "bodycompositionmeasurementmibfs.h"
#include "bodysensorlocation.h"
#include "currenttime.h"
#include "datetime.h"
#include "daydatetime.h"
#include "dayofweek.h"
#include "dstoffset.h"
#include "exacttime256.h"
#include "heartratecontrolpoint.h"
#include "heartratemeasurement.h"
#include "hexstring.h"
#include "localtimeinformation.h"
#include "pnpid.h"
#include "referencetimeinformation.h"
#include "textstring.h"
#include "timeaccuracy.h"
#include "timesource.h"
#include "timezone.h"
#include "userindex.h"


namespace bvp
{

class BLEValueParser final
{
public:
    Configuration configuration;

    template <class T>
    std::unique_ptr<T> make_value(const char *data, size_t size) const
    {
        static_assert(std::is_final<T>(), "Error: Cannot make value for not final class.");
        return std::unique_ptr<T>(new T(data, size, configuration));
    }

    std::unique_ptr<BaseValue> make_value(CharacteristicType characteristicType, const char *data, size_t size) const
    {
        switch (characteristicType)
        {
            // Unsorted
            // 3.70 Date Time
            case CharacteristicType::DateTime:
                return make_value<DateTime>(data, size);
            // 3.72 Day Date Time
            case CharacteristicType::DayDateTime:
                return make_value<DayDateTime>(data, size);
            // 3.73 Day of Week
            case CharacteristicType::DayOfWeek:
                return make_value<DayOfWeek>(data, size);
            // 3.76 DST Offset
            case CharacteristicType::DSTOffset:
                return make_value<DSTOffset>(data, size);
            // 3.90 Exact Time 256
            case CharacteristicType::ExactTime256:
                return make_value<ExactTime256>(data, size);
            // 3.220 Time Accuracy
            case CharacteristicType::TimeAccuracy:
                return make_value<TimeAccuracy>(data, size);
            // 3.228 Time Source
            case CharacteristicType::TimeSource:
                return make_value<TimeSource>(data, size);
            // 3.232 Time Zone
            case CharacteristicType::TimeZone:
                return make_value<TimeZone>(data, size);
            // 3.239 User Index
            case CharacteristicType::UserIndex:
                return make_value<UserIndex>(data, size);

            // Device Information Service (DIS_SPEC_V11r00.pdf)
            // 3.1 Manufacturer Name String
            case CharacteristicType::ManufacturerNameString:
                return make_value<TextString>(data, size);
            // 3.2 Model Number String
            case CharacteristicType::ModelNumberString:
                return make_value<TextString>(data, size);
            // 3.3 Serial Number String
            case CharacteristicType::SerialNumberString:
                return make_value<TextString>(data, size);
            // 3.4 Hardware Revision String
            case CharacteristicType::HardwareRevisionString:
                return make_value<TextString>(data, size);
            // 3.5 Firmware Revision String
            case CharacteristicType::FirmwareRevisionString:
                return make_value<TextString>(data, size);
            // 3.6 Software Revision String
            case CharacteristicType::SoftwareRevisionString:
                return make_value<TextString>(data, size);
            // 3.7 System ID
            case CharacteristicType::SystemID:
                return make_value<HexString>(data, size);
            // 3.8 IEEE 11073-20601 Regulatory Certification Data List
            case CharacteristicType::IEEE1107320601RegulatoryCertificationDataList:
                // TODO:
                break;
            // 3.9 PnPID
            case CharacteristicType::PnPID:
                return make_value<PnPID>(data, size);

            // Current Time Service (CTS_SPEC_V1.1.0.pdf)
            // 3.1 Current Time
            case CharacteristicType::CurrentTime:
                return make_value<CurrentTime>(data, size);
            // 3.2 Local Time Information
            case CharacteristicType::LocalTimeInformation:
                return make_value<LocalTimeInformation>(data, size);
            // 3.3 Reference Time Information
            case CharacteristicType::ReferenceTimeInformation:
                return make_value<ReferenceTimeInformation>(data, size);

            // Battery Service (BAS_V1.1.pdf)
            // 3.1 Battery Level
            case CharacteristicType::BatteryLevel:
                return make_value<BatteryLevel>(data, size);
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
                return make_value<HeartRateMeasurement>(data, size);
            // 3.2 Body Sensor Location
            case CharacteristicType::BodySensorLocation:
                return make_value<BodySensorLocation>(data, size);
            // 3.3 Heart Rate Control Point
            case CharacteristicType::HeartRateControlPoint:
                return make_value<HeartRateControlPoint>(data, size);

            // Body Composition Service (BCS_V1.0.0.pdf)
            // 3.1 BodyCompositionFeature
            case CharacteristicType::BodyCompositionFeature:
                return make_value<BodyCompositionFeature>(data, size);
            // 3.2 BodyCompositionMeasurement
            case CharacteristicType::BodyCompositionMeasurement:
                return make_value<BodyCompositionMeasurement>(data, size);
            // Non standard
            // Xiaomi Mi Body Composition Scale 2 (XMTZC05HM)
            case CharacteristicType::BodyCompositionMeasurementMIBFS:
                return make_value<BodyCompositionMeasurementMIBFS>(data, size);

            // Other
            case CharacteristicType::DeviceName:
            case CharacteristicType::Appearance:
            case CharacteristicType::PeripheralPrivacyFlag:
            case CharacteristicType::ReconnectionAddress:
            case CharacteristicType::PeripheralPreferredConnectionParameters:
            case CharacteristicType::ServiceChanged:
            case CharacteristicType::AlertLevel:
            case CharacteristicType::TxPowerLevel:
            case CharacteristicType::TimewithDST:
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
            case CharacteristicType::Unknown:
                break;
        }

        if (isPrintable(data, size))
        {
            return make_value<TextString>(data, size);
        }

        return make_value<HexString>(data, size);
    }

private:
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
