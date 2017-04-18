import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

GridLayout {
	property var recipe

	id: editor
	columns: 2
	Label { text: "Name" }
	TextField { text: editor.recipe.name }
	Label { text: "Menge" }
	DoubleField { text: editor.recipe.quantity }
}
