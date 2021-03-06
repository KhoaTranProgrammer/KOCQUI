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
 * This file implements GridView display                            *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-30-2020                                               *
 *        Separate GridView display to KOCQGridView.qml             *
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
                    addIconSignal(parent, "gridview")
                }
            }
        }
    }

    GridView {
        id: id_gridView
        anchors.fill: parent
        cellWidth: itemWidth
        cellHeight: itemHeight

        focus: true
    }

    function initDisplay(inputModel) {
        id_gridView.model = inputModel
        id_gridView.delegate = id_displayPlugins
    }

    function show(status) {
        id_gridView.visible = status
    }
}
