import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
//import QtQuick.Controls 2.0 as C2
import "styles"

Rectangle {
    visible: styleData.visibleMonth
    enabled: styleData.visibleMonth

    property var _data

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
            layoutDirection: Qt.LeftToRight
            Layout.fillWidth: true
            height: Math.max(dateText.height, shiftCombo.height)

            Rectangle {
                anchors.fill: parent
                color: shiftsModel.get(_data.shiftIndex).color
            }

            Label {
                id: dateText
                text: _data.date.getDate()
                Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
                Layout.fillWidth: true
            }

            ComboBox {
                id: shiftCombo
                model: shiftsModel
                Layout.alignment: Qt.AlignRight
                currentIndex: _data.shiftIndex
                onCurrentIndexChanged: _data.shiftIndex = currentIndex
                style: ShiftComboStyle {}
            }
        }

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"
        }
    }
}
