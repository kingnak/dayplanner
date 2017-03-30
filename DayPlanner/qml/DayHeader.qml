import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
//	height: layout.height
	//width: parent.width
	height: Math.max(dateText.height, shiftCombo.height)
	color: shiftsModel.get(dayData.shiftIndex).color

	property var dayData
	RowLayout {
		//id: layout
		//anchors.fill: parent
		anchors.left: parent.left
		anchors.right: parent.right

	//	Rectangle {
	//		anchors.fill: parent
	//		color: shiftsModel.get(dayData.shiftIndex).color
	//	}

		Label {
			id: dateText
			text: dayData.date.getDate()
			Layout.alignment: Qt.AlignVCenter | Qt.AlignLeft
			Layout.fillWidth: true
		}

		ComboBox {
			id: shiftCombo
			model: shiftsModel
			Layout.alignment: Qt.AlignRight
			currentIndex: _data.shiftIndex
			onCurrentIndexChanged: dayData.shiftIndex = currentIndex
			style: ShiftComboStyle { }
		}
	}
}
