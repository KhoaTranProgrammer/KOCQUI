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
 * This file defines control for Affine Transform                   *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Aug-27-2020                                               *
 *        Initial version implements for control: warp              *
 *******************************************************************/

import QtQuick 2.0

BasicControl {
    // Properties to control Affine Transform
    property double point1: 0.33
    property double point2: 0.85
    property double point3: 0.15

    // Function to initialize controls
    function initializeControls() {
        addControl("Point 1",    // name
                   0,            // minimum value
                   1,            // maximum value
                   0.01,         // slider step size
                   point1,       // current value
                   "point1")     // property name

        addControl("Point 2",       // name
                   0,               // minimum value
                   1.10,            // maximum value
                   0.01,            // slider step size
                   point2,          // current value
                   "point2")        // property name

        addControl("Point 3",       // name
                   0,               // minimum value
                   0.85,            // maximum value
                   0.01,            // slider step size
                   point3,          // current value
                   "point3")        // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "point1") {
            // When point1 is changed
            point1 = newValue
        } else if(currentProperty === "point2") {
            // When point2 is changed
            point2 = newValue
        } else if(currentProperty === "point3") {
            // When point3 is changed
            point3 = newValue
        }
    }
}
