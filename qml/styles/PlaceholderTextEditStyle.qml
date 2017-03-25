import QtQuick 2.5
import QtQuick.Controls.Styles 1.4

TextFieldStyle {
    id: textFieldStyle
    property string decoratorString
    property bool showHovered: true

    background: Rectangle {
        color: "transparent"
        width: control.width
        height: control.height
        implicitHeight: 20
        implicitWidth: 40

        readonly property color _borderColor: "#C0C0C0"

        Rectangle {
            color: _borderColor; anchors.left: parent.left; width: 1; height: parent.height; visible: showHovered
        }
        Rectangle {
            color: _borderColor; anchors.right: parent.right; width: 1; height: parent.height; visible: showHovered
        }
        Rectangle {
            color: _borderColor; anchors.top: parent.top; height: 1; width: parent.width; visible: showHovered
        }
        Rectangle {
            color: _borderColor; anchors.bottom: parent.bottom; height: 1; width: parent.width; visible: showHovered
        }
    }
}
