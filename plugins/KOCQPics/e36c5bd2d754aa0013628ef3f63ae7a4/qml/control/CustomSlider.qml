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
 * This file defines the custom version of Slider                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version implements to display Minimum, Maximum,   *
 *        Current value                                             *
 *******************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.4

Item {
    id: root

    // Input properties
    property string textValue: ""
    property double currentValue: 128
    property double minValue: 0
    property double maxValue: 255
    property double stepValue: 1
    property int textSize: height * 0.4

    Rectangle {
        id: id_displayarea
        anchors.fill: parent
        color: "transparent"

        // Slider to change value
        Slider {
            id: id_slider
            anchors.fill: parent
            value: currentValue
            minimumValue: minValue
            maximumValue: maxValue
            stepSize: stepValue

            onValueChanged: {
                currentValue = value
            }
        }

        // Text to display Minimum value
        Text {
            anchors {
                right: id_slider.left
                verticalCenter: id_slider.verticalCenter
            }
            text: minValue
            font.pixelSize: textSize
            font.bold: true
            color: "black"
        }

        // Text to display Maximum value
        Text {
            anchors {
                left: id_slider.right
                verticalCenter: id_slider.verticalCenter
            }
            text: maxValue
            font.pixelSize: textSize
            font.bold: true
            color: "black"
        }

        // Text to display Current value
        Text {
            anchors {
                bottom: id_slider.verticalCenter
                bottomMargin: 5
                horizontalCenter: id_displayarea.horizontalCenter
            }
            text: textValue + ": " + currentValue
            font.pixelSize: textSize
            font.bold: true
            color: "black"
        }
    }
}
