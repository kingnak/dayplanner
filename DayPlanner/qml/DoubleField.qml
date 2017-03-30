import QtQuick 2.0
import QtQuick.Controls 1.4

TextField {
    signal doubleFinished(string val)
    signal doubleError(string val)

    property string value: ""
    onValueChanged: text = value

    validator: DoubleValidator { bottom: 0; decimals: 1 }
    onEditingFinished: if (acceptableInput) doubleFinished(text); else doubleError(text);
}
