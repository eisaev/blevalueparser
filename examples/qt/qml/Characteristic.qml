import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14
import dev.eisaev.blemanager 1.0


Item {
    id: control
    property var model: [
        {
            title: qsTr("Raw data"),
            value: BLEManagerSingleton.characteristicValue
        },
        {
            title: qsTr("Parsed data"),
//            value: "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum."
            value: BLEManagerSingleton.characteristicValueParsed
        }
    ]

    function setCharacteristicName(name) {
        titleCharacteristic.text = name
    }

    StackView.onDeactivated: {
        BLEManagerSingleton.unsubscribeFromNotifications()
    }

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: UISettings.normalSpacer

        PageHeader {
            id: titleCharacteristic
        }

        PageBody {
            enabled: BLEManagerSingleton.isDeviceConnected

            BodyListView {
                model: control.model
                delegate: ListItem {
                    title: modelData.title

                    onSelected: (index) => {
                        console.log(index)
                    }

                    ListItemLayout {
                        ListItemDescription {
                            text: modelData.value
                        }

                        ListItemSpacer {}
                    }
                }
            }
        }

        ButtonsRow {
            enabled: BLEManagerSingleton.isActive

            CustomButton {
                visible: BLEManagerSingleton.characteristicIsRead
                enabled: isDeviceConnected
                text: qsTr("Read value")
                onClicked: BLEManagerSingleton.readCharacteristicValue()
            }

            CustomButton {
                visible: BLEManagerSingleton.characteristicIsNotify
                enabled: isDeviceConnected && !isSubscribed
                text: qsTr("Subscribe")
                onClicked: BLEManagerSingleton.subscribeToNotifications()
            }
        }

        StatusBar {}
    }
}
