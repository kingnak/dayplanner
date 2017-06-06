import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Dialogs 1.2
import SortFilterProxyModel 0.2
import "styles"

Item {
	property var _data
	id: root

	StackView {
		id: recStack
		anchors.fill: parent
		initialItem: recList
	}

	Component {
		id: recList
		ColumnLayout {
			RecipeTemplateFilter {
				Layout.fillHeight: true
				Layout.fillWidth: true
				model: root._data
				onEditTemplate: recStack.push({item: recEditor, properties: {_data: recipeTemplateModel.loadTemplateById(id)}})
				onDeleteTemplate: {
					confirmDelete.templateName = recipeTemplateModel.loadTemplateById(id).name;
					confirmDelete.templateId = id;
					confirmDelete.open();
				}
			}

			RowLayout {
				Item {
					Layout.fillWidth: true
				}
				Button {
					text: "Neu"
					onClicked: recStack.push({item: recEditor, properties: {_data: recipeTemplateModel.createTemplate()}})
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
			popOnBack: false
		}
	}

	MessageDialog {
		id: confirmDelete
		property string templateName: ""
		property int templateId: -1
		text: "Rezeptvorlage " + confirmDelete.templateName + " wirklich löschen?"
		standardButtons: StandardButton.Yes | StandardButton.No
		onButtonClicked: {
			if (clickedButton === StandardButton.Yes) {
				recipeTemplateModel.removeTemplateById(templateId);
			}
		}
	}
}
