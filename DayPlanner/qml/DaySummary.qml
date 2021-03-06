import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

Rectangle {
	property var _data
	id: root
	property bool highlight: false
	anchors.fill: parent
	signal openDay(date d)

	MouseArea {
		anchors.fill: parent
		onClicked: root.openDay(_data.date)
	}

	ColumnLayout {
		anchors.fill: parent
		spacing: 0

		DayHeader {
			highlight: root.highlight
			dayData: root._data
			anchors.left: parent.left
			anchors.right: parent.right
		}

		Flickable {
			anchors.left: parent.left
			anchors.right: parent.right
			Layout.fillHeight: true
			contentHeight: c.height
			contentWidth: c.width
			clip: true

			Column {
				id: c
				anchors.left: parent.left
				width: root.width

				MealSummary {
					visible: !_data.breakfast.isEmpty
					width: parent.width
					mealData: _data.breakfast
				}

				MealSummary {
					visible: !_data.lunch.isEmpty
					width: parent.width
					mealData: _data.lunch
				}

				MealSummary {
					visible: !_data.dinner.isEmpty
					width: parent.width
					mealData: _data.dinner
				}

				MealSummary {
					visible: !_data.snack.isEmpty
					width: parent.width
					mealData: _data.snack
				}

				TrainingSummary {
					visible: !_data.workout.isEmpty
					width: parent.width
					workoutData: _data.workout
				}
			}
		}
	}
}
