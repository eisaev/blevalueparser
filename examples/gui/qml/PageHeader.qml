import QtQuick 2.14
import QtQuick.Layouts 1.14


Text {
    Layout.fillWidth: true
    width: parent.width
    horizontalAlignment: Qt.AlignCenter
    font.pixelSize: UISettings.fontSizeHeader1
    color: UISettings.colorText
    text: "<Unknown>"

    property bool backAsExit: false

    CustomButton {
        text: backAsExit ? "⨯" : "←"
        square: true
        onClicked: goBack()
    }
}
