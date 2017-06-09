import QtQuick 2.0
import QtQuick.Controls.Styles 1.4
import QtGraphicalEffects 1.0

MenuStyle {
	id: root
	property bool showIcons: true
	property int iconSize: 16

	itemDelegate.label: Row {
		Item {
			visible: root.showIcons && root.iconSize > 0
			width: root.iconSize + 2 // padding
			height: root.iconSize
			anchors.verticalCenter: parent.verticalCenter
			Image {
				id: img
				source: styleData.iconSource
				visible: false
				sourceSize: Qt.size(root.iconSize,root.iconSize)
			}
			Desaturate {
				anchors.fill: img;
				source: img;
				desaturation: styleData.enabled ? 0 : 0.8
			}
		}
		Text {
			text: styleData.text;
			color: styleData.enabled ? "#000" : baseStyle.disabledColor;
			anchors.verticalCenter: parent.verticalCenter
		}
	}
}
