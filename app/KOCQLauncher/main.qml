import QtQuick 2.6
import QtQuick.Window 2.2

Rectangle {
    id: root
    anchors.fill: parent
    color: "black"

    signal addIconSignal(var anObject)
    signal homeSignal()

    Rectangle {
        id: id_menuArea

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }
        height: parent.height * 0.1

        Image {
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
            }
            fillMode: Image.PreserveAspectFit
            source: "images/home.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    homeSignal()
                }
            }
        }
    }

    Rectangle {
        id: id_pluginArea

        anchors {
            left: parent.left
            right: parent.right
            top: id_menuArea.bottom
            bottom: parent.bottom
        }
    }
}
