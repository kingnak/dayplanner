import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

GridLayout {
	property var ingredient
	signal close()

	function _passThroughValues() {
		editor.ingredient.name = txtName.text;
		editor.ingredient.referenceQuantity = txtQuantity.text;
		editor.ingredient.defaultQuantity = txtDefQuantity.text;
		editor.ingredient.fat = txtFat.text;
		editor.ingredient.protein = txtProtein.text;
		editor.ingredient.carbs = txtCarbs.text;
		editor.ingredient.calories = txtCalories.text;
	}

	id: editor
	columns: 2
	Label { text: "Name" }
	TextField { text: editor.ingredient.name; id: txtName }
	Label { text: "Menge" }
	Column {
		IntegerField { text: editor.ingredient.referenceQuantity; id: txtQuantity; }
		Button { text: "Auf 100 umrechnen"; onClicked: { _passThroughValues(); editor.ingredient.calcTo100(); } }
	}
	Label { text: "Standard Menge" }
	IntegerField { text: editor.ingredient.defaultQuantity; id: txtDefQuantity; }
	Label { text: "Fett" }
	DoubleField { text: editor.ingredient.fat; id: txtFat; }
	Label { text: "Eiweiß" }
	DoubleField { text: editor.ingredient.protein; id: txtProtein; }
	Label { text: "Kohlenhydrate" }
	DoubleField { text: editor.ingredient.carbs; id: txtCarbs; }
	Label { text: "Kalorien" }
	DoubleField { text: editor.ingredient.calories; id: txtCalories; }
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
				editor.ingredient.save();
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
