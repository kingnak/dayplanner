import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
import org.kingnak.dayplanner 1.0
import "styles"

Item {
	id: root

	property alias backgroundColor: rect.color
	property alias title: txt.text
	property var itemData


	width: parent.width
	height: rect.height

	Rectangle {
		id: rect
		z: 2
		width: parent.width
		height: Math.max(txt.height*1.2, txt.height+6)

		RowLayout {
			width: parent.width
			anchors.verticalCenter: parent.verticalCenter
			Text {
				Layout.fillWidth: true
				font: baseStyle.headerFont
				id: txt
			}
			Text {
				font: baseStyle.defaultFont
				text: "\u03A3 " + utils.formatNumber(itemData.sumFat);
				Layout.minimumWidth: 40 + metrics.boundingRect("F").width
			}
			Text {
				font: baseStyle.defaultFont
				text: "\u03A3 " + utils.formatNumber(itemData.sumCarbs);
				Layout.minimumWidth: 40 + metrics.boundingRect("KH").width
			}
			Text {
				font: baseStyle.defaultFont
				text: "\u03A3 " + utils.formatNumber(itemData.sumProtein);
				Layout.minimumWidth: 40 + metrics.boundingRect("EW").width
			}
			Text {
				font: baseStyle.defaultFont
				text: "\u03A3 " + utils.formatNumber(itemData.sumCalories);
				Layout.minimumWidth: 40 + metrics.boundingRect("kcal \u03A3").width
			}
		}
		FontMetrics {
			id: metrics
			font: baseStyle.editorFont
		}
	}
}
