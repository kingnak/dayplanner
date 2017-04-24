import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

ListView {
    id: root
    clip: true
	implicitHeight: 100

    property var _data

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
			onRemoveItem: _data.removeMeal(idx)
			addMenuEnabled: !isConnected
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
		}
	}
}
