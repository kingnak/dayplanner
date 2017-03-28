import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import "qml"
import org.kingnak.dayplanner 1.0

ApplicationWindow {
    id: root

    property bool useSingleDayView: true

    DayModel {
        id: dayModel
    }

    RecipeModel {
        id: recipeModel
    }

    ListModel {
        id: shiftsModel
        ListElement { text: ""; color: "transparent" }
        ListElement { text: "0"; color: "red" }
        ListElement { text: "X"; color: "green" }
        ListElement { text: "A1"; color: "blue" }
        ListElement { text: "A2"; color: "yellow" }
        ListElement { text: "N1"; color: "cyan" }
        ListElement { text: "N2"; color: "magenta" }
    }
    Item {
        id: mealList
        property int type: 1
        property int fatSum: 5
        property int proteinSum: 9
        property int carbSum: 4
        property int calorieSum: 500
        property var items: ListModel {
            ListElement {
                name: "Müsli"
                factor: 1
                calcFat: 2
                calcProtein: 3
                calcCarb: 2
                calcCalorie: 200
            }
            ListElement {
                name: "Banane"
                factor: 1
                calcFat: 3
                calcProtein: 6
                calcCarb: 2
                calcCalorie: 300
            }
        }
    }

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Loader {
        anchors.fill: parent
        sourceComponent: root.useSingleDayView ? singeDayView : calendar
    }

    Component {
        id: calendar

        Calendar {
            onVisibleMonthChanged: dayModel.clearCache(new Date(calendar.visibleYear, calendar.visibleMonth, 1))
            anchors.fill: parent
            style: CalendarStyle {
                dayDelegate: DayItem {
                    _data: dayModel.dataForDate(styleData.date)
                    visible: styleData.visibleMonth
                    enabled: styleData.visibleMonth
                }
            }
        }
    }

    Component {
        id: singeDayView

        DayItem {
            _data: dayModel.dataForDate(new Date())
            anchors.fill: parent
        }
    }

}