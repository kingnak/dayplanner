import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
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
		RecipeFilter {
			model: root._data
			onEditRecipe: recStack.push({item: recEditor, properties: {recipe: recipeModel.loadDataForRecipe(id)}})
		}

	}

	Component {
		id: recEditor
		RecipeEditor {

		}
	}
}
