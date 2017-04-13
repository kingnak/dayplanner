import QtQuick 2.5
import QtQuick.Controls 2.0

RangeSlider {
	id: control
	background: Rectangle {
		x: control.leftPadding
		y: control.topPadding + control.availableHeight / 2 - height / 2 - Math.max(txf.height, txs.height) / 2
		implicitWidth: 200
		implicitHeight: 4
		width: control.availableWidth
		height: implicitHeight
		radius: 2
		color: "#bdbebf"

		Rectangle {
			x: control.first.visualPosition * parent.width
			width: control.second.visualPosition * parent.width - x
			height: parent.height
			color: "#21be2b"
			radius: 2
		}
	}

	first.handle: Item {
		x: control.leftPadding + first.visualPosition * (control.availableWidth - width)
		y: control.topPadding + control.availableHeight / 2 - height / 2
		implicitWidth: 8
		implicitHeight: 16+txf.height
		property real curValue: (control.to-control.from)*first.visualPosition+control.from
		Column {
			Rectangle {
				width: 8
				height: 16
				color: first.pressed ? "#f0f0f0" : "#f6f6f6"
				border.color: "#bdbebf"
			}
			Text {
				id: txf
				text: utils.formatNumber(first.handle.curValue)
				x: 8-width
			}
		}
	}

	second.handle: Item {
		x: control.leftPadding + second.visualPosition * (control.availableWidth - width)
		y: control.topPadding + control.availableHeight / 2 - height / 2
		implicitWidth: 8
		implicitHeight: 16+txs.height
		property real curValue: (control.to-control.from)*second.visualPosition+control.from
		Column {
			Rectangle {
				width: 8
				height: 16
				color: second.pressed ? "#f0f0f0" : "#f6f6f6"
				border.color: "#bdbebf"
			}
			Text {
				id: txs
				text: utils.formatNumber(second.handle.curValue)
			}
		}

	}

}
