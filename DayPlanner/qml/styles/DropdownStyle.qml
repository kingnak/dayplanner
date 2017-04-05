import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"
	property color borderColor: baseStyle.controlBorderColor
    property bool showHovered: true
    width: control.width
    height: control.height
    implicitHeight: 20
	implicitWidth: 50

    Canvas {
        readonly property color _clr: parent.borderColor
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 2
        width: 5
        height: 5
        contextType: "2d"
        visible: root.showHovered

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
		border.color: parent.borderColor
		color: "transparent"
		anchors.left: parent.left
		width: parent.width
		height: parent.height
		visible: root.showHovered
    }
}
