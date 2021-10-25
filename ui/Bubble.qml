import QtQuick 2.14
import QtQuick.Window 2.14

Image {
    id: bubble
    source: "qrc:///iconos/bolaNegra.svg"
    smooth: true
    property real centerX
    property real bubbleCenter
    property real centerY
    fillMode: Image.PreserveAspectFit
}
