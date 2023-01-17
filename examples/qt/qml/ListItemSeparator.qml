import QtQuick 2.14


Rectangle {
    color: index === 0 ? "transparent" : UISettings.colorSeparator

    function adjustSize() {
        implicitWidth = parent.width
        implicitHeight = UISettings.normalLine
    }

    Component.onCompleted: {
        adjustSize()
    }

    Connections {
        target: root

        function onSizeChanged() {
            adjustSize()
        }
    }
}
