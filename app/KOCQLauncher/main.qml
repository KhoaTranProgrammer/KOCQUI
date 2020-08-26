/*
 * MIT License
 * 
 * Copyright (c) 2020 KhoaTran Programmer
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
 * VERSION: 1.0.2 *
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
 *******************************************************************/

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.0
import KOCQCoreGUI 1.0

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
        cellWidth: id_pluginArea.width / 4
        cellHeight: id_pluginArea.height / 3

        model: id_listPlugins
        delegate: id_displayPlugins
        focus: true
    }

    function addPlugin() {
        id_listPlugins.append({"name": ""})
    }

    function quitPlugin() {
        
    }
}
