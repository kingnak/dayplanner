import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
    property var _data
    id: root

    ColumnLayout {
        anchors.fill: parent

        RowLayout {
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
                style: ShiftComboStyle { }
            }
        }

        MealList {
            id: breakfast
            Layout.fillWidth: true
            _data: root._data.breakfast
        }

        MealList {
            id: lunch
            Layout.fillWidth: true
			_data: root._data.lunch
        }

		MealList {
			id: dinner
			Layout.fillWidth: true
			_data: root._data.dinner
		}

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "green"
        }
    }
}
