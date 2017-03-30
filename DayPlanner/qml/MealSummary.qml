import QtQuick 2.5
import QtQuick.Layouts 1.1

Column {
	property var mealData
	//anchors.left: parent.left
	//anchors.right: parent.right

	Rectangle {
		id: head
		width: parent.width
		height: txt.height
		color: utils.mealColor(mealData.type)
		Text {
			id: txt
			text: utils.mealName(mealData.type)
		}
	}

	Flow {
		id: flw
		width: parent.width
		Text {
			text: "F: " + utils.formatNumber(mealData.sumFat) + ", "
		}
		Text {
			text: "EW: " + utils.formatNumber(mealData.sumProtein) + ", "
		}
		Text {
			text: "KH: " + utils.formatNumber(mealData.sumCarbs) + ", "
		}
		Text {
			text: "kcal: " + utils.formatNumber(mealData.sumCalories)
		}

	}
}
