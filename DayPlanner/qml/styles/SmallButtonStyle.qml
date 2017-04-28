import QtQuick 2.5
import QtQuick.Controls.Styles 1.1

ButtonStyle {
	property bool square: true
	background: Rectangle {
		implicitHeight: 10
		width: square ? height : width
		border.color: baseStyle.controlBorderColor
		color: "transparent"
		visible: control.hovered
	}
}
