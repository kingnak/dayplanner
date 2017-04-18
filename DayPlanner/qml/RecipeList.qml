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
			RecipeFilter {
				Layout.fillHeight: true
				Layout.fillWidth: true
				model: root._data
				onEditRecipe: recStack.push({item: recEditor, properties: {recipe: recipeModel.loadDataForRecipe(id)}})
				onDeleteRecipe: {
					confirmClose.recipeName = recipeModel.loadDataForRecipe(id).name;
					confirmClose.recipeId = id;
					confirmClose.open();
				}
			}
			RowLayout {
				Item {
					Layout.fillWidth: true
				}
				Button {
					text: "Neu"
					onClicked: recStack.push({item: recEditor, properties: {recipe: recipeModel.loadDataForRecipe(-1)}})
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
		RecipeEditor {
			onClose: recStack.pop();
		}
	}

	MessageDialog {
		id: confirmClose
		property string recipeName: ""
		property int recipeId: -1
		text: "Rezept " + confirmClose.recipeName + " wirklich löschen?"
		standardButtons: StandardButton.Yes | StandardButton.No
		onButtonClicked: {
			if (clickedButton == StandardButton.Yes) {
				recipeModel.removeRecipe(recipeId);
			}
		}
	}
}
