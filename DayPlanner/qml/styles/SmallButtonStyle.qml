import QtQuick 2.5
import QtQuick.Controls.Styles 1.1

ButtonStyle {
	background: Rectangle {
		implicitHeight: 10
		border.color: baseStyle.controlBorderColor
		color: "transparent"
		visible: control.hovered
	}
}
