import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import dev.eisaev.blemanager 1.0


Item {
    property var characteristicsView: null

    function onServiceSelected(index) {
        BLEManagerSingleton.connectToService(index)
        characteristicsView = Qt.createComponent("Characteristics.qml")
        stackView.push(characteristicsView)
    }

    StackView.onActivated: {
        BLEManagerSingleton.disconnectFromCharacteristic()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: UISettings.normalSpacer

        PageHeader {
            text: qsTr("Services")
        }

        HorizontalBusyIndicator {
            Layout.fillWidth: true
            running: BLEManagerSingleton.isServicesDiscoveryInProgress
        }

        PageBody {
            enabled: BLEManagerSingleton.isDeviceConnected

            BodyListView {
                model: BLEManagerSingleton.availableServices
                delegate: ListItem {
                    title: modelData.description

                    onSelected: (index) => {
                        onServiceSelected(index)
                    }

                    ListItemLayout {
                        ListItemDescription {
                            Layout.fillWidth: true
                            text: modelData.uuid
                        }

                        ListItemSpacer {}
                    }
                }
            }
        }

        StatusBar {}
    }
}
