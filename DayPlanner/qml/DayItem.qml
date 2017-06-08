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
		showSeparator: false
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
		Layout.fillHeight: false
		_data: root._data.workout
		popupAbove: true
	}

	function doExpand(which) {
		__toggleCollapsed(which, true);
		which.showExpanded = true;
		which.showCollapsed = false;
	}

	function doCollapse(which) {
		which.showExpanded = false;
		__toggleCollapsed(null, false);
	}

	function __toggleCollapsed(except, collapsed) {
		if (except != breakfast) { breakfast.showCollapsed = collapsed; breakfast.showExpanded = false; }
		if (except != lunch) { lunch.showCollapsed = collapsed; lunch.showExpanded = false; }
		if (except != dinner){ dinner.showCollapsed = collapsed; dinner.showExpanded = false; }
		if (except != snack) { snack.showCollapsed = collapsed; snack.showExpanded = false; }
	}
}
