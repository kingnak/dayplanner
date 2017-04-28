import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

ColumnLayout {

	property var _data
	id: root

	DayHeader {
		dayData: _data
		anchors.left: parent.left
		anchors.right: parent.right
	}

	MealList {
		id: breakfast
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.breakfast
		onRequestExpand: doExpand(breakfast);
		onRequestCollapse: doCollapse(breakfast);
	}

	MealList {
		id: lunch
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.lunch
		onRequestExpand: doExpand(lunch);
		onRequestCollapse: doCollapse(lunch);
	}

	MealList {
		id: dinner
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.dinner
		onRequestExpand: doExpand(dinner);
		onRequestCollapse: doCollapse(dinner);
	}

	MealList {
		id: snack
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.snack
		onRequestExpand: doExpand(snack);
		onRequestCollapse: doCollapse(snack);
	}

	WorkoutList {
		id: workouts
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.workout
		popupAbove: true
	}

	function doExpand(which) {
		__toggleVisible(which, false);
		which.showExpanded = true;
	}

	function doCollapse(which) {
		which.showExpanded = false;
		__toggleVisible(null, true);
	}

	function __toggleVisible(except, vis) {
		if (except != breakfast) breakfast.visible = vis;
		if (except != lunch) lunch.visible = vis;
		if (except != dinner) dinner.visible = vis;
		if (except != snack) snack.visible = vis;
		workouts.visible = vis;

	}
}
