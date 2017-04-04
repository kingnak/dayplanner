import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
	property var dayData

//	id: root
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
			contentWidth: txt.width
			contentHeight: txt.height
			anchors.left: parent.left
			anchors.right: parent.right
			height: txt.height
			clip: true
			opacity: (dayData.sumFat > 0 || dayData.sumProtein > 0 || dayData.sumCarbs > 0 || dayData.sumCalories > 0 || dayData.workout.count > 0) ? 1 : 0
			Row {
				id: txt
				Text {
					//text: "F: " + utils.formatNumber(dayData.sumFat) + ", "
					text: baseStyle.formatSummary(utils.formatNumber(dayData.sumFat), "F", ", ");
					opacity: dayData.sumFat > 0 ? 1 : 0
					font: baseStyle.summaryFont
				}
				Text {
					//text: "KH: " + utils.formatNumber(dayData.sumCarbs) + ", "
					text: baseStyle.formatSummary(utils.formatNumber(dayData.sumCarbs), "KH", ", ");
					visible: dayData.sumCarbs > 0
					font: baseStyle.summaryFont
				}
				Text {
					//text: "EW: " + utils.formatNumber(dayData.sumProtein) + ", "
					text: baseStyle.formatSummary(utils.formatNumber(dayData.sumProtein), "EW", ", ");
					visible: dayData.sumProtein > 0
					font: baseStyle.summaryFont
				}
				Text {
					//text: "kcal: " + utils.formatNumber(dayData.sumCalories)
					text: baseStyle.formatSummary(utils.formatNumber(dayData.sumCalories), "kcal", "");
					visible: dayData.sumCalories > 0
					font: baseStyle.summaryFont
				}
				Text {
					//text: "kcal: " + utils.formatNumber(dayData.sumCalories)
					text: baseStyle.formatSummary(dayData.workout.count, "T", "");
					visible: dayData.workout.count > 0
					font: baseStyle.summaryFont
				}
			}
		}
	}
}
