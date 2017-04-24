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
	width: 800
	height: 600
	title: qsTr("Day Planner")

	toolBar: ToolBar {
		style: ToolBarStyle {
			padding.top: 0
		}
		height: 24
		RowLayout {
			anchors.fill: parent
			Item {
				Layout.fillWidth: true
			}

			ToolButton {
				id: gotoIngredients
				style: SmallButtonStyle{}
				iconSource: "qrc:///icons/ingredients"
				onClicked: {
					stack.pop({item: calendar, immediate:true});
					stack.push({item: ingredientEditorStackView, replace: true});
					gotoCalendar.enabled = true;
					gotoCalendar.visible = true;
					gotoIngredients.enabled = false;
					gotoIngredients.visible = false;
				}
			}
			ToolButton {
				id: gotoCalendar
				style: SmallButtonStyle{}
				iconSource: "qrc:///icons/calendar"
				enabled: false
				visible: false
				onClicked: {
					stack.pop({item: ingredientEditorStackView, immediate:true});
					stack.push({item: calendar, replace: true});
					gotoCalendar.enabled = false;
					gotoCalendar.visible = false;
					gotoIngredients.enabled = true;
					gotoIngredients.visible = true;
				}
			}
		}
	}

    DayModel {
        id: dayModel
    }

    IngredientModel {
        id: ingredientModel
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

	Component {
		id: ingredientEditorStackView
		ColumnLayout {
			//anchors.fill: parent

			IngredientList {
				_data: ingredientModel
				Layout.fillHeight: true
				Layout.fillWidth: true
			}
		}
	}
}
