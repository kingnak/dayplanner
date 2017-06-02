import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

Item {
	id: root

	property alias popupAbove: inp.popupAbove
	property alias imageRole: inp.imageRole
	property alias model: inp.model
	height: rect.height
	width: parent.width
	z: 2

	signal existingItemSelected(var item)
	signal newItemSelected(string name)

	Rectangle {
		id: rect

		color: "lightGrey";
		width: parent.width
		height: inp.height

		FilterTextInput {
			width: parent.width
			id: inp
			textRole: "name"
			font: baseStyle.editorFont
			onAccepted: {
				if (selectedItem) {
					root.existingItemSelected(selectedItem)
				} else {
					root.newItemSelected(text);
				}

				text = "";
				focus = true;
			}
		}
	}
}
