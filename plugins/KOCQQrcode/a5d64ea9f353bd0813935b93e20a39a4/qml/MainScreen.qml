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
 * This file is the main qml of KOCQQrcode Plugin                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: June-09-2020                                              *
 *        Initial version implements qrrcode detection from image   *
 *******************************************************************/

import QtQuick 2.0
import QtQuick.Dialogs 1.0
import KOCQCoreGUI 1.0

Rectangle {
    id: root

    property string inputFile: ""
    anchors.fill: parent
    color: "transparent"

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
        }
    }

    // Area to display Camera Select
    Item {
        id: id_detectQR
        anchors {
            top: id_diplayimagearea.bottom
            bottom: root.bottom
            horizontalCenter: root.horizontalCenter
        }
        width: height

        Image {
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../images/qr_code.png"

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_image.image = kocqQrcodeObject.imageQRCodeDetect(inputFile)
                }
            }
        }
    }

    // Area to display image
    Item {
        id: id_diplayimagearea
        anchors {
            top: id_cameraselectarea.top
            left: id_cameraselectarea.right
            right: root.right
        }
        height: root.height * 0.8

        KOCQMatImage {
            id: id_image
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
            id_image.image = kocqQrcodeObject.openImage(inputFile)
        }
    }
}
