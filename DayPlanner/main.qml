import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "qml"
import "qml/styles"
import org.kingnak.dayplanner 1.0
import SortFilterProxyModel 0.2


ApplicationWindow {
    id: root

    visible: true
	width: 640
    height: 480
	title: qsTr("Day Planner")

    DayModel {
        id: dayModel
    }

    RecipeModel {
        id: recipeModel
	}

	TrainingModel {
		id: trainingModel
	}

	BaseStyle {
		id: baseStyle
	}

	Utils {
		id: utils
		function mealName(mealType) {
			switch (mealType) {
			case Meal.Breakfast: return "Frühstück";
			case Meal.Lunch: return "Mittag";
			case Meal.Dinner: return "Abend";
			case Meal.Snacks: return "Snacks";
			default: return "Anderes";
			}
		}
	}

	ShiftModel {
		id: shiftsModel
	}


	// Recipe Editor Test
	ColumnLayout {
		anchors.fill: parent

		RecipeList {
			_data: recipeModel
			Layout.fillHeight: true
			Layout.fillWidth: true
		}
	}

	/*
	StackView {
		id: stack
		initialItem: calendar
		anchors.fill: parent
	}

    Component {
        id: calendar

        Calendar {
            onVisibleMonthChanged: dayModel.clearCache(new Date(calendar.visibleYear, calendar.visibleMonth, 1))
            style: CalendarStyle {
				dayDelegate: DaySummary {
					highlight: styleData.today
                    _data: dayModel.dataForDate(styleData.date)
					opacity: styleData.visibleMonth ? 1 : 0
                    enabled: styleData.visibleMonth
					onOpenDay: {
						stack.push({item: singleDayView, properties: {_data:dayModel.dataForDate(d)}});
					}
                }
            }
        }
    }

    Component {
		id: singleDayView

		GridLayout {
			property alias _data: theDay._data
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
						text: "< zurück"
						onClicked: stack.pop();
					}
					Rectangle {
						Layout.fillWidth: true
						color: "transparent"
					}
				}

				DayItem {
					anchors.left: parent.left
					anchors.right: parent.right
					id: theDay
					Layout.fillHeight: true
				}
			}

			Rectangle { Layout.fillWidth: true; Layout.minimumWidth: 0 }
			Rectangle { Layout.fillHeight: true; Layout.columnSpan: 3; Layout.minimumHeight: 5 }
		}
	}
	*/
}
