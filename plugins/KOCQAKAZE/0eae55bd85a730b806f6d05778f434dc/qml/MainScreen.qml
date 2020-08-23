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
 * VERSION: 1.0.0 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file is the main qml of KOCQAKAZE Plugin                    *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-22-2020                                               *
 *        Initial version supports for Windows                      *
 *******************************************************************/

import QtQuick 2.6
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import KOCQCoreGUI 1.0

Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"

    property string inputFile1: ""
    property string inputFile2: ""
    property string inputHomography: ""

    Timer {
        interval: 5; running: true; repeat: false
        onTriggered: {
            inputFile1 = kocqAkazeObject.defaultInputImage_1()
            id_image1txt.text = inputFile1

            inputFile2 = kocqAkazeObject.defaultInputImage_2()
            id_image2txt.text = inputFile2

            inputHomography = kocqAkazeObject.defaultHomography()
            id_homographytxt.text = inputHomography

            id_image.image = kocqAkazeObject.AKAZE_match(inputFile1, inputFile2, inputHomography)

            id_matchingResult.text = kocqAkazeObject.getMatchingResults()
        }
    }

    // Area to display Image1 Select
    Item {
        id: id_image1selectarea
        anchors {
            top: root.top
            left: root.left
        }
        height: root.height * 0.05
        width: height

        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../images/baseline_image.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                id_fileDialog.visible = true
                inputFile1 = ""
                id_image1txt.text = inputFile1
            }
        }
    }

    // Image1 link
    Text {
        id: id_image1txt
        anchors {
            left: id_image1selectarea.right
            right: root.right
            verticalCenter: id_image1selectarea.verticalCenter
        }
        text: "Choose Input"
        font.pixelSize: id_image1selectarea.height * 0.3
        font.bold: true
        color: "black"
    }

    // Area to display Image2 Select
    Item {
        id: id_image2selectarea
        anchors {
            top: id_image1selectarea.bottom
            left: root.left
        }
        height: root.height * 0.05
        width: height

        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../images/baseline_image.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                id_fileDialog.visible = true
                inputFile2 = ""
                id_image2txt.text = inputFile2
            }
        }
    }

    // Image2 link
    Text {
        id: id_image2txt
        anchors {
            left: id_image2selectarea.right
            right: root.right
            verticalCenter: id_image2selectarea.verticalCenter
        }
        text: "Choose Input"
        font.pixelSize: id_image2selectarea.height * 0.3
        font.bold: true
        color: "black"
    }

    // Area to display Homography Select
    Item {
        id: id_homographyselectarea
        anchors {
            top: id_image2selectarea.bottom
            left: root.left
        }
        height: root.height * 0.05
        width: height

        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../images/baseline_image.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                id_fileDialog.visible = true
                inputHomography = ""
                id_homographytxt.text = inputHomography
            }
        }
    }

    // Homography link
    Text {
        id: id_homographytxt
        anchors {
            left: id_homographyselectarea.right
            right: root.right
            verticalCenter: id_homographyselectarea.verticalCenter
        }
        text: "Choose Input"
        font.pixelSize: id_homographyselectarea.height * 0.3
        font.bold: true
        color: "black"
    }

    // Matching result
    Text {
        id: id_matchingResult
        anchors {
            right: parent.right
            top: top.top
        }
        text: ""
        font.pixelSize: id_image1selectarea.height * 0.7
        font.bold: true
        color: "yellow"
    }

    // Area to display image
    KOCQMatImage {
        id: id_image
        anchors.fill: parent
        z: -1
    }

    // FileDialog to select file
    FileDialog {
        id: id_fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            id_image.clearImage()
            id_matchingResult.text = ""

            var path = id_fileDialog.fileUrl.toString()
            path = path.replace(/^(file:\/{3})/, "")

            if(Qt.platform.os === "android"){
                path = "/" + path
            }

            // Update Input data
            if(inputFile1 == "") {
                inputFile1 = path
                id_image1txt.text = inputFile1
            } else if(inputFile2 == "") {
                inputFile2 = path
                id_image2txt.text = inputFile2
            } else if(inputHomography == "") {
                inputHomography = path
                id_homographytxt.text = inputHomography
            }
        }
    }

    // Area to display Done button
    Item {
        id: id_donearea
        anchors {
            bottom: root.bottom
            horizontalCenter: root.horizontalCenter
        }
        height: root.height * 0.1
        width: height

        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../images/baseline_done_all_black.png"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                id_image.image = kocqAkazeObject.AKAZE_match(inputFile1, inputFile2, inputHomography)
                id_matchingResult.text = kocqAkazeObject.getMatchingResults()
            }
        }
    }
}
