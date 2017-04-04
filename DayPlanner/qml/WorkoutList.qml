import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import org.kingnak.dayplanner 1.0
import "styles"

ListView {
	id: root
	clip: true
	implicitHeight: 100

	property var _data

	model: _data.items

	delegate: workoutItem

	header: headerBanner
	headerPositioning: ListView.OverlayHeader
	footer: footerEditor
	footerPositioning: _data.isEmpty ? ListView.InlineFooter : ListView.OverlayFooter

	Component {
		id: workoutItem

		Rectangle {
			width: parent.width
			height: row.height

			MouseArea {
				anchors.fill: parent
				hoverEnabled: true
				id: mouseArea
			}

			RowLayout {
				id: row
				property bool hovered: mouseArea.containsMouse || txtName.hovered || txtInfo.hovered
				width: parent.width

				ToolButton {
					text: "X"
					onClicked: _data.removeWorkout(index)
				}

				TextField {
					id: txtName
					Layout.fillWidth: true
					text: name
					font: baseStyle.editorFont
					style: PlaceholderTextEditStyle {
						showHovered: row.hovered
					}
				}

				TextField {
					id: txtInfo
					Layout.fillWidth: true
					text: info
					font: baseStyle.editorFont
					style: PlaceholderTextEditStyle {
						showHovered: row.hovered
					}
				}
			}
		}
	}

	Component {
		id: footerEditor
		Rectangle {
			z: 2
			color: "lightGrey";
			width: parent.width
			height: inp.height

			FilterTextInput {
				width: parent.width
				id: inp
				textRole: "name"
				model: trainingModel
				onAccepted: {
					if (selectedItem)
						_data.createWorkoutForTraining(selectedItem.itemId);
					else
						_data.createWorkout(text);
					text = "";
					focus = true;
					root.positionViewAtEnd();
				}
			}
		}
	}

	Component {
		id: headerBanner
		Rectangle {
			z: 2
			width: parent.width
			height: Math.max(txt.height*1.2, txt.height+6)

			color: baseStyle.trainingColor

			RowLayout {
				width: parent.width
				anchors.verticalCenter: parent.verticalCenter
				Text {
					Layout.fillWidth: true
					font: baseStyle.headerFont
					color: baseStyle.trainingFontColor
					id: txt
					text: "Training"
				}
			}
		}
	}
}
