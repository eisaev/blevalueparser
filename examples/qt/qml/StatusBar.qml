import QtQuick 2.14
import dev.eisaev.blemanager 1.0


Text {
    font.pixelSize: UISettings.fontSizeSmall
    font.italic: true
    color: UISettings.colorTextAlt
    text: BLEManagerSingleton.statusString
}
