import QtQuick 2.14


Rectangle {
    color: index === 0 ? "transparent" : UISettings.colorSeparator

    Timer {
        id: timer
    }

    function adjustSize() {
        // Workaround: when software renderer is used, we get an outdated width/height/etc if we request it immediately
        runDelayed(timer, UISettings.adjustDelay, function() {
            implicitWidth = parent.width
            implicitHeight = UISettings.normalLine
        })
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
