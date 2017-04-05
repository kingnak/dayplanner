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
	footerPositioning: _data.isEmpty ? ListView.InlineFooter : ListView.OverlayFooter

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
                    onClicked: _data.removeMeal(index)
					style: SmallButtonStyle {}
                }

                TextField {
                    id: txtName
                    Layout.fillWidth: true
                    text: name
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

    Component {
        id: footerEditor
		Rectangle {
			z: 2
			color: "lightGrey";
			width: parent.width
			height: inp.height

			FilterTextInput {
				width: parent.width
				id: inp
				textRole: "name"
				model: recipeModel
				font: baseStyle.editorFont
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
			height: Math.max(txt.height*1.2, txt.height+6)

			color: baseStyle.mealColor(_data.type)

			RowLayout {
				width: parent.width
				anchors.verticalCenter: parent.verticalCenter
				Text {
					Layout.fillWidth: true
					font: baseStyle.headerFont
					id: txt
					text: utils.mealName(_data.type)
				}
				Text {
					font: baseStyle.defaultFont
					text: "\u03A3 " + utils.formatNumber(_data.sumFat);
					Layout.minimumWidth: 40 + metrics.boundingRect("F").width
				}
				Text {
					font: baseStyle.defaultFont
					text: "\u03A3 " + utils.formatNumber(_data.sumCarbs);
					Layout.minimumWidth: 40 + metrics.boundingRect("KH").width
				}
				Text {
					font: baseStyle.defaultFont
					text: "\u03A3 " + utils.formatNumber(_data.sumProtein);
					Layout.minimumWidth: 40 + metrics.boundingRect("EW").width
				}
				Text {
					font: baseStyle.defaultFont
					text: "\u03A3 " + utils.formatNumber(_data.sumCalories);
					Layout.minimumWidth: 40 + metrics.boundingRect("kcal \u03A3").width
				}
			}
			FontMetrics {
				id: metrics
				font: baseStyle.editorFont
			}
		}
	}
}
