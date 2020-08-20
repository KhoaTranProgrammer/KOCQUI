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
 * This file is the main qml of KOCQSegmentation Plugin             *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-17-2020                                               *
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
    property bool isInputed: false
    property string p_Source: "Source Image"
    property string p_BlackImage: "Black Background Image"
    property string p_LaplaceImage: "Laplace Filtered Image"
    property string p_SharpedImage: "New Sharped Image"
    property string p_BinaryImage: "Binary Image"
    property string p_TransformImage: "Distance Transform Image"
    property string p_PeaksImage: "Peaks"
    property string p_ResultImage: "Final Result"

    Component.onCompleted: {
        addPlugin(p_Source)
        addPlugin(p_BlackImage)
        addPlugin(p_LaplaceImage)
        addPlugin(p_SharpedImage)
        addPlugin(p_BinaryImage)
        addPlugin(p_ResultImage)
    }

    Timer {
        interval: 5; running: true; repeat: false
        onTriggered: {
            inputFile = kocqSegObject.defaultInput()
            id_imagetxt.text = inputFile
            kocqSegObject.imageSegmentation(inputFile)
            isInputed = !isInputed
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

            kocqSegObject.imageSegmentation(inputFile)

            isInputed = !isInputed
        }
    }

    Rectangle {
        id: id_imageArea
        color: "transparent"

        anchors {
            left: parent.left
            right: parent.right
            top: id_imageselectarea.bottom
            bottom: parent.bottom
        }
    }

    // Store the list of images
    ListModel {
        id: id_listImages
    }

    // Display the list of images
    Component {
        id: id_displayImages

        Item {
            height: id_gridView.cellHeight
            width: id_gridView.cellWidth

            Rectangle {
                property bool isInputed: root.isInputed
                id: id_delegateImage
                anchors {
                    left: parent.left
                    right: parent.right
                    top: parent.top
                    margins: 5
                }
                height: parent.height * 0.85
                color: "transparent"

                KOCQMatImage {
                    id: id_image
                    anchors.fill: id_delegateImage
                }

                onIsInputedChanged: {
                    if(title === p_Source){
                        id_image.image = kocqSegObject.getSourceImage()
                    }else if(title === p_BlackImage){
                        id_image.image = kocqSegObject.getBlackImage()
                    }else if(title === p_LaplaceImage){
                        id_image.image = kocqSegObject.getLaplaceImage()
                    }else if(title === p_SharpedImage){
                        id_image.image = kocqSegObject.getSharpedImage()
                    }else if(title === p_BinaryImage){
                        id_image.image = kocqSegObject.getBinaryImage()
                    }else if(title === p_ResultImage){
                        id_image.image = kocqSegObject.getResultImage()
                    }
                }
            }

            Rectangle {
                id: id_delegateText
                anchors {
                    left: parent.left
                    right: parent.right
                    top: id_delegateImage.bottom
                    bottom: parent.bottom
                }
                color: "transparent"

                Text {
                    anchors.centerIn: id_delegateText
                    text: title
                    font.pixelSize: id_delegateText.height * 0.5
                    color: "black"
                    wrapMode: Text.WordWrap
                }
            }
        }
    }

    GridView {
        id: id_gridView
        anchors.fill: id_imageArea
        cellWidth: id_imageArea.width / 3
        cellHeight: id_imageArea.height / 2

        model: id_listImages
        delegate: id_displayImages
    }

    function addPlugin(title) {
        id_listImages.append({"title": title})
    }
}
