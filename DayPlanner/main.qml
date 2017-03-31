import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "qml"
import "qml/styles"
import org.kingnak.dayplanner 1.0


ApplicationWindow {
    id: root

    visible: true
	width: 640
    height: 480
    title: qsTr("Hello World")

    DayModel {
        id: dayModel
    }

    RecipeModel {
        id: recipeModel
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
			default: return "Anderes";
			}
		}
		function mealColor(mealType) {
			return baseStyle.mealColor(mealType);
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

		ColumnLayout {
			property alias _data: theDay._data

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
    }
}
