import QtQuick 2.0

Rectangle {
    id: root
    color: "transparent"
    property color borderColor: "#c0c0c0"
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
        color: borderColor; anchors.left: parent.left; width: 1; height: parent.height; visible: root.showHovered
    }
    Rectangle {
        color: borderColor; anchors.right: parent.right; width: 1; height: parent.height; visible: root.showHovered
    }
    Rectangle {
        color: borderColor; anchors.top: parent.top; height: 1; width: parent.width; visible: root.showHovered
    }
    Rectangle {
        color: borderColor; anchors.bottom: parent.bottom; height: 1; width: parent.width; visible: root.showHovered
    }
}
