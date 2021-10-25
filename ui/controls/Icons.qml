import QtQuick 2.12
import QtQuick.Controls 2.12

Rectangle {
    id:root

    property url path: "../icons/sokect.png"
    property bool status: false

    signal clicke;

    width: 50
    height: 50
    radius: 10
    color: status ? "#17a81a" : "Transparent";

    Image {
        id: name
        source: path
        anchors.fill: parent
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicke();
    }
}
