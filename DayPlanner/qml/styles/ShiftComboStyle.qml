import QtQuick 2.0
import QtQuick.Controls.Styles 1.4

ComboBoxStyle {
    id: comboStyle
    property bool showHovered: control.hovered
    background: DropdownStyle {
        showHovered: comboStyle.showHovered
    }
}
