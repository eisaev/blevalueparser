import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import dev.eisaev.blemanager 1.0


Item {
    property var characteristicView: null

    function onCharacteristicSelected(index) {
        BLEManagerSingleton.connectToCharacteristic(index)
        characteristicView = Qt.createComponent("Characteristic.qml")
        stackView.push(characteristicView)
        stackView.currentItem.setCharacteristicName(BLEManagerSingleton.characteristicName)
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: UISettings.normalSpacer

        PageHeader {
            text: qsTr("Characteristics")
        }

        HorizontalBusyIndicator {
            Layout.fillWidth: true
            running: BLEManagerSingleton.isCharacteristicsDiscoveryInProgress
        }

        PageBody {
            enabled: BLEManagerSingleton.isDeviceConnected

            BodyListView {
                model: BLEManagerSingleton.availableCharacteristics
                delegate: ListItem {
                    title: modelData.description

                    onSelected: (index) => {
                        onCharacteristicSelected(index)
                    }

                    ListItemLayout {
                        ListItemDescription {
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
