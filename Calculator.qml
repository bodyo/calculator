import QtQuick 2.4

CalculatorForm {
    anchors.fill: parent

    buttonCalc.onClicked: {
        mathEngine.setInputString(textField.text);
        textField.text = mathEngine.calculateInputString();
    }
}
