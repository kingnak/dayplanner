import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

Item {
	id: root

	function applyName() {
		name = txtName.text
	}

	property var addMenu
	property bool addMenuEnabled: false

	signal removeItem(int idx)

	height: rect.height
	width: parent.width
	Rectangle {
		id: rect
		width: parent.width
		height: row.height

		MouseArea {
			anchors.fill: parent
			hoverEnabled: true
			id: mouseArea
		}

		RowLayout {
			id: row
			property bool hovered: mouseArea.containsMouse || txtName.hovered || txtFat.hovered || txtProtein.hovered || txtCarbs.hovered || txtCalories.hovered
			width: parent.width

			ToolButton {
				text: "X"
				tooltip: "Löschen"
				onClicked: root.removeItem(index)
				style: SmallButtonStyle {}
			}

			ToolButton {
				text: "+"
				menu: addMenu
				style: SmallButtonStyle {}
				opacity: addMenuEnabled ? 1 : 0
				enabled: addMenuEnabled
			}

			TextField {
				id: txtName
				Layout.fillWidth: true
				text: name
				onEditingFinished: name = text
				font: baseStyle.editorFont
				style: PlaceholderTextEditStyle {
					showHovered: row.hovered
				}
			}

			DoubleField {
				id: txtFactor
				value: factor
				font: baseStyle.editorFont
				style: PlaceholderTextEditStyle {
					showHovered: row.hovered
					postfix: "x"
				}
				onDoubleFinished: factor = val;
				onDoubleError: value = factor;
			}

			DoubleField {
				id: txtFat
				value: calcFat
				font: baseStyle.editorFont
				style: PlaceholderTextEditStyle {
					showHovered: row.hovered
					postfix: "F"
				}
				onDoubleFinished: calcFat = val;
				onDoubleError: value = calcFat;
			}

			DoubleField {
				id: txtCarbs
				value: calcCarbs
				font: baseStyle.editorFont
				style: PlaceholderTextEditStyle {
					postfix: "KH"
					showHovered: row.hovered
				}
				onDoubleFinished: calcCarbs = val;
				onDoubleError: value = calcCarbs;
			}


			DoubleField {
				id: txtProtein
				value: calcProtein
				font: baseStyle.editorFont
				style: PlaceholderTextEditStyle {
					postfix: "EW"
					showHovered: row.hovered
				}
				onDoubleFinished: calcProtein = val;
				onDoubleError: value = calcProtein;
			}

			DoubleField {
				id: txtCalories
				value: calcCalories
				font: baseStyle.editorFont
				style: PlaceholderTextEditStyle {
					postfix: "kcal"
					showHovered: row.hovered
				}
				onDoubleFinished: calcCalories = val;
				onDoubleError: value = calcCalories;
			}

		}
	}
}
