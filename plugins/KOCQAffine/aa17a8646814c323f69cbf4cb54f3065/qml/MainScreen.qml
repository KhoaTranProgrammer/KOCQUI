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
 * This file is the main qml of KOCQAffine Plugin                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-26-2020                                               *
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

    property string inputFile: ""

    Component.onCompleted: {
        id_loaderWarpControl.source = "WarpControl.qml"

        // Initialize data for new control
        var scene = null
        scene = id_loaderWarpControl.item
        scene.parent = root
        scene.anchors.fill = id_warpcontrolArea
        // Connect signal controlInfor with slot controlInformationUpdate
        scene.controlInfor.connect(controlInformationUpdate)
        // Call initializeControls function
        scene.initializeControls()
    }

    Timer {
        interval: 5; running: true; repeat: false
        onTriggered: {
            inputFile = kocqAffineObject.defaultInput()
            id_imagetxt.text = inputFile
            kocqAffineObject.affineTransforms(inputFile, 0.33, 0.85, 0.15)
            id_warpImage.image = kocqAffineObject.getWarpDst()
            id_warpRotateImage.image = kocqAffineObject.getWarpRotateDst()
        }
    }

    // Area to display Image Select
    Item {
        id: id_imageselectarea
        anchors {
            top: root.top
            left: root.left
        }
        height: root.height * 0.1
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
            }
        }
    }

    // Image link
    Text {
        id: id_imagetxt
        anchors {
            left: id_imageselectarea.right
            right: root.right
            verticalCenter: id_imageselectarea.verticalCenter
        }
        text: "Choose Input"
        font.pixelSize: id_imageselectarea.height * 0.3
        font.bold: true
        color: "black"
    }

    // Area to display warp image
    Rectangle {
        id: id_warpImageArea
        anchors {
            left: parent.left
            bottom: parent.bottom
            top: id_imageselectarea.bottom
        }
        width: parent.width / 2
        color: "transparent"

        KOCQMatImage {
            id: id_warpImage
            anchors.fill: parent
        }
    }

    Rectangle {
        id: id_warpcontrolArea
        anchors {
            left: id_warpImageArea.left
            right: id_warpImageArea.right
            bottom: parent.bottom
        }
        height: id_warpImageArea.height * 0.3
        color: "transparent"
    }

    // Area to display warp rotate
    Rectangle {
        anchors {
            right: parent.right
            bottom: parent.bottom
            top: id_imageselectarea.bottom
        }
        width: parent.width / 2
        color: "transparent"

        KOCQMatImage {
            id: id_warpRotateImage
            anchors.fill: parent
        }
    }

    // FileDialog to select file
    FileDialog {
        id: id_fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            var path = id_fileDialog.fileUrl.toString()
            path = path.replace(/^(file:\/{3})/, "")

            if(Qt.platform.os === "android"){
                inputFile = "/" + path
            } else {
                inputFile = path
            }

            // Update Input image location
            id_imagetxt.text = inputFile
            controlInformationUpdate()
        }
    }

    // Using to open control
    Loader {
        id: id_loaderWarpControl
    }

    // This is processing slot for signal controlInfor
    function controlInformationUpdate() {
        // Variable to get input arguments for DIP features
        var scene = null
        scene = id_loaderWarpControl.item

        kocqAffineObject.affineTransforms(inputFile, scene.point1, scene.point2, scene.point3)
        id_warpImage.image = kocqAffineObject.getWarpDst()
        id_warpRotateImage.image = kocqAffineObject.getWarpRotateDst()
    }
}
