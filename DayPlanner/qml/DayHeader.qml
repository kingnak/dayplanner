import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
	property var dayData

	id: root
	height: cols.height//Math.max(dateText.height, shiftCombo.height)
	color: baseStyle.shiftColor(shiftsModel.shiftList[dayData.shiftIndex])

	ColumnLayout {
		id: cols
		width: parent.width

		RowLayout {
			width: parent.width
			spacing: 0

			Rectangle {
				Layout.fillWidth: true
				Layout.maximumWidth: 5
				Layout.preferredWidth: 0
			}

			Label {
				id: dateText
				font: baseStyle.headerFont
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

		Flickable {
			contentHeight: flw.height
			contentWidth: flw.width
			height: flw.height
			width: root.width
			clip: true
			Row {
				id: flw
				//width: root.width
				Text {
					text: "F: " + utils.formatNumber(dayData.sumFat) + ", "
					visible: dayData.sumFat > 0
				}
				Text {
					text: "EW: " + utils.formatNumber(dayData.sumProtein) + ", "
					visible: dayData.sumProtein > 0
				}
				Text {
					text: "KH: " + utils.formatNumber(dayData.sumCarbs) + ", "
					visible: dayData.sumCarbs > 0
				}
				Text {
					text: "kcal: " + utils.formatNumber(dayData.sumCalories)
					visible: dayData.sumCalories > 0
				}

			}
		}

	}
}
