import QtQuick 2.0
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.4

BorderedContainer {
	property alias ingredient: editor.ingredient
	signal close()
	id: root
	backVisible: false

	GridLayout {
		id: editor
		property var ingredient

		function _passThroughValues() {
			editor.ingredient.name = txtName.text;
			editor.ingredient.referenceQuantity = txtQuantity.text;
			editor.ingredient.defaultQuantity = txtDefQuantity.text;
			editor.ingredient.fat = txtFat.value;
			editor.ingredient.protein = txtProtein.value;
			editor.ingredient.carbs = txtCarbs.value;
			editor.ingredient.calories = txtCalories.value;
		}

		columns: 2
		Label { text: "Name" }
		TextField { text: editor.ingredient.name; id: txtName }
		Label { text: "Menge" }
		Column {
			IntegerField { text: editor.ingredient.referenceQuantity; id: txtQuantity; }
			Button { text: "Auf 100 umrechnen"; onClicked: { editor._passThroughValues(); editor.ingredient.calcTo100(); } }
		}
		Label { text: "Standard Menge" }
		IntegerField { text: editor.ingredient.defaultQuantity; id: txtDefQuantity; }
		Label { text: "Fett" }
		DoubleField { value: editor.ingredient.fat; id: txtFat; onDoubleFinished: editor.ingredient.fat = val; onDoubleError: value = editor.ingredient.fat; }
		Label { text: "Kohlenhydrate" }
		DoubleField { value: editor.ingredient.carbs; id: txtCarbs; onDoubleFinished: editor.ingredient.carbs = val; onDoubleError: value = editor.ingredient.carbs; }
		Label { text: "Eiweiß" }
		DoubleField { value: editor.ingredient.protein; id: txtProtein; onDoubleFinished: editor.ingredient.protein = val; onDoubleError: value = editor.ingredient.protein; }
		Label { text: "Kalorien" }
		DoubleField { value: editor.ingredient.calories; id: txtCalories; onDoubleFinished: editor.ingredient.calories = val; onDoubleError: value = editor.ingredient.calories; }
		Column {
			Button {
				text: "Zurück"
				onClicked: root.close();
			}
		}
		Column {
			Button {
				text: "Speichern"
				onClicked: {
					editor._passThroughValues();
					editor.ingredient.save();
					root.close();
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
}
