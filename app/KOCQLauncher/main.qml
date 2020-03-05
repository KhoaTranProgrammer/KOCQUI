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
        color: "transparent"

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

        Image {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            fillMode: Image.PreserveAspectFit
            source: "images/close.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Qt.quit()
                }
            }
        }
    }

    Rectangle {
        id: id_pluginArea
        color: "transparent"

        anchors {
            left: parent.left
            right: parent.right
            top: id_menuArea.bottom
            bottom: parent.bottom
        }
    }

    // Background
    gradient: Gradient {
        GradientStop { position: 0.00; color: "#E8F5E9" }
        GradientStop { position: 0.20; color: "#C8E6C9" }
        GradientStop { position: 0.40; color: "#A5D6A7" }
        GradientStop { position: 1.60; color: "#81C784" }
        GradientStop { position: 0.80; color: "#66BB6A" }
        GradientStop { position: 1.00; color: "#4CAF50" }
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
                color: "transparent"

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
        cellHeight: id_pluginArea.height / 4

        model: id_listPlugins
        delegate: id_displayPlugins
        //highlight: Rectangle { color: "lightsteelblue"; radius: 5 }
        focus: true
    }

    function addPlugin() {
        id_listPlugins.append({"name": ""})
    }

    function quitPlugin() {
        
    }
}
