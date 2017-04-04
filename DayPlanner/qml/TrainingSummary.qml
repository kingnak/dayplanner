import QtQuick 2.5
import QtQuick.Layouts 1.1
import "styles"

Column {
	property var workoutData

	Rectangle {
		width: parent.width
		height: Math.max(flw.height*1.2, flw.height+6)
		color: baseStyle.trainingColor

		Flow {
			id: flw
			width: parent.width
			anchors.verticalCenter: parent.verticalCenter
			Repeater {
				model: workoutData.items
				delegate: Text {
					font: baseStyle.defaultFont
					text: model.name
					color: baseStyle.trainingFontColor
				}
			}
			spacing: 3
		}

	}
}
