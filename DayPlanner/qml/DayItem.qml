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
	}

	MealList {
		id: lunch
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.lunch
	}

	MealList {
		id: dinner
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.dinner
	}

	MealList {
		id: snack
		Layout.fillWidth: true
		Layout.fillHeight: true
		_data: root._data.snack
	}
}
