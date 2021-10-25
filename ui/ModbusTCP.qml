import QtQuick 2.12
import QtQuick.Controls 2.12
import "controls"
import UTTEC 1.0
//id
//Declaración de propiedades
//Declaración de señales
//Funciones JavaScript
//Propiedades del Objeto
//Objetos hijos
//Estados
//Transiciones

Rectangle {
    id:root

    color: "Transparent"
    border.color: "#cccccc"
    width:  row2.width  + (2 * row2.anchors.margins)
    height: row2.height + switchAddress.height + (3 * row2.anchors.margins)
    radius: 20

    Host{
        id:host
        address: ipField.text
        port: parseInt(portField.text)
    }

    Switch1 {
        id: switchAddress

        anchors.top: parent.top
        anchors.left: parent.left
        anchors.margins: 50
        labelOn:  qsTr("Enable")
        labelOff: qsTr("Disable")
    }

    Icons {
        id:icono

        anchors.verticalCenter: switchAddress.verticalCenter
        anchors.left: switchAddress.left
        anchors.leftMargin: 260
        enabled: switchAddress.checked
        onClicke:
        {
            status = status ? host.closeConnection() : host.openConnection()
        }
    }
    Row {
        id: row2

        anchors.top: switchAddress.bottom
        anchors.left: parent.left
        anchors.margins: switchAddress.anchors.margins
        spacing: 20

        TextField {
            id:ipField
            readOnly: !switchAddress.checked
            placeholderText: qsTr("192.168.0.1")
            horizontalAlignment: Text.AlignHCenter
            background: Rectangle {
                implicitWidth: 200
                implicitHeight: 40
                radius: height
                color: "white"
                border.color: "white"
            }
            Label {
                anchors.bottom: parent.top
                anchors.bottomMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Network Address")
                color: "White"
                font: ipField.font
            }
        }
        TextField {
            id:portField
            readOnly: !switchAddress.checked
            horizontalAlignment: Text.AlignHCenter
            placeholderText : "502"
            background: Rectangle {
                implicitWidth: 125
                implicitHeight: 40
                radius: height
                color: "white"
                border.color: "white"
            }
            Label {
                anchors.bottom: parent.top
                anchors.bottomMargin: 15
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("Port")
                color: "White"
                font: portField.font
            }
        }
    }
    Label {
        id: titel
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.top
        anchors.bottomMargin: 20
        text: "Modbus TCP"
        color: "white"
        font.pixelSize: 22
    }
}
