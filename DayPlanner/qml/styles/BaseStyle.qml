import QtQuick 2.5
import org.kingnak.dayplanner 1.0

Item {

	function mealColor(mealType) {
		switch (mealType) {
		case Meal.Breakfast: return "#FFF176";
		case Meal.Lunch: return "#FF8A65";
		case Meal.Dinner: return "#9575CD";
		default: return "#E0E0E0";
		}
	}

	function shiftColor(shiftName) {
		switch (shiftName) {
		case "0": return "transparent";
		case "X": return "#81D4FA";
		case "A1": return "#81D4FA";
		case "A2": return "#FFD54F";
		case "A3": return "#FFD54F";
		case "Z1": return "#CE93D8";
		case "Z2": return "#CE93D8";
		case "N1": return "#CE93D8";
		case "N2": return "#CE93D8";
		default: return "lightgray";
		}
	}

}
