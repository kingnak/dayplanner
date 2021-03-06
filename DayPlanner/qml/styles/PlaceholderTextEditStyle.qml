import QtQuick 2.5
import QtQuick.Controls.Styles 1.4

TextFieldStyle {
    id: textFieldStyle
    property string postfix
    property bool showHovered: true
	property alias textWidth: mtrcs.text

	TextMetrics {
		font: baseStyle.editorFont
		id: mtrcs
	}
    background: Rectangle {
        color: "transparent"
        width: control.width
        height: control.height
        implicitHeight: 20
		implicitWidth: postFixLabel.implicitWidth + (textWidth != "" ? mtrcs.width + 10 : 40)

		property color borderColor: baseStyle.controlBorderColor

        Text {
            id: postFixLabel
            anchors.right: parent.right
            text: postfix
            anchors.verticalCenter: parent.verticalCenter
            anchors.rightMargin: 5
			color: parent.borderColor
			font: baseStyle.editorFont
        }

        Rectangle {
			border.color: parent.borderColor
			color: "transparent"
			anchors.left: parent.left
			width: parent.width
			height: parent.height
			visible: showHovered
        }
    }
}
