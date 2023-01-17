import QtQuick 2.14
import QtQuick.Controls 2.14


ListView {
    anchors.fill: parent
    anchors.margins: UISettings.normalSpacer
    clip: true

    ScrollBar.vertical: ScrollBar {
        policy: ScrollBar.AlwaysOn
        active: ScrollBar.AsNeeded
    }
}
