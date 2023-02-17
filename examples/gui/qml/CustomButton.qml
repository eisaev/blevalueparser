import QtQuick 2.14
import QtQuick.Layouts 1.14
import QtQuick.Controls 2.14


Button {
    id: control
    text: qsTr("Button")
    font.pixelSize: UISettings.fontSizeNormal

    property bool square: false

    Timer {
        id: timer
    }

    function setHighlighted(highlighted) {
        if (highlighted) {
            if (control.enabled) {
                bg.color = UISettings.colorHighlight
                bg.border.width = UISettings.doubleLine
            }
        } else {
            bg.color = UISettings.colorBg
            bg.border.width = UISettings.normalLine
        }
    }

    function adjustSize() {
        // Workaround: when software renderer is used, we get an outdated width/height/etc if we request it immediately
        runDelayed(timer, UISettings.adjustDelay, function() {
            if (square) {
                padding = UISettings.halfSpacer
                implicitWidth = implicitHeight
            } else {
                verticalPadding = UISettings.normalSpacer
                horizontalPadding = UISettings.doubleSpacer
            }
            setHighlighted(hovered)
        })
    }

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        onClicked: {
            control.clicked()
        }

        onEntered: {
            setHighlighted(true)
        }

        onExited: {
            setHighlighted(false)
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
        id: bg
        opacity: enabled ? 1.0 : 0.5
        color: UISettings.colorBg
        border.color: UISettings.colorLine
        border.width: UISettings.normalLine
        radius: UISettings.cornerRadius
    }

    Connections {
        target: root

        function onSizeChanged() {
            adjustSize()
        }
    }
}
