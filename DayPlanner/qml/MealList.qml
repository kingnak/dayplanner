import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

ListView {
    id: root
    clip: true
    implicitHeight: 100

    property var _data

    model: _data.items

    delegate: mealItem

    header: headerBanner
    headerPositioning: ListView.OverlayHeader
    footer: footerEditor
    footerPositioning: ListView.InlineFooter

    Component {
        id: mealItem

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
                property bool hovered: mouseArea.containsMouse || txtName.hovered || txtFat.hovered || txtProtein.hovered || txtCarbs.hovered || txtCalories.hovered
                width: parent.width

                ToolButton {
                    text: "X"
                    //width: 20
                    onClicked: _data.removeMeal(index)
                }

                TextField {
                    id: txtName
                    Layout.fillWidth: true
                    text: name
                    style: PlaceholderTextEditStyle {
                        showHovered: row.hovered
                    }
                }

                DoubleField {
                    id: txtFactor
                    value: factor
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
                    style: PlaceholderTextEditStyle {
                        showHovered: row.hovered
                        postfix: "F"
                    }
                    onDoubleFinished: calcFat = val;
                    onDoubleError: value = calcFat;
                }

                DoubleField {
                    id: txtProtein
                    value: calcProtein
                    style: PlaceholderTextEditStyle {
                        postfix: "EW"
                        showHovered: row.hovered
                    }
                    onDoubleFinished: calcProtein = val;
                    onDoubleError: value = calcProtein;
                }

                DoubleField {
                    id: txtCarbs
                    value: calcCarbs
                    style: PlaceholderTextEditStyle {
                        postfix: "KH"
                        showHovered: row.hovered
                    }
                    onDoubleFinished: calcCarbs = val;
                    onDoubleError: value = calcCarbs;
                }

                DoubleField {
                    id: txtCalories
                    value: calcCalories
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

    Component {
        id: footerEditor
        Rectangle {
            color: "lightGrey";
            width: parent.width
            height: inp.height

            FilterTextInput {
                width: parent.width
                id: inp
                textRole: "name"
                model: recipeModel
                onAccepted: {
                    if (selectedItem)
                        _data.createMealForRecipe(selectedItem.itemId);
                    else
                        _data.createMeal(text);
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
            height: txt.height

            color: {
                var c = "transparent";
                switch (_data.type) {
                case Meal.Breakfast:
				default:
                    c = "grey";
                }
                c;
            }

            Text {
                id: txt
                text: {
                    switch (_data.type) {
					case Meal.Breakfast: return "Frühstück";
					case Meal.Lunch: return "Mittag";
					case Meal.Dinner: return "Abend";
					default: return "Anderes";
                    }
                }
            }

        }
    }
}
