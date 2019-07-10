import QtQuick 2.0
import QtQuick.Controls 2.13
Rectangle {
    id: scrollRectangle
    property color bordercolor: "transparent"
    property color color: "black"

    ScrollView {
        id: scrollView
        anchors.fill: parent
        Rectangle {
            anchors.fill : parent
            color: scrollRectangle.color
        }
        ListModel {
            id: listModel
            ListElement {
                message2log : ""
                message2logLevel : ""
            }
        }
        ListView {
            id: listView
            anchors.bottom: parent.bottom
            width: parent.width
            height: 0
            model: listModel
            delegate: Rectangle {
                border.color: scrollRectangle.bordercolor
                width: scrollRectangle.width
                height: txt.font.pixelSize + (2 * (txt.font.pixelSize >> 3))
                color: "transparent"
                Text {
                    id: txt
                    fontSizeMode: Text.FixedSize
                    anchors.fill: parent
                    text: message2log
                    Component.onCompleted: {
                        if (message2logLevel == "info"){
                            txt.color = "green"
                        } else if (message2logLevel == "debug"){
                            txt.color = "lightblue"
                        } else if (message2logLevel == "fatal"){
                            txt.color = "red"
                        } else if (message2logLevel == "critical"){
                            txt.color = "yellow"
                        }
                    }
                }
                Component.onCompleted: {
                    listView.height = txt.font.pixelSize + txt.topPadding + txt.bottomPadding
                    listView.height *= listModel.count
                }
            }
        }

    }
    function log(message, level = "info"){
        listModel.append({
                        "message2log" : message,
                        "message2logLevel" : level
                    })
    }

    Component.onCompleted: {
        listModel.clear()
    }

}
