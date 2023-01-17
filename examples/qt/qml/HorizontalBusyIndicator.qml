import QtQuick 2.14


Item {
    id: control

    property bool running: false
    property color color: UISettings.colorLine

    function adjustSize() {
        implicitHeight = UISettings.doubleLine
        busyAnimation.restart()
    }

    Component.onCompleted: {
        adjustSize()
    }

    Rectangle {
        id: busyRect
        width: parent.width / 5
        height: parent.height
        color: control.color
        visible: control.running

        property real middle: width * 2
        property real end: width * 4

        SequentialAnimation {
            id: busyAnimation
            loops: Animation.Infinite
            running: control.running

            XAnimator {
                target: busyRect
                from: 0
                to: busyRect.middle
                easing.type: Easing.InCubic
                duration: 500
            }

            XAnimator {
                target: busyRect
                from: busyRect.middle
                to: busyRect.end
                easing.type: Easing.OutCubic
                duration: 500
            }

            XAnimator {
                target: busyRect
                from: busyRect.end
                to: busyRect.middle
                easing.type: Easing.InCubic
                duration: 500
            }

            XAnimator {
                target: busyRect
                from: busyRect.middle
                to: 0
                easing.type: Easing.OutCubic
                duration: 500
            }
        }
    }

    Connections {
        target: root

        function onSizeChanged() {
            adjustSize()
        }
    }
}
