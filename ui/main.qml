import QtQuick 2.12
import QtQuick.Controls 2.12
import "controls"
ApplicationWindow {
    id: window
    title: qsTr("QModbus")
    visible: true
    color: "#232527"
    opacity: 0.97
    width: 640
    height: 480

    ModbusTCP {
        id: networkAddress
        anchors.centerIn: parent
    }
}
