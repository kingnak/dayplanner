import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
//	height: layout.height
	//width: parent.width
	height: Math.max(dateText.height, shiftCombo.height)
	color: baseStyle.shiftColor(shiftsModel.shiftList[dayData.shiftIndex])

	property var dayData
	RowLayout {
		anchors.left: parent.left
		anchors.right: parent.right

		Label {
			id: dateText
			text: dayData.date.getDate()
			Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
			Layout.fillWidth: true
		}

		ComboBox {
			id: shiftCombo
			model: shiftsModel.shiftList
			Layout.alignment: Qt.AlignRight
			currentIndex: dayData.shiftIndex
			onCurrentIndexChanged: dayData.shiftIndex = currentIndex
			style: ShiftComboStyle { }
		}
	}
}
