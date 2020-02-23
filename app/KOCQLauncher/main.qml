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

    Loader {
        id: id_myLoader
        anchors.fill: id_pluginArea
        objectName: "PluginLoader"

        onLoaded: {
            id_gridView.visible = false
        }

        onStatusChanged: {
            if (status == Loader.Null) {
                id_gridView.visible = true
            }
        }
    }

    // Store the list of Plugins
    ListModel {
        id: id_listPlugins
    }

    // Display the list of Features
    Component {
        id: id_displayPlugins

        Item {
            height: id_gridView.cellHeight
            width: id_gridView.cellWidth

            Rectangle {

                anchors {
                    fill: parent
                }
                color: "white"

                Component.onCompleted: {
                    addIconSignal(parent)
                }
            }
        }
    }

    GridView {
        id: id_gridView
        anchors.fill: id_pluginArea
        cellWidth: id_pluginArea.width / 6
        cellHeight: id_pluginArea.height / 3

        model: id_listPlugins
        delegate: id_displayPlugins
        highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    function addPlugin() {
        id_listPlugins.append({"name": ""})
    }

    function quitPlugin() {
        
    }
}
