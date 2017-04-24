import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import SortFilterProxyModel 0.2
import "styles"

Item {
	property var _data
	property var stats: _data.stats
	id: root

	StackView {
		id: recStack
		anchors.fill: parent
		initialItem: recList
	}

	Component {
		id: recList
		ColumnLayout {
			IngredientFilter {
				Layout.fillHeight: true
				Layout.fillWidth: true
				model: root._data
				onEditIngredient: recStack.push({item: recEditor, properties: {ingredient: ingredientModel.loadDataForIngredient(id)}})
				onDeleteIngredient: {
					confirmClose.ingredientName = ingredientModel.loadDataForIngredient(id).name;
					confirmClose.ingredientId = id;
					confirmClose.open();
				}
			}
			RowLayout {
				Item {
					Layout.fillWidth: true
				}
				Button {
					text: "Neu"
					onClicked: recStack.push({item: recEditor, properties: {ingredient: ingredientModel.loadDataForIngredient(-1)}})
				}
				Item {
					Layout.minimumWidth: 5
				}
			}
			Item {
				Layout.minimumHeight: 5
			}
		}

	}

	Component {
		id: recEditor
		IngredientEditor {
			onClose: recStack.pop();
		}
	}

	MessageDialog {
		id: confirmClose
		property string ingredientName: ""
		property int ingredientId: -1
		text: "Rezept " + confirmClose.ingredientName + " wirklich löschen?"
		standardButtons: StandardButton.Yes | StandardButton.No
		onButtonClicked: {
			if (clickedButton == StandardButton.Yes) {
				ingredientModel.removeIngredient(ingredientId);
			}
		}
	}
}
