import QtQuick 2.5
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import "styles"

BorderedContainer {
	id: root
	property var writeBackMeal
	property int recipeId
	property var _data: recipeModel.loadRecipeById(recipeId)
	property bool dispose: false
	property bool popOnBack: true

	signal openTemplate(int id)
	signal close()

	onBack: if (popOnBack) { stack.pop() } else { close(); }

	ColumnLayout {
		anchors.fill: parent

		Component.onCompleted: {
			if (!_data.isTemplate) _data.writeBackMeal = writeBackMeal;
		}
		Component.onDestruction: {
			_data.writeBackMeal = null;
			if (dispose) {
				var t = _data;
				_data = undefined;
				t.deleteLater();
			}
		}

		Row {
			spacing: 10
			Text { text: "Name:"; anchors.verticalCenter: parent.verticalCenter; font: baseStyle.headerFont }
			TextField {
				text: _data.name
				style: PlaceholderTextEditStyle { }
				width: 200
				onEditingFinished: _data.name = text
			}
			Button {
				tooltip: "Kopieren"
				iconSource: "qrc:///icons/copy"
				style: SmallButtonStyle{ iconSize: 16; borderAlwaysVisible:true}
				onClicked: {
					if (!_data.copyToClipboard()) {
						showError("Fehler beim Kopieren");
					}
				}
			}
			Button {
				tooltip: "Importieren"
				iconSource: "qrc:///icons/paste"
				style: SmallButtonStyle{ iconSize: 16; borderAlwaysVisible:true}
				onClicked: {
					if (!_data.pasteFromClipboard()) {
						showError("Fehler beim Importieren.\nSind die Daten im richtigen Format?");
					}
				}
			}
			Button {
				visible: !_data.isTemplate && !_data.isConnectedToTemplate
				text: "Als Vorlage speichern"
				style: SmallButtonStyle{square: false; borderAlwaysVisible:true}
				onClicked: {
					_data.saveAsTemplate();
				}
			}
			Button {
				visible: !_data.isTemplate && _data.isConnectedToTemplate
				text: "Vorlage aktualisieren"
				style: SmallButtonStyle{square: false; borderAlwaysVisible:true}
				onClicked: {
					_data.updateTemplate();
				}
			}
			Button {
				visible: !_data.isTemplate && _data.isConnectedToTemplate
				text: "Vorlage öffnen"
				style: SmallButtonStyle{square: false; borderAlwaysVisible:true}
				onClicked: {
					root.openTemplate(_data.templateId)
				}
			}
		}

		Row {
			Text { text: "Rezept für "; anchors.verticalCenter: parent.verticalCenter; font: baseStyle.defaultFont }
			IntegerField {
				id: txtServings
				text: _data.servings
				onIntFinished: {
					var old = _data.servings;
					_data.servings = val;
					if (old === _data.displayServings) {
						_data.displayServings = val;
					}
				}
				style: PlaceholderTextEditStyle{textWidth: "22"}
			}
			Text { text: " Portionen"; anchors.verticalCenter: parent.verticalCenter; font: baseStyle.defaultFont }
		}

		Row {
			spacing: 15
			Row {
				Text { text: "Anzeige für "; anchors.verticalCenter: parent.verticalCenter; font: baseStyle.defaultFont }
				IntegerField {
					id: txtDisplayServings
					text: _data.displayServings
					onIntFinished: _data.displayServings = val
					style: PlaceholderTextEditStyle{textWidth: "22"}
				}
				Text { text: " Portionen"; anchors.verticalCenter: parent.verticalCenter; font: baseStyle.defaultFont }
			}
			Button {
				enabled: _data.servings !== _data.displayServings
				opacity: enabled?1:0
				style: SmallButtonStyle{square: false; borderAlwaysVisible:true}
				text: "Angaben für " + _data.displayServings + " Portionen übernehmen"
				onClicked: _data.adjustForServings(_data.displayServings);
			}
		}

		CheckBox {
			text: "Werte überschreiben"
			checked: _data.nutritionValuesOverridden
			onCheckedChanged: _data.nutritionValuesOverridden = checked
			style: CheckBoxStyle{ label :Text{text: "Werte überschreiben";font: baseStyle.defaultFont}}
		}

		Row {
			visible: _data.nutritionValuesOverridden
			spacing: 5
			Label { text: "Fett"; anchors.verticalCenter: parent.verticalCenter }
			DoubleField { value: _data.fat; id: txtFat; onDoubleFinished: _data.overrideFat(val); style: PlaceholderTextEditStyle {} }
			Rectangle { visible: true; width: 5; height: parent.height; color: "transparent" }
			Label { text: "Kohlenhydrate"; anchors.verticalCenter: parent.verticalCenter; }
			DoubleField { value: _data.carbs; id: txtCarbs; onDoubleFinished: _data.overrideCarbs(val); style: PlaceholderTextEditStyle {} }
			Rectangle { visible: true; width: 5; height: parent.height; color: "transparent" }
			Label { text: "Eiweiß"; anchors.verticalCenter: parent.verticalCenter; }
			DoubleField { value: _data.protein; id: txtProtein; onDoubleFinished: _data.overrideProtein(val); style: PlaceholderTextEditStyle {} }
			Rectangle { visible: true; width: 5; height: parent.height; color: "transparent" }
			Label { text: "Kalorien"; anchors.verticalCenter: parent.verticalCenter; }
			DoubleField { value: _data.calories; id: txtCalories; onDoubleFinished: _data.overrideCalories(val); style: PlaceholderTextEditStyle {} }
		}

		ListView {
			Layout.fillHeight: true
			Layout.fillWidth: true
			model: _data.items.items
			delegate: recipeItem
			header: headerBanner
			headerPositioning: ListView.OverlayHeader
			footer: footerEditor
			footerPositioning: _data.items.isEmpty ? ListView.InlineFooter : ListView.OverlayFooter
			clip: true

			Component {
				id: recipeItem
				IngredientEditorDelegate {
					selectable: false
					width: parent.width
					onRemoveItem: _data.items.removeItem(idx)
					addButtonVisible: true
					addButtonEnabled: !isConnectedToIngredient
					onAddItem: _data.items.createIngredientFromItem(idx)
				}
			}

			Component {
				id: footerEditor
				IngredientEditorListSelector {
					model: ingredientModel
					popupAbove: true
					onExistingItemSelected: {
						_data.items.createItemForIngredient(item.itemId);
						list.positionViewAtEnd();
					}
					onNewItemSelected: {
						_data.items.createItem(name);
						list.positionViewAtEnd();
					}
				}
			}

			Component {
				id: headerBanner
				IngredientEditorHeader {
					hasImportMenu: false
					backgroundColor: _data.isTemplate ? baseStyle.templateHeaderColor : baseStyle.ingredientHeaderColor
					title: "Zutaten"
					itemData: _data.items
				}
			}

		}

	}

	function showError(txt) {
		errorMsg.text = txt;
		errorMsg.open();
	}

	MessageDialog {
		id: errorMsg
		standardButtons: StandardButton.Ok
	}
}
