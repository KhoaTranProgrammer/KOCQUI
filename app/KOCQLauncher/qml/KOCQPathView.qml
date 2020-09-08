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
 * This file implements PathView display                            *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Sep-08-2020                                               *
 *        Support PathView                                          *
 *******************************************************************/

import QtQuick 2.0

Item {

    property int itemHeight: parent.height / 3
    property int itemWidth: parent.width / 4

    // Display the list of Plugins
    Component {
        id: id_displayPlugins

        Item {
            width: itemWidth
            height: itemHeight

            Rectangle {

                anchors {
                    fill: parent
                }
                color: "transparent"

                Component.onCompleted: {
                    addIconSignal(parent, "pathview")
                }
            }
        }
    }

    PathView {
        id: id_pathView
        anchors.fill: parent
        path: Path {
            startX: 0
            startY: id_pathView.height * 0.2
            PathQuad { x: id_pathView.width / 2; y: id_pathView.height * 0.8; controlX: 50; controlY: 50 }
            PathQuad { x: id_pathView.width; y: id_pathView.height * 0.2; controlX: 50; controlY: 50 }
        }
    }

    function initDisplay(inputModel) {
        id_pathView.model = inputModel
        id_pathView.delegate = id_displayPlugins
    }

    function show(status) {
        id_pathView.visible = status
    }
}
