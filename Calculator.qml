import QtQuick 2.7

CalculatorForm {
    anchors.fill: parent

    textField.focus: true
    buttonCalc.onClicked: {
        mathEngine.setInputString(textField.text);
        textField.text = mathEngine.calculate();
    }
    Keys.onPressed: {
//                buttonCalc.clicked()
    }
}
