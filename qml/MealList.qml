import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import org.kingnak.dayplanner 1.0
import "styles"

ListView {
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
        RowLayout {
            /*
            id: row
            property bool hovered: index == currentIndex

            MouseArea {
                anchors.fill: parent
                //onEntered: row.hovered = index == currentIndex
                //onExited: row.hovered = containsMouse
                //onEntered: currentIndex = index
                //onExited: if (currentIndex == index) currentIndex = -1
                hoverEnabled: true
            }
            */
            width: parent.width
            TextField {
                Layout.fillWidth: true
                text: name
                style: PlaceholderTextEditStyle {
                    showHovered: true//row.hovered
                }
            }
            TextField {
                text: calcFat
                placeholderText: "Fett"
                style: PlaceholderTextEditStyle {
                    showHovered: true//row.hovered
                }
            }
            //Text { text: calcProtein + "EW" }
            //Text { text: calcCarb + "KH" }
            //Text { text: calcCalorie + "kcal" }
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
