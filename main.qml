import QtQuick 2.7
import QtQuick.Controls 1.5
import QtQuick.Controls.Styles 1.4
import "qml"
import org.kingnak.dayplanner 1.0

ApplicationWindow {

    DayModel {
        id: dayModel
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

    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")


    Calendar {
        id: calendar
        onVisibleMonthChanged: dayModel.clearCache(new Date(calendar.visibleYear, calendar.visibleMonth, 1))
        anchors.fill: parent
        style: CalendarStyle {
            dayDelegate: DayItem {
                _data: dayModel.dataForDate(styleData.date)
            }
        }
    }

/*
    DayItem {
        _data: dayModel.dataForDate(new Date())
        anchors.fill: parent
    }
*/

}
