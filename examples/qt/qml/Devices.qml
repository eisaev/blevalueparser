import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import dev.eisaev.blemanager 1.0


Item {
    property var servicesView: null

    function onDeviceSelected(index) {
        servicesView = Qt.createComponent("Services.qml")
        stackView.push(servicesView)
        BLEManagerSingleton.stopDevicesDiscovery()
        BLEManagerSingleton.connectToDevice(index)
    }

    function rssiColor(level) {
        if (level > -70) {
            return "green"
        } else if (level < -90) {
            return "red"
        } else {
            return "darkorange"
        }
    }

//    Component.onCompleted: {
//        BLEManagerSingleton.startDevicesDiscovery()
//    }

    StackView.onActivated: {
        BLEManagerSingleton.disconnectFromService()
        BLEManagerSingleton.disconnectFromDevice()
        BLEManagerSingleton.startDevicesDiscovery()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: UISettings.normalSpacer

        PageHeader {
            backAsExit: true
            text: qsTr("Devices")
        }

        HorizontalBusyIndicator {
            Layout.fillWidth: true
            running: BLEManagerSingleton.isDeviceDiscoveryInProgress
        }

        PageBody {
            enabled: BLEManagerSingleton.isActive

            BodyListView {
                model: BLEManagerSingleton.availableDevices
                delegate: ListItem {
                    title: modelData.name === "" ? "<NoName>" : modelData.name

                    onSelected: (index) => {
                        onDeviceSelected(index)
                    }

                    ListItemLayout {
                        RowLayout {
                            width: parent.width

                            ListItemDescription {
                                Layout.fillWidth: true
                                text: modelData.address
                            }

                            ListItemInformation {
                                color: rssiColor(modelData.rssi)
                                text: modelData.rssi
                            }
                        }

                        ListItemSpacer {}
                    }
                }
            }
        }

        ButtonsRow {
            enabled: BLEManagerSingleton.isActive

            CustomButton {
                enabled: !BLEManagerSingleton.isDeviceDiscoveryInProgress
                text: qsTr("Discovery devices")
                onClicked: BLEManagerSingleton.startDevicesDiscovery()
            }
        }

        StatusBar {}
    }
}
