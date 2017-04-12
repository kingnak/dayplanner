import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0 as Q2
import QtQuick.Controls.Styles 1.4
import SortFilterProxyModel 0.2
import "styles"

TextField {
    property alias model: sorter.sourceModel
    property alias minPopupWidth: popup.minWidth
    property alias minPopupHeight: popup.minHeight
    property alias textRole: popup.modelRole
    property var selectedItem: null

    id: root
    function selectNext() {
        if (popup.visible && popup.count > 0) {
            if (popup.currentIndex === -1) {
                popup.currentIndex = 0;
            } else if (popup.currentIndex < popup.count-1) {
                popup.currentIndex++;
            }
        }
    }

    function selectPrev() {
        if (popup.visible && popup.count > 0) {
            if (popup.currentIndex === -1) {
                popup.currentIndex = 0;
            } else if (popup.currentIndex > 0) {
                popup.currentIndex--;
            }
        }
    }

    Keys.onPressed: {
        switch (event.key) {
        case Qt.Key_Up:
            selectPrev();
            event.accepted = true;
            break;
        case Qt.Key_Down:
            event.accepted = true;
            if (!popup.visible) {
                popup.open();
                popup.currentIndex = -1;
            }
            selectNext();
            break;
        case Qt.Key_Escape:
            popup.close();
            event.accepted = true;
            break;
        }
    }

    SortFilterProxyModel {
        id: sorter
        sourceModel: null
        filterPattern: root.text
        filterCaseSensitivity: Qt.CaseInsensitive
    }

    Q2.Popup {
        id: popup
        property alias count: list.count
        property alias currentIndex: list.currentIndex
        property alias currentItem: list.currentItem
        property string modelRole: "text"

        property int minWidth: 200
        property int minHeight: 100

        width: Math.max(parent.width, minPopupWidth)
        x: parent.x - (parent.style ? parent.stlye.leftPadding : 0)
        y: parent.y + parent.height
        padding: 0
        margins: 0
        height: Math.max(minPopupHeight, list.implicitHeight)

        contentItem: ListView {
            id: list
            clip:true
            model: sorter
            delegate: Rectangle {
                width: parent.width
                height: txt.height
                color: "transparent"
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: list.currentIndex = index
                    onClicked: {
                        list.currentIndex = index;
                        root.accepted();
                    }
                }

                Text { id:txt; text: popup.modelRole === '' ? modelData : model[popup.modelRole]; }
            }
            highlight: Rectangle { color: "#c0c0c0"}
        }

        Rectangle {
             id: scrollbar
             anchors.right: list.right
             opacity: list.flicking ? 1 : 0
             Behavior on opacity {
                 NumberAnimation { duration: 150 }
             }
             y: list.visibleArea.yPosition * list.height
             width: 5
             height: list.visibleArea.heightRatio * list.height
             color: "black"
         }
    }

    onTextChanged:{
        if (text != "") {
            popup.currentIndex = -1;
            popup.open();
        }
    }
    onAccepted: _finishEditing();
    onEditingFinished: _finishEditing();

    function _finishEditing() {
        var idx = popup.currentIndex
        if (idx !== -1) {
            selectedItem = sorter.get(idx);
			//text = sorter.get(idx).name; // <- Will reset selected item for onAccept listeners to -1...
        } else {
			// Try to find a case insensitive match
			if (sorter.count > 0 && sorter.get(0).name.toLowerCase() === text.toLowerCase()) {
				selectedItem = sorter.get(0);
			} else {
				selectedItem = null;
			}
        }

		popup.close();
    }

    style: TextFieldStyle {
        background: DropdownStyle {
            showHovered: root.hovered || root.focus || popup.visible
        }
    }

}
