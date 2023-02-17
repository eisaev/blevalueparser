import QtQuick 2.14
import QtQuick.Layouts 1.14


ColumnLayout {
    id: itemLayout

    Timer {
        id: timer
    }

    function adjustSize() {
        // Workaround: when software renderer is used, we get an outdated width/height/etc if we request it immediately
        runDelayed(timer, UISettings.adjustDelay, function() {
            width = parent.width
            parent.height = height
        })
    }

    Component.onCompleted: {
        adjustSize()
    }

    ListItemSeparator {}

    ListItemTitle {
        text: title
    }

    Connections {
        target: root

        function onSizeChanged() {
            itemLayout.adjustSize()
        }
    }
}
