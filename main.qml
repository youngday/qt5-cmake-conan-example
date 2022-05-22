import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.2
import TaoQuick 1.0
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    CusButton_Blue {
        width: 120
        height: 36
        anchors.centerIn: parent
        text: "Hello"
        onClicked: {
            console.log("hello TaoQuick")
        }
    }
    Button {
        id: button1
        x: 50
        y: 50
        text: "button1"
        onClicked: label1.text = buttonsClicked.button1Clicked()
    }

    Button {
        id: button2
        x: 50
        y: 100
        width: 200
        height: 75
        text: "button2"
        onClicked: label2.text = buttonsClicked.button2Clicked()
    }

    Label {
        id: label1
        x: 50
        y: 200
        text: "button1 clicked 0 times"

    }

    Label {
        id: label2
        x: 50
        y: 230
        text: "button2 clicked 0 times"

    }

}



 
