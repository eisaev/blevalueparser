import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.14
import dev.eisaev.blemanager 1.0


ApplicationWindow {
    id: root
    title: qsTr("BLE Value Parser Demo App")
    minimumWidth: 640
    minimumHeight: 480
    visible: true
    color: UISettings.colorBg

    property bool isDeviceConnected: BLEManagerSingleton.isDeviceConnected
    property bool isSubscribed: BLEManagerSingleton.isSubscribed

    property var devicesView: null

    Component.onCompleted: {
        UISettings.appWidth = Qt.binding(function() { return width })
        UISettings.appHeight = Qt.binding(function() { return height })

        devicesView = Qt.createComponent("Devices.qml")
        stackView.push(devicesView)
    }

    signal sizeChanged

    onWidthChanged: {
        sizeChanged()
    }

    onHeightChanged: {
        sizeChanged()
    }

    function runDelayed(timer, delayMs, cb) {
        timer.interval = delayMs;
        timer.triggered.connect(cb);
        timer.repeat = false;
        timer.start();
    }

    function goBack() {
        if (null === stackView.pop()) {
            Qt.quit()
        }
    }

    Item {
        anchors.fill: parent
        focus: true

        StackView {
            id: stackView
            anchors.fill: parent
        }

        Keys.onPressed: (event) => {
            switch (event.key) {
                case Qt.Key_Escape:
                case Qt.Key_Back: {
                    goBack();
                    event.accepted = true
                    break;
                }
                default:
                    break;
            }
        }
    }
}
