import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls 2.0 as Q2
//import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
//import org.kingnak.dayplanner 1.0
//import "styles"

SplitView {
	property var _data
	id: root

	SortFilterProxyModel {
		id: sorter
		sourceModel: root._data
		filters:  AllOf {
			RegExpFilter {
				roleName: "name"
				pattern: searchText.text
				caseSensitivity: Qt.CaseInsensitive
			}
			RangeFilter {
				roleName: "fat"
				minimumValue: fatRange.first.value
				maximumValue: fatRange.second.value
			}
		}
	}

	Column {
		Layout.minimumWidth: 200
		Text { text: "Fett" }
		Q2.RangeSlider {
			id: fatRange
			from: 0
			to: 50
			second.value: 50
			first.onValueChanged: console.log("Fett: " + first.value + " - " + second.value)
			second.onValueChanged: console.log("Fett: " + first.value + " - " + second.value)
		}
	}

	Item {
		width: Layout.preferredWidth
		Layout.minimumWidth: 150
		Layout.preferredWidth: 160+200
		Layout.fillHeight: true
		height: parent.height
		TextField {
			id: searchText
			width: parent.width
			anchors.top: parent.top
		}
		TableView {
			width:parent.width
			Layout.fillHeight: true
			anchors.top: searchText.bottom
			anchors.bottom: parent.bottom

			id: table
			model: sorter
			TableViewColumn {
				role: "name"
				title: "Name"
			}
			TableViewColumn {
				role: "fat"
				title: "Fett"
				width: 40
				delegate: doubleDelegate
			}
			TableViewColumn {
				role: "protein"
				title: "EW"
				width: 40
				delegate: doubleDelegate
			}
			TableViewColumn {
				role: "carbs"
				title: "KH"
				width: 40
				delegate: doubleDelegate
			}
			TableViewColumn {
				role: "calories"
				title: "kcal"
				width: 40
				delegate: doubleDelegate
			}
			Component {
				id: doubleDelegate
				Text {
					text: utils.formatNumber(styleData.value)
					color: styleData.textColor
					elide: styleData.elideMode
					horizontalAlignment: Text.AlignRight
				}
			}
		}
	}

	Grid {
		id: editor
		property var obj: recipeModel.loadDataForRecipe(sorter.get(table.currentRow).itemId)
		Layout.fillWidth: true
		Layout.fillHeight: true
		columns: 2
		Label { text: "Name" }
		TextField { text: editor.obj.name }
		Label { text: "Menge" }
		DoubleField { text: editor.obj.quantity }
	}

}
