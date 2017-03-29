import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import QtQuick.Layouts 1.1
import "qml"
import org.kingnak.dayplanner 1.0


ApplicationWindow {
    id: root

    property bool useSingleDayView: true
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
