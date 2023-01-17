import QtQuick 2.14
import QtQuick.Layouts 1.14


ColumnLayout {
    id: itemLayout
    width: parent.width

    function adjustSize() {
        parent.height = height
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
