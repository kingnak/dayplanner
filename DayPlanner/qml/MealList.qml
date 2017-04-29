import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

ListView {
    id: root
    clip: true
	implicitHeight: 100

    property var _data
	property bool popupAbove: false
	property bool expandable: true
	property bool showExpanded: false

	signal requestExpand()
	signal requestCollapse()

    model: _data.items

    delegate: mealItem

    header: headerBanner
    headerPositioning: ListView.OverlayHeader
	footer: footerEditor
	footerPositioning: _data.isEmpty ? ListView.InlineFooter : ListView.OverlayFooter

    Component {
        id: mealItem
		IngredientEditorDelegate {
			width: parent.width

			onRemoveItem: {
				if (isConnectedToRecipe) {
					confirmDelete.recipeName = name;
					confirmDelete.recipeIndex = idx;
					confirmDelete.open();
				} else {
					_data.removeMeal(idx)
				}
			}

			onEditItem: stack.push({item: recipeEditor, properties: {recipeId:_data.items[idx].recipeId, writeBackMeal:_data.items[idx], dispose:true} })
			editButtonEnabled: isConnectedToRecipe
			editButtonVisible: isConnectedToRecipe
			addButtonEnabled: !isConnected
			addButtonVisible: !isConnected || isConnectedToIngredient // actually !isConnected, but make it a placeholder (disabled buttons are transparent)
			addMenu: Menu {
				onAboutToShow: applyName()
				MenuItem {
					text: "Neue Zutat"
					onTriggered: {
						_data.createIngredientFromMeal(index);
					}
				}
				MenuItem {
					text: "Neues Rezept"
					onTriggered: {
						_data.createRecipeFromMeal(index);
					}
				}
			}
		}

    }

    Component {
        id: footerEditor
		IngredientEditorListSelector {
			popupAbove: root.popupAbove
			model: uniformModel
			onExistingItemSelected: {
				if (item.objectType === UniformRecipeIngredientModel.Ingredient)
					_data.createMealForIngredient(item.itemId);
				else if (item.objectType === UniformRecipeIngredientModel.Recipe)
					console.log("Selected Recipe " + item.itemId);
				root.positionViewAtEnd();
			}
			onNewItemSelected: {
				_data.createMeal(name);
				root.positionViewAtEnd();
			}
		}
    }

    Component {
		id: headerBanner
		IngredientEditorHeader {
			backgroundColor: baseStyle.mealColor(_data.type)
			title: utils.mealName(_data.type)
			itemData: _data
			expandable: root.expandable
			showExpanded: root.showExpanded
			onRequestExpand: root.requestExpand()
			onRequestCollapse: root.requestCollapse()
		}
	}

	Component {
		id: recipeEditor
		RecipeEditor {

		}
	}

	MessageDialog {
		id: confirmDelete
		property string recipeName: ""
		property int recipeIndex: -1
		text: "Rezept " + confirmDelete.recipeName + " wirklich löschen?"
		standardButtons: StandardButton.Yes | StandardButton.No
		onButtonClicked: {
			if (clickedButton === StandardButton.Yes) {
				_data.removeMeal(recipeIndex);
			}
		}
	}
}
