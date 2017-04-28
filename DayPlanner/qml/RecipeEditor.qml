import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import "styles"

ColumnLayout {
	property int recipeId
	property var _data: recipeModel.loadRecipeById(recipeId)
	property bool dispose: false

	//Component.onCompleted: {
	//	_data = recipeModel.loadRecipeById(recipeId);
	//}
	Component.onDestruction: {
		if (dispose) {
			var t = _data;
			_data = undefined;
			t.deleteLater();
		}
	}

	Row {
		Text { text: "Name:" }
		TextField {
			text: _data.name
		}
	}

	Text {
		text: "Zutaten für <b>" + _data.servings + "</b> Portionen";
	}
	Row {
		Text { text: "Anzeige für " }
		IntegerField {
			id: txtServings
			text: _data.displayServings
			onIntFinished: _data.displayServings = val
		}
		Text { text: " Portionen" }
	}

	ListView {
		Layout.fillHeight: true
		Layout.fillWidth: true
		model: _data.items.items
		delegate: recipeItem
		header: headerBanner
		headerPositioning: ListView.OverlayHeader
		footer: footerEditor
		footerPositioning: _data.isEmpty ? ListView.InlineFooter : ListView.OverlayFooter

		Component {
			id: recipeItem
			IngredientEditorDelegate {
				width: parent.width
				onRemoveItem: _data.items.removeItem(idx)
				addMenuEnabled: false
			}
		}

		Component {
			id: footerEditor
			IngredientEditorListSelector {
				model: ingredientModel
				onExistingItemSelected: {
					_data.items.createItemForIngredient(item.itemId);
					root.positionViewAtEnd();
				}
				onNewItemSelected: {
					_data.items.createItem(name);
					root.positionViewAtEnd();
				}
			}
		}

		Component {
			id: headerBanner
			IngredientEditorHeader {
				backgroundColor: "#f0f0f0"
				title: "Zutaten"
				itemData: _data.items
			}
		}

	}

}
