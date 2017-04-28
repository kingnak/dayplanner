import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
	property var dayData
	property bool highlight: false

	height: cols.height
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

			Rectangle {
				width: dateMetrics.width
				height: width
				color: "transparent"

				TextMetrics {
					id: dateMetrics
					font: dateText.font
					text: "XX";
				}
				Canvas {
					anchors.fill: parent
					visible: highlight
					contextType: "2d"
					onPaint: {
						context.fillStyle = baseStyle.todayHighlightColor;
						context.ellipse(0,0,width,height);
						context.fill();
					}
				}

				Label {
					id: dateText
					font: baseStyle.headerFont
					text: dayData.date.getDate()
					anchors.centerIn: parent
				}
			}

			Label {
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
				spacing: 2
				id: txt
				Text {
					//text: "F: " + utils.formatDouble(dayData.sumFat) + ", "
					text: baseStyle.formatSummary(utils.formatDouble(dayData.sumFat), "F", ", ");
					visible: dayData.sumFat > 0
					font: baseStyle.summaryFont
					textFormat: Text.RichText
				}
				Text {
					//text: "KH: " + utils.formatDouble(dayData.sumCarbs) + ", "
					text: baseStyle.formatSummary(utils.formatDouble(dayData.sumCarbs), "KH", ", ");
					visible: dayData.sumCarbs > 0
					font: baseStyle.summaryFont
					textFormat: Text.RichText
				}
				Text {
					//text: "EW: " + utils.formatDouble(dayData.sumProtein) + ", "
					text: baseStyle.formatSummary(utils.formatDouble(dayData.sumProtein), "EW", ", ");
					visible: dayData.sumProtein > 0
					font: baseStyle.summaryFont
					textFormat: Text.RichText
				}
				Text {
					//text: "kcal: " + utils.formatDouble(dayData.sumCalories)
					text: baseStyle.formatSummary(utils.formatDouble(dayData.sumCalories), "kcal", ", ");
					visible: dayData.sumCalories > 0
					font: baseStyle.summaryFont
					textFormat: Text.RichText
				}
				Text {
					//text: "kcal: " + utils.formatDouble(dayData.sumCalories)
					text: baseStyle.formatSummary(dayData.workout.count, "T", "");
					opacity: dayData.workout.count > 0 ? 1 : 0
					font: baseStyle.summaryFont
					textFormat: Text.RichText
				}
			}
		}
	}
}
