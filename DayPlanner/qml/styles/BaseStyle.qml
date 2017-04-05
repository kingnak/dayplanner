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
		case "A2": return "#FFE57F";
		case "A3": return "#FFE57F";
		case "Z1": return "#03A9F4";
		case "Z2": return "#03A9F4";
		case "N1": return "#40C4FF";
		case "N2": return "#40C4FF";
		default: return "#9E9E9E";
		}
	}

	property color trainingColor: "#512DA8"
	property color trainingFontColor: "#FFFFFF"
	property color todayHighlightColor: "#FF7F7F"

	property color controlBorderColor: "#60000000"

	property font headerFont: Qt.font({
		weight: Font.Bold,
		pointSize: 9
	})
	property font shiftFont: Qt.font({
		weight: Font.Bold,
		pointSize: 9
	})
	property font defaultFont: Qt.font({
		weight: Font.Normal,
		pointSize: 9
	})
	property font editorFont: Qt.font({
		weight: Font.Normal,
		pointSize: 9
	})
	property font summaryFont: Qt.font({
		weight: Font.Normal,
		pointSize: 9
	})

	function formatSummary(value, type, postfix) {
		var ret = value + '&nbsp;<span style="color:\'#80000000\';font-size:8pt;">'+type+postfix+'</span>';
		return ret;
	}
}
