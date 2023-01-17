import QtQuick 2.14
import QtQuick.Layouts 1.14


Rectangle {
    Layout.fillWidth: true
    Layout.fillHeight: true
    color: UISettings.colorBgAlt
    opacity: enabled ? 1.0 : 0.5
    border.color: UISettings.colorLine
    border.width: UISettings.normalLine
    radius: UISettings.cornerRadius
    clip: true
}
