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
				implicitWidth: 24; implicitHeight: 24
				Image {
					source: "qrc:///icons/ingredient"
					anchors.fill: parent
				}

				onClicked: {
					stack.push(ingredientEditorStackView);
					gotoCalendar.visible = true;
					gotoTemplates.visible = false;
					gotoIngredients.visible = false;
				}
			}
			ToolButton {
				id: gotoTemplates
				style: SmallButtonStyle{}
				implicitWidth: 24; implicitHeight: 24
				Image {
					source: "qrc:///icons/recipe"
					anchors.fill: parent
				}
				onClicked: {
					stack.push(templateEditorStackView);
					gotoCalendar.visible = true;
					gotoTemplates.visible = false;
					gotoIngredients.visible = false;
				}
			}
			ToolButton {
				id: gotoCalendar
				style: SmallButtonStyle{square:false}
				text: "< zurück"
				visible: false
				onClicked: {
					stack.pop();
					gotoCalendar.visible = false;
					gotoTemplates.visible = true;
					gotoIngredients.visible = true;
				}
			}
		}
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

		BorderedContainer {
			property alias _data: theDay._data
			DayItem {
				anchors.fill: parent
				id: theDay
			}
			onBack: stack.pop();
		}
	}

	Component {
		id: ingredientEditorStackView
		ColumnLayout {
			IngredientList {
				_data: ingredientModel
				Layout.fillHeight: true
				Layout.fillWidth: true
			}
		}
	}

	Component {
		id: templateEditorStackView
		ColumnLayout {
			RecipeTemplateList {
				_data: recipeTemplateModel
				Layout.fillHeight: true
				Layout.fillWidth: true
			}
		}
	}
}
