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

			color: utils.mealColor(_data.type)

			RowLayout {
				width: parent.width
				Text {
					Layout.fillWidth: true
					id: txt
					text: utils.mealName(_data.type)
				}
				Text {
					text: "\u03A3 " + utils.formatNumber(_data.sumFat);
					Layout.minimumWidth: 40 + metrics.boundingRect("F").width
				}
				Text {
					text: "\u03A3 " + utils.formatNumber(_data.sumProtein);
					Layout.minimumWidth: 40 + metrics.boundingRect("EW").width
				}
				Text {
					text: "\u03A3 " + utils.formatNumber(_data.sumCarbs);
					Layout.minimumWidth: 40 + metrics.boundingRect("KH").width
				}
				Text {
					text: "\u03A3 " + utils.formatNumber(_data.sumCalories);
					Layout.minimumWidth: 40 + metrics.boundingRect("kcal \u03A3").width
				}
			}
			FontMetrics {
				id: metrics
			}
		}
	}
}
