import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import SortFilterProxyModel 0.2
import "styles"

SplitView {
	property var _data
	property var stats: _data.stats()
	id: root

	SortFilterProxyModel {
		id: sorter
		sourceModel: root._data
		filters: AllOf {
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
			RangeFilter {
				roleName: "carbs"
				minimumValue: carbsRange.first.value
				maximumValue: carbsRange.second.value
			}
			RangeFilter {
				roleName: "protein"
				minimumValue: proteinRange.first.value
				maximumValue: proteinRange.second.value
			}
			RangeFilter {
				roleName: "calories"
				minimumValue: caloriesRange.first.value
				maximumValue: caloriesRange.second.value
			}
		}
	}

	Column {
		Layout.minimumWidth: 200
		Text { text: "Fett"; font: baseStyle.headerFont }
		RangeSlider {
			id: fatRange
			from: stats.minFat
			to: stats.maxFat
			Component.onCompleted: setValues(stats.minFat, stats.maxFat)
		}
		Text { text: "Kohlenhydrate"; font: baseStyle.headerFont }
		RangeSlider {
			id: carbsRange
			from: stats.minCarbs
			to: stats.maxCarbs
			Component.onCompleted: setValues(stats.minCarbs, stats.maxCarbs)
		}
		Text { text: "Eiweiß"; font: baseStyle.headerFont }
		RangeSlider {
			id: proteinRange
			from: stats.minProtein
			to: stats.maxProtein
			Component.onCompleted: setValues(stats.minProtein, stats.maxProtein)
		}
		Text { text: "Kalorien"; font: baseStyle.headerFont }
		RangeSlider {
			id: caloriesRange
			from: stats.minCalories
			to: stats.maxCalories
			Component.onCompleted: setValues(stats.minCalories, stats.maxCalories)
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
/*
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
*/
}
