pragma Singleton

import QtQuick 2.14


Item {
    property int appHeight
    property int appWidth

    readonly property color colorBg: "#ffffff"
    readonly property color colorBgAlt: Qt.darker(UISettings.colorBg, 1.03)

    readonly property color colorText: "#202020"
    readonly property color colorTextAlt: Qt.lighter(UISettings.colorText, 3.0)
    readonly property color colorSeparator: "#abbdd0"
    readonly property color colorHighlight: Qt.lighter(UISettings.colorSeparator, 1.3)
    readonly property color colorLine: "#6610cc"

    readonly property real fontSizeNormal: (appWidth + appHeight) * 0.015
    readonly property real fontSizeSmall: fontSizeNormal / 1.3
    readonly property real fontSizeHeader2: fontSizeNormal * 1.3
    readonly property real fontSizeHeader1: fontSizeHeader2 * 1.3

    readonly property real doubleSpacer: fontSizeNormal
    readonly property real normalSpacer: doubleSpacer / 2.0
    readonly property real halfSpacer: normalSpacer / 2.0

    readonly property real cornerRadius: fontSizeNormal / 4.0

    readonly property int normalLine: fontSizeNormal / 10.0
    readonly property int doubleLine: normalLine * 2

    readonly property int adjustDelay: 0
}
