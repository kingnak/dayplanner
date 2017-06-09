import QtQuick 2.5
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0

ButtonStyle {
	property bool square: true
	property int iconSize: 16
	property bool borderAlwaysVisible: false
	background: Rectangle {
		implicitHeight: 10
		width: square ? height : width
		border.color: baseStyle.controlBorderColor
		color: control.pressed ? "#20000000" : ( borderAlwaysVisible && control.hovered ? "#10000000" : "transparent" )
		visible: borderAlwaysVisible || control.hovered
	}
	label: Row {
		Item {
			width: img.width; height: img.height
			Image {
				id: img
				source: control.iconSource
				sourceSize: Qt.size(iconSize, iconSize)
			}
			Desaturate {
				anchors.fill: img
				source: img
				visible: iconSize > 0 && control.iconSource !== ""
				desaturation: control.enabled ? 0 : 0.8
			}
		}
		Text {
			text: control.text
			color: control.enabled ? "#000" : baseStyle.disabledColor
		}
	}
}
