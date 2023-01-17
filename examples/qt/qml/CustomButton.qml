import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14


Button {
    id: control
    text: qsTr("Button")
    font.pixelSize: UISettings.fontSizeNormal

    property bool square: false

    function adjustSize() {
        if (square) {
            padding = UISettings.halfSpacer
            width = height
        } else {
            verticalPadding = UISettings.normalSpacer
            horizontalPadding = UISettings.doubleSpacer
        }
    }

    Component.onCompleted: {
        adjustSize()
    }

    contentItem: Text {
        text: control.text
        font: control.font
        opacity: enabled ? 1.0 : 0.5
        color: UISettings.colorLine
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }

    background: Rectangle {
        opacity: enabled ? 1.0 : 0.5
        color: control.hovered && control.enabled ? UISettings.colorHighlight : UISettings.colorBg
        border.color: UISettings.colorLine
        border.width: control.hovered && control.enabled ? UISettings.doubleLine : UISettings.normalLine
        radius: UISettings.cornerRadius
    }

    Connections {
        target: root

        function onSizeChanged() {
            adjustSize()
        }
    }
}
