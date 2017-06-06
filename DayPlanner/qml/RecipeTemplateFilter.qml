import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import SortFilterProxyModel 0.2
import "styles"

SplitView {
	property alias model: sorter.sourceModel

	id: theList
	signal deleteTemplate(int id)
	signal editTemplate(int id)

	SortFilterProxyModel {
		id: sorter
		sortRoleName: "name"
		sortCaseSensitivity: Qt.CaseInsensitive
	}

	Item {
		width: Layout.preferredWidth
		Layout.minimumWidth: 150
		Layout.preferredWidth: 160+200
		Layout.fillHeight: true
		height: parent.height
		TextField {
			id: searchText
			width: parent.width
			anchors.top: parent.top
		}
		TableView {
			width:parent.width
			Layout.fillHeight: true
			anchors.top: searchText.bottom
			anchors.bottom: parent.bottom

			id: table
			model: sorter
			TableViewColumn {
				role: "itemId"
				delegate: editDelegate
				width: 35
			}

			TableViewColumn {
				role: "name"
				title: "Name"
			}
			TableViewColumn {
				role: "fat"
				title: "Fett"
				width: 40
				delegate: doubleDelegate
			}
			TableViewColumn {
				role: "carbs"
				title: "KH"
				width: 40
				delegate: doubleDelegate
			}
			TableViewColumn {
				role: "protein"
				title: "EW"
				width: 40
				delegate: doubleDelegate
			}
			TableViewColumn {
				role: "calories"
				title: "kcal"
				width: 40
				delegate: doubleDelegate
			}
			Component {
				id: editDelegate
				Row {
					spacing: 0
					ToolButton {
						style: SmallButtonStyle{}
						height: 15
						iconSource: "qrc:///icons/delete-small"
						onClicked: theList.deleteTemplate(styleData.value)
					}
					ToolButton {
						style: SmallButtonStyle{}
						height: 15
						iconSource: "qrc:///icons/edit-small"
						onClicked: theList.editTemplate(styleData.value)
					}
				}
			}
			Component {
				id: doubleDelegate
				Text {
					text: utils.formatDouble(styleData.value)
					color: styleData.textColor
					elide: styleData.elideMode
					horizontalAlignment: Text.AlignRight
				}
			}
		}
	}
}
