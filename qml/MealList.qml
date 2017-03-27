import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
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

                TextField {
                    id: txtName
                    Layout.fillWidth: true
                    text: name
                    style: PlaceholderTextEditStyle {
                        showHovered: row.hovered
                    }
                }

                TextField {
                    id: txtFat
                    text: calcFat
                    style: PlaceholderTextEditStyle {
                        showHovered: row.hovered
                        postfix: "F"
                    }
                    onEditingFinished: fat = text
                }

                TextField {
                    id: txtProtein
                    text: calcProtein
                    style: PlaceholderTextEditStyle {
                        postfix: "EW"
                        showHovered: row.hovered
                    }
                    onEditingFinished: protein = text
                }

                TextField {
                    id: txtCarbs
                    text: calcCarbs
                    style: PlaceholderTextEditStyle {
                        postfix: "KH"
                        showHovered: row.hovered
                    }
                    onEditingFinished: carbs = text
                }

                TextField {
                    id: txtCalories
                    text: calcCalories
                    style: PlaceholderTextEditStyle {
                        postfix: "kcal"
                        showHovered: row.hovered
                    }
                    onEditingFinished: calories = text
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


            TextField {
                width: parent.width
                id: inp
                onAccepted: {
                    _data.createMeal(text);
                    text = "";
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
                    c = "grey";
                }
                c;
            }

            Text {
                id: txt
                text: {
                    var t = "";
                    switch (_data.type) {
                    case Meal.Breakfast:
                        t = "Frühstück";
                    }
                    t;
                }
            }

        }
    }
}
