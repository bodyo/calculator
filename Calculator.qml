import QtQuick 2.7

CalculatorForm {
    anchors.fill: parent

    textField.focus: true
    buttonCalc.onClicked: {
        textField.text = mathEngine.calculate(textField.text);
    }
    Keys.onPressed: {
//                buttonCalc.clicked()
    }
}
