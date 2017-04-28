import QtQuick 2.5
import QtQuick.Layouts 1.1

Column {
	property var mealData

	Rectangle {
		width: parent.width
		height: Math.max(flw.height*1.2, flw.height+6);
		color: baseStyle.mealColorLight(mealData.type)

		Flow {
			id: flw
			width: parent.width
			anchors.verticalCenter: parent.verticalCenter
			Text {
				font: baseStyle.defaultFont
				text: utils.mealName(mealData.type) + ": "
			}
			Text {
				font: baseStyle.defaultFont
				text: "F: " + utils.formatDouble(mealData.sumFat) + ", "
			}
			Text {
				font: baseStyle.defaultFont
				text: "KH: " + utils.formatDouble(mealData.sumCarbs) + ", "
			}
			Text {
				font: baseStyle.defaultFont
				text: "EW: " + utils.formatDouble(mealData.sumProtein) + ", "
			}
			Text {
				font: baseStyle.defaultFont
				text: "kcal: " + utils.formatDouble(mealData.sumCalories)
			}

		}
	}
}
