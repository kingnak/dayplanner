import QtQuick 2.5
import org.kingnak.dayplanner 1.0

QtObject {

	function mealColor(mealType) {
		switch (mealType) {
		case Meal.Breakfast: return "#FFD54F";
		case Meal.Lunch: return "#81C784";
		case Meal.Dinner: return "#4FC3F7";
		case Meal.Snacks: return "#DCE775";
		default: return "#E0E0E0";
		}
	}

	function mealColorLight(mealType) {
		switch (mealType) {
		case Meal.Breakfast: return "#FFE082";
		case Meal.Lunch: return "#A5D6A7";
		case Meal.Dinner: return "#4FC3F7";
		case Meal.Snacks: return "#81D4FA";
		default: return "#EEEEEE";
		}
	}

	function shiftColor(shiftName) {
		switch (shiftName) {
		case "0": return "transparent";
		case "X": return "#FFC107";
		case "A1": return "#FFC107";
		case "A2": return "#4CAF50";
		case "A3": return "#4CAF50";
		case "Z1": return "#03A9F4";
		case "Z2": return "#03A9F4";
		case "N1": return "#03A9F4";
		case "N2": return "#03A9F4";
		default: return "#9E9E9E";
		}
	}

	property font headerFont: Qt.font({
		weight: Font.Bold,
		pointSize: 9
	})
	property font shiftFont: Qt.font({
		weight: Font.Normal,
		pointSize: 9
	})
	property font defaultFont: Qt.font({
		weight: Font.Normal,
		pointSize: 8
	})
	property font editorFont: Qt.font({
		weight: Font.Normal,
		pointSize: 8
	})

}
