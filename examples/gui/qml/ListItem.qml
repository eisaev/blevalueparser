import QtQuick 2.14


Rectangle {
    width: parent ? parent.width : 0
    color: UISettings.colorBgAlt

    // Workaround for
    // https://bugreports.qt.io/browse/QTBUG-86009
    required property int index
    required property var modelData
    required property var title

    signal selected(int index)

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onEntered: {
            parent.color = UISettings.colorHighlight
        }

        onExited: {
            parent.color = "transparent"
        }

        onClicked: {
            selected(index)
        }
    }
}
