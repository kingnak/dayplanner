import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

GridLayout {
	property var recipe
	signal close()

	function _passThroughValues() {
		editor.recipe.name = txtName.text;
		editor.recipe.quantity = txtQuantity.text;
		editor.recipe.fat = txtFat.text;
		editor.recipe.protein = txtProtein.text;
		editor.recipe.carbs = txtCarbs.text;
		editor.recipe.calories = txtCalories.text;
		editor.recipe.url = txtUrl.text;
	}

	id: editor
	columns: 2
	Label { text: "Name" }
	TextField { text: editor.recipe.name; id: txtName }
	Label { text: "Menge" }
	Column {
		DoubleField { text: editor.recipe.quantity; id: txtQuantity; }
		Button { text: "Auf 100 umrechnen"; onClicked: { _passThroughValues(); editor.recipe.calcTo100(); } }
	}
	Label { text: "Fett" }
	DoubleField { text: editor.recipe.fat; id: txtFat; }
	Label { text: "Eiweiß" }
	DoubleField { text: editor.recipe.protein; id: txtProtein; }
	Label { text: "Kohlenhydrate" }
	DoubleField { text: editor.recipe.carbs; id: txtCarbs; }
	Label { text: "Kalorien" }
	DoubleField { text: editor.recipe.calories; id: txtCalories; }
	Label { text: "URL" }
	TextField { text: editor.recipe.url; id: txtUrl; }
	Column {
		Button {
			text: "Zurück"
			onClicked: editor.close();
		}
	}
	Column {
		Button {
			text: "Speichern"
			onClicked: {
				_passThroughValues();
				editor.recipe.save();
				editor.close();
			}
		}
		Item {}
		Layout.fillWidth: true
	}
	Item {
		Layout.columnSpan: 2
		Layout.fillHeight: true
	}
}
