import QtQuick 2.0
import QtQuick.Controls.Styles 1.4

ComboBoxStyle {
    id: comboStyle
    background: Rectangle {
        id: rectBack
        color: "transparent"
        width: control.width
        height: control.height
        implicitHeight: 20
        implicitWidth: 40

        readonly property color _borderColor: "#C0C0C0"

        Canvas {
            readonly property alias _clr: rectBack._borderColor
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 2
            width: 5
            height: 5
            contextType: "2d"
            visible: control.hovered

            onPaint: {
                context.reset();
                context.fillStyle = _clr;
                context.moveTo(0, 0);
                context.lineTo(width, 0);
                context.lineTo(width/2, height);
                context.closePath();
                context.fill();
            }
        }

        Rectangle {
            color: _borderColor; anchors.left: parent.left; width: 1; height: parent.height; visible: control.hovered
        }
        Rectangle {
            color: _borderColor; anchors.right: parent.right; width: 1; height: parent.height; visible: control.hovered
        }
        Rectangle {
            color: _borderColor; anchors.top: parent.top; height: 1; width: parent.width; visible: control.hovered
        }
        Rectangle {
            color: _borderColor; anchors.bottom: parent.bottom; height: 1; width: parent.width; visible: control.hovered
        }
    }
}
