import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

ColumnLayout {
    id: root
	implicitHeight: 100
	spacing: 0

    property var _data
	property bool popupAbove: false
	property bool expandable: true
	property bool showExpanded: false
	property bool showCollapsed: false

	signal requestExpand()
	signal requestCollapse()

	IngredientEditorHeader {
		backgroundColor: baseStyle.mealColor(_data.type)
		title: utils.mealName(_data.type)
		itemData: _data
		expandable: root.expandable
		showExpanded: root.showExpanded
		onRequestExpand: root.requestExpand()
		onRequestCollapse: root.requestCollapse()
		Layout.fillWidth: true
	}

	ListView {
		id: list
		clip: true
		implicitHeight: 100
		Layout.fillHeight: true
		Layout.fillWidth: true
		model: _data.items
		visible: !showCollapsed

		delegate: mealItem

		footer: footerEditor
		footerPositioning: _data.isEmpty ? ListView.InlineFooter : ListView.OverlayFooter
	}

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
			popupAbove: root.popupAbove || (root.showExpanded && !_data.isEmpty)
			imageRole: "iconUrl"
			model: uniformModel
			onExistingItemSelected: {
				if (item.objectType === UniformRecipeIngredientModel.Ingredient)
					_data.createMealForIngredient(item.itemId);
				else if (item.objectType === UniformRecipeIngredientModel.Recipe) {
					var rec = recipeTemplateModel.instantiateTemplate(item.itemId);
					if (rec) _data.createMealForRecipe(rec);
				}
				list.positionViewAtEnd();
			}
			onNewItemSelected: {
				_data.createMeal(name);
				list.positionViewAtEnd();
			}
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
