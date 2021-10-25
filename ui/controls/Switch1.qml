import QtQuick 2.12
import QtQuick.Controls 2.12

Switch {
    id: control

    property string labelOn:  qsTr("ON")
    property string labelOff: qsTr("OFF")

    //Declaración de señales

    //Funciones JavaScript

    //Propiedades del Objeto
    indicator: Rectangle {
        implicitWidth: 55
        implicitHeight: 30
        radius: height/2
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        color:        control.checked ? "#17a81a" : "#ffffff"
        border.color: "#232527"
        Rectangle {
            width: parent.height
            height:parent.height
            radius:parent.radius
            x: control.checked ? parent.width - width : 0
            color: "#ffffff"
            border.color: parent.border.color
        }
    }
    contentItem: Text {
        text: control.checked ? labelOn : labelOff
        font: control.font
        color: "white"
        verticalAlignment: Text.AlignVCenter
        leftPadding: control.indicator.width + control.spacing
    }

    //Objetos hijos
    //Estados
    //Transiciones
}
