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
 * 1.0.0: Aug-31-2020                                               *
 *        Support ListView                                          *
 *******************************************************************/

import QtQuick 2.0

Item {

    property int itemHeight: parent.height / 3
    // Display the list of Plugins
    Component {
        id: id_displayPlugins

        Item {
            width: parent.width
            height: itemHeight

            Rectangle {

                anchors {
                    fill: parent
                }
                color: "transparent"

                Component.onCompleted: {
                    addIconSignal(parent, "listview")
                }
            }
        }
    }

    Flickable {
        id: id_listView
        anchors.fill: parent
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                id: id_repeater
            }
        }
    }

    function initDisplay(inputModel) {
        id_repeater.model = inputModel
        id_repeater.delegate = id_displayPlugins
        id_listView.contentHeight = inputModel.count * itemHeight
    }

    function show(status) {
        id_listView.visible = status
    }
}
