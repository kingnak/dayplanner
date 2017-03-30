import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import "styles"

Rectangle {
    property var _data
    id: root

	GridLayout {
        anchors.fill: parent
		columns: 3

		Rectangle { Layout.fillWidth: true; Layout.minimumWidth: 0 }

		ColumnLayout {
			Layout.minimumWidth: 400
			Layout.preferredWidth: 450
			Layout.maximumWidth: 650
			Layout.minimumHeight: 400
			Layout.preferredHeight: 600
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
		}

		Rectangle { Layout.fillWidth: true; Layout.minimumWidth: 0 }
		Rectangle { Layout.fillHeight: true; Layout.columnSpan: 3; Layout.minimumHeight: 0 }
    }
}
