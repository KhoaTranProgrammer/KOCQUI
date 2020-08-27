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
 * This file defines basic control and intend to use by others.     *
 * It supports many CustomSlider                                    *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version                                           *
 *        May-31-2020                                               *
 *        Update Slider Height from quater to half of parent        *
 *******************************************************************/

import QtQuick 2.0

Item {
    id: root
    anchors.fill: parent

    // Image information
    property int inputWidth: 0
    property int inputHeight: 0

    // The height of each control
    property int sliderHeight: height / 3

    // Properties to update new value for property
    property double newValue: 0
    property string currentProperty: ""

    // Signal to announce when control information are updated
    signal controlInfor

    // Store the list of Controls
    ListModel {
        id: id_listOfControls
    }

    // Display the list of Controls
    Component {
        id: id_displayControls

        Item {
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            height: sliderHeight
            width: parent.width * 3 / 4

            // The CustomSlider is used for user to control feature
            CustomSlider {
                anchors.fill: parent

                // Setting input for CustomSlider
                textValue: name
                currentValue: currentV
                minValue: minV
                maxValue: maxV
                stepValue: stepV

                // When user changes value of Slider
                onCurrentValueChanged: {
                    // Update the name of property that is changed
                    currentProperty = propertyName

                    // New value of changed property
                    newValue = currentValue

                    // Call updateProperties function
                    updateProperties()

                    // Emit controlInfor signal
                    controlInfor()
                }
            }
        }
    }

    // Apply Scroll View for Control List
    Flickable {
        anchors.fill: parent
        contentHeight: id_listOfControls.count * sliderHeight
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_listOfControls
                delegate: id_displayControls
            }
        }
    }

    // Function to add control into the list of Controls
    function addControl(name, minV, maxV, stepV, currentV, propertyName) {
        id_listOfControls.append({"name": name,
                                  "minV": minV,
                                  "maxV": maxV,
                                  "stepV": stepV,
                                  "currentV": currentV,
                                  "propertyName": propertyName
                                 })
    }
}
