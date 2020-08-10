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
 * VERSION: 1.0.1 *
 *****************/

/********************************************************************
 * PURPOSE                                                          *
 ********************************************************************
 * This file is the main qml of KOCQQrcode Plugin                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: June-09-2020                                              *
 *        Initial version implements qrrcode detection from image   *
 * 1.0.1: Aug-08-2020                                               *
 *        Supports to detect QRCode using camera input in Windows   *
 *******************************************************************/

import QtQuick 2.0
import QtQuick.Dialogs 1.0
import KOCQrcodeCamFilter 1.0
import QtMultimedia 5.8
import KOCQCoreGUI 1.0

Rectangle {
    id: root

    property string inputFile: ""
    anchors.fill: parent
    color: "transparent"

    Timer {
        interval: 5; running: true; repeat: false
        onTriggered: {
            inputFile = kocqQrcodeObject.defaultInput()
            id_imagetxt.text = inputFile
            id_image.image = kocqQrcodeObject.imageQRCodeDetect(inputFile)
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
                id_Timer.stop()
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

    // Area to display Camera Select
    Item {
        id: id_cameraselectarea
        anchors {
            top: id_imageselectarea.bottom
            left: root.left
        }
        height: root.height * 0.1
        width: height

        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../images/baseline_camera.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_image.clearImage()
                    id_Timer.start()
                    id_imagetxt.text = "Choose Input"
                }
            }
        }
    }

    // Area to display image
    KOCQMatImage {
        id: id_image
        anchors.fill: id_cameraArea

        onDrawingChanged: {
            id_textResult.text = kocqQrcodeObject.qrResult()
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

            id_kocqMat.clearImage()

            // Update Input image location
            id_imagetxt.text = inputFile
            id_image.image = kocqQrcodeObject.openImage(inputFile)
            id_image.image = kocqQrcodeObject.imageQRCodeDetect(inputFile)
        }
    }

    Rectangle {
        id: id_cameraArea
        anchors {
            top: id_imageselectarea.bottom
            bottom: id_resultArea.top
            horizontalCenter: parent.horizontalCenter
        }
        width: parent.width * 0.8
        color: "transparent"
    }

    Rectangle {
        id: id_resultArea
        anchors {
            left: parent.left
            right: parent.right
            bottom: parent.bottom
        }
        height: parent.height * 0.1
        color: "transparent"

        Text {
            id: id_textResult
            anchors.centerIn: id_resultArea
            text: ""
            font.pixelSize: id_resultArea.height * 0.5
            color: "black"
            wrapMode: Text.WordWrap
        }
    }

    KOCQrcodeCamFilter {
        id: id_kocqMat
        anchors.fill: id_cameraArea

        onQrResultChanged: {
            id_textResult.text = qrResult
        }
    }

    Timer {
        id: id_Timer
        interval: 5; running: false; repeat: true
        onTriggered: {
            if (kocqQrcodeObject.getPluginState() === kocqQrcodeObject.getState_PLUGINLOAD()) {
                id_kocqMat.getVideoFrame()
            } else {
                id_Timer.stop()
            }
        }
    }
}
