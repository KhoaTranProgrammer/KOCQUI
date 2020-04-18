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
 * This GUI demonstrates OpenCV drawing and text output functions   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-18-2020                                               *
 *        Initial version supports 8 drawing types.                 *
 *        Supports list of buttons to select the types.             *
 *******************************************************************/

import QtQuick 2.0
import KOCQCoreGUI 1.0
import "Data.js" as Data

Item {
    id: root
    anchors.fill: parent

    property int number: 0
    property int maxNumber: 0
    property string currentType: ""
    property int p_curIndex: -1

    Component.onCompleted: {
        // Load data
        for (var i = 0; i < Data.draw_tyles.length; i+=2) {
            addItems(Data.draw_tyles[i], Data.draw_tyles[i+1])
        }
    }

    KOCQMatImage {
        id: id_outputimage
        anchors.fill: parent
    }

    Timer {
        interval: 50; running: true; repeat: true
        onTriggered: {
            number++
            if(number > maxNumber) number = 0

            if(currentType === Data.Type001) {
                id_outputimage.image = kocqDrawObject.drawingType001(number)
            } else if(currentType === Data.Type002) {
                id_outputimage.image = kocqDrawObject.drawingType002(number)
            } else if(currentType === Data.Type003) {
                id_outputimage.image = kocqDrawObject.drawingType003(number)
            } else if(currentType === Data.Type004) {
                id_outputimage.image = kocqDrawObject.drawingType004(number)
            } else if(currentType === Data.Type005) {
                id_outputimage.image = kocqDrawObject.drawingType005(number)
            } else if(currentType === Data.Type006) {
                id_outputimage.image = kocqDrawObject.drawingType006(number)
            } else if(currentType === Data.Type007) {
                id_outputimage.image = kocqDrawObject.drawingType007(number)
            }
        }
    }

    ListModel {
        id: id_listOfType
    }

    Component {
        id: id_displayDelegate

        Item {
            id: id_delegateItem

            property int p_curIndexOfItem: root.p_curIndex

            height: id_typeArea.width
            width: id_typeArea.width

            Rectangle {
                id: id_delegateItemBg
                anchors.fill: parent
                anchors.margins: parent.width * 0.05
                color: "transparent"

                Image {
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    smooth: true
                    z: 1
                    source: "../images/" + image
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        number = 0
                        if( (drawType === Data.Type001) || (drawType === Data.Type002)
                         || (drawType === Data.Type003) || (drawType === Data.Type004)
                         || (drawType === Data.Type005) || (drawType === Data.Type006)
                         || (drawType === Data.Type007)
                        ) {
                            maxNumber = 100
                        }
                        currentType = drawType
                        root.p_curIndex = index
                    }
                }
            }

            onP_curIndexOfItemChanged: {
                if(p_curIndexOfItem == index){
                    id_delegateItemBg.color = "yellow"
                } else {
                    id_delegateItemBg.color = "transparent"
                }
            }
        }
    }

    Rectangle {
        id: id_typeArea
        anchors {
            top: parent.top
            right: parent.right
            bottom: parent.bottom
        }
        width: parent.width * 0.07
        color: "transparent"

    }

    Flickable {
        id: id_container
        anchors {
            left: id_typeArea.left
            right: id_typeArea.right
            verticalCenter: id_typeArea.verticalCenter
        }
        height: 0
        contentHeight: (id_listOfType.count + 1) * id_typeArea.width
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_listOfType
                delegate: id_displayDelegate
            }
        }
    }

    function addItems(drawType, icon) {
        id_listOfType.append({"drawType": drawType, "image": icon})
        id_container.height = id_listOfType.count * id_typeArea.width
    }
}
