/*
 * MIT License
 * 
 * Copyright (c) 2020-2021 KhoaTran Programmer
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/******************
 * VERSION: 1.0.5 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file is the main qml of KOCQLauncher                        *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version uses GridView to store all of Plugins     *
 * 1.0.1: May-29-2020                                               *
 *        Support to load QtQuick.Dialogs, KOCQCoreGUI              *
 *        Change the way to display home and exit button            *
 * 1.0.2: Aug-23-2020                                               *
 *        Support 4 icons per line instead of 6                     *
 * 1.0.3: Aug-30-2020                                               *
 *        Separate GridView display to KOCQGridView.qml             *
 * 1.0.4: Sep-09-2020                                               *
 *        Supports ListView and PathView                            *
 * 1.0.5: Jan-23-2021                                               *
 *        Load Qt Multimedia                                        *
 *******************************************************************/

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.0
import KOCQCoreGUI 1.0
import QtMultimedia 5.0

Rectangle {
    id: root
    anchors.fill: parent
    color: "black"

    signal addIconSignal(var anObject, string type)
    signal homeSignal()

    Component.onCompleted: {
        // Display as gridview
        id_viewControl.source = "qml/KOCQGridView.qml"
        id_gridviewOption.color = "white"

        var scene = null
        scene = id_viewControl.item
        scene.parent = root
        scene.anchors.fill = id_pluginArea
        scene.initDisplay(id_listPlugins)
        scene.show(true)

    }

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
            width: height
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
            width: height
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
        id: id_optionArea
        color: "transparent"

        anchors {
            left: parent.left
            right: parent.right
            top: id_menuArea.bottom
        }
        height: parent.height * 0.05

        // Gridview Option
        Rectangle {
            id: id_gridviewOption
            color: "transparent"

            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            width: height

            Image {
                anchors.fill: parent
                source: "images/gridview.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_gridviewOption.color = "white"
                    id_listviewOption.color = "transparent"
                    id_pathviewOption.color = "transparent"

                    id_viewControl.source = "qml/KOCQGridView.qml"
                    id_gridviewOption.color = "white"

                    var scene = null
                    scene = id_viewControl.item
                    scene.parent = root
                    scene.anchors.fill = id_pluginArea
                    scene.initDisplay(id_listPlugins)
                }
            }
        }

        // Listview Option
        Rectangle {
            id: id_listviewOption
            color: "transparent"

            anchors {
                right: id_gridviewOption.left
                top: parent.top
                bottom: parent.bottom
            }
            width: height

            Image {
                anchors.fill: parent
                source: "images/listview.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_gridviewOption.color = "transparent"
                    id_listviewOption.color = "white"
                    id_pathviewOption.color = "transparent"

                    id_viewControl.source = ""
                    id_viewControl.source = "qml/KOCQListView.qml"
                    var scene = null
                    scene = id_viewControl.item
                    scene.parent = root
                    scene.anchors.fill = id_pluginArea
                    scene.initDisplay(id_listPlugins)
                }
            }
        }

        // Pathview Option
        Rectangle {
            id: id_pathviewOption
            color: "transparent"

            anchors {
                right: id_listviewOption.left
                top: parent.top
                bottom: parent.bottom
            }
            width: height

            Image {
                anchors.fill: parent
                source: "images/pathview.png"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_gridviewOption.color = "transparent"
                    id_listviewOption.color = "transparent"
                    id_pathviewOption.color = "white"

                    id_viewControl.source = ""
                    id_viewControl.source = "qml/KOCQPathView.qml"
                    var scene = null
                    scene = id_viewControl.item
                    scene.parent = root
                    scene.anchors.fill = id_pluginArea
                    scene.initDisplay(id_listPlugins)
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
            top: id_optionArea.bottom
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
            var scene = null
            scene = id_viewControl.item
            scene.show(false)
            id_optionArea.visible = false
        }

        onStatusChanged: {
            if (status == Loader.Null) {
                var scene = null
                scene = id_viewControl.item
                scene.show(true)
                id_optionArea.visible = true
            }
        }
    }

    // Store the list of Plugins
    ListModel {
        id: id_listPlugins
    }

    function addPlugin() {
        id_listPlugins.append({"name": ""})
    }

    function quitPlugin() {
        
    }

    // Using to open view control
    Loader {
        id: id_viewControl
    }
}
