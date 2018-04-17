import QtQuick 2.4
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Item {
    width: 400
    height: 400

    property alias buttonCalc: buttonCalc
    property alias textField: textField

    Rectangle {
        id: rectangle
        color: "#ffffff"
        anchors.fill: parent

        GridLayout {
            id: grid
            anchors.rightMargin: 5
            anchors.bottomMargin: 5
            anchors.leftMargin: 5
            anchors.topMargin: 5
            columnSpacing: 5
            rowSpacing: 5
            anchors.fill: parent

            TextField {
                id: textField
                placeholderText: "Input math"
                horizontalAlignment: TextInput.Left
                Material.accent: Material.Blue

                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.columnSpan: 4
                Layout.column: 1
                Layout.row: 0
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 1

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonLBrac
                text: qsTr("(")
                onClicked: textField.text += buttonLBrac.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 2
                Layout.row: 1

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonRBrac
                text: qsTr(")")
                onClicked: textField.text += buttonRBrac.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 3
                Layout.row: 1

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonRemOfDiv
                text: qsTr("%")
                onClicked: textField.text += buttonRemOfDiv.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 4
                Layout.row: 1

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonPow
                text: qsTr("^")
                onClicked: textField.text += buttonPow.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 2
                id: button7
                text: qsTr("7")
                onClicked: textField.text += button7.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 2
                Layout.row: 2
                id: button8
                text: qsTr("8")
                onClicked: textField.text += button8.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 3
                Layout.row: 2
                id: button9
                text: qsTr("9")
                onClicked: textField.text += button9.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 4
                Layout.row: 2

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonDev
                text: qsTr("/")
                onClicked: textField.text += buttonDev.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 3
                id: button4
                text: qsTr("4")
                onClicked: textField.text += button4.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 2
                Layout.row: 3
                id: button5
                text: qsTr("5")
                onClicked: textField.text += button5.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 3
                Layout.row: 3
                id: button6
                text: qsTr("6")
                onClicked: textField.text += button6.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 4
                Layout.row: 3

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonMul
                text: qsTr("*")
                onClicked: textField.text += buttonMul.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 4
                id: button1
                text: qsTr("1")
                onClicked: textField.text += button1.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 2
                Layout.row: 4
                id: button2
                text: qsTr("2")
                onClicked: textField.text += button2.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 3
                Layout.row: 4
                id: button3
                text: qsTr("3")
                onClicked: textField.text += button3.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 4
                Layout.row: 4

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonSub
                text: qsTr("-")
                onClicked: textField.text += buttonSub.text
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 1
                Layout.row: 5
                id: button0
                text: qsTr("0")
                onClicked: textField.text += button0.text
            }
            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 2
                Layout.row: 5

                id: buttonDot
                text: qsTr(".")
                onClicked: textField.text += buttonDot.text
            }
            Button {
                Material.accent: Material.Blue
                highlighted: true
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 3
                Layout.row: 5
                id: buttonCalc
                text: qsTr("=")
            }

            Button {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.column: 4
                Layout.row: 5

                highlighted: true
                Material.accent: Material.BlueGrey
                id: buttonAdd
                text: qsTr("+")
                onClicked: textField.text += buttonAdd.text
            }
        }
    }
}
