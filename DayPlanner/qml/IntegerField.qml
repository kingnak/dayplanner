import QtQuick 2.0
import QtQuick.Controls 1.4
import org.kingnak.dayplanner 1.0

TextField {
	signal intFinished(string val)
	signal intError(string val)

	property string value: ""
	onValueChanged: text = utils.formatInt(value)
	font: baseStyle.editorFont

	validator: IntValidator { bottom: 0 }
	onEditingFinished: if (acceptableInput) intFinished(utils.parseInt(text)); else intError(text);
}
