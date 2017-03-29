import QtQuick 2.0
import QtQuick.Controls 1.4

TextField {
    function _toDouble(t) {
        t = t.replace(Qt.locale().decimalPoint, '.');
        return t;
    }
    function _toString(v) {
        v = v+'';
        v = v.replace('.', Qt.locale().decimalPoint);
        return v;
    }

    signal doubleFinished(string val)
    signal doubleError(string val)

    property string value: ""
    onValueChanged: {
        text = _toString(value)
    }

    validator: DoubleValidator { bottom: 0; decimals: 1 }
    onEditingFinished: if (acceptableInput) doubleFinished(_toDouble(text)); else doubleError(text);
}
