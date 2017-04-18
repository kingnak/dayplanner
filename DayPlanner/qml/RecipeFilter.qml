import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import SortFilterProxyModel 0.2
import "styles"

SplitView {
	property alias model: sorter.sourceModel

	id: theList
	signal deleteRecipe(int id)
	signal editRecipe(int id)

	SortFilterProxyModel {
		id: sorter
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
				role: "itemId"
				delegate: editDelegate
			}

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
				id: editDelegate
				Row {
					spacing: 0
					ToolButton {
						style: SmallButtonStyle{}
						text: "X"
						onClicked: theList.deleteRecipe(styleData.value)
					}
					ToolButton {
						style: SmallButtonStyle{}
						text: "E"
						onClicked: theList.editRecipe(styleData.value)
					}
				}
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
}
