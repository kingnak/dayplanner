import QtQuick 2.0
import QtQuick.Controls 1.4
import org.kingnak.dayplanner 1.0

TextField {
    signal doubleFinished(string val)
    signal doubleError(string val)

    property string value: ""
	onValueChanged: text = utils.formatNumber(value)
	font: baseStyle.editorFont

    validator: DoubleValidator { bottom: 0; decimals: 1 }
	onEditingFinished: if (acceptableInput) doubleFinished(utils.parseNumber(text)); else doubleError(text);
}
