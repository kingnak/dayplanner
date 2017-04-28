import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import "styles"

GridLayout {
	default property alias content: inner_space.data

	signal back()
	property alias backVisible: backBtn.visible
	property bool backEnabled: backBtn.enabled

	columns: 3
	rowSpacing: 0
	columnSpacing: 0


	Rectangle { Layout.fillWidth: true; Layout.minimumWidth: 0 }

	ColumnLayout {
		spacing: 0
		Layout.minimumWidth: 400
		Layout.preferredWidth: 450
		Layout.maximumWidth: 650
		Layout.minimumHeight: 400
		Layout.preferredHeight: 600

		RowLayout {
			anchors.left: parent.left
			anchors.right: parent.right

			ToolButton {
				id: backBtn
				style: SmallButtonStyle{square:false}
				text: "< zurück"
				onClicked: back()
			}
			Rectangle {
				Layout.fillWidth: true
				color: "transparent"
			}
		}

		Item {
			id: inner_space
			Layout.fillHeight: true
			anchors.left: parent.left
			anchors.right: parent.right
		}
	}

	Rectangle { Layout.fillWidth: true; Layout.minimumWidth: 0 }
	Rectangle { Layout.fillHeight: true; Layout.columnSpan: 3; Layout.minimumHeight: 5 }
}
