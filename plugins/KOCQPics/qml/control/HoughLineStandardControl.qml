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
 * This file defines control for Hough Line Standard                *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version implements for control: Standard trackbar,*
 *        Min threshold                                             *
 *******************************************************************/

import QtQuick 2.0

BasicControl {
    // Properties to control Hough Line Standard
    property int s_trackbar: 150
    property int min_threshold: 50

    // Function to initialize controls
    function initializeControls() {
        addControl("Standard trackbar",    // name
                   0,               // minimum value
                   150,             // maximum value
                   1,               // slider step size
                   s_trackbar,      // current value
                   "s_trackbar")    // property name

        addControl("Min threshold", // name
                   0,               // minimum value
                   100,             // maximum value
                   1,               // slider step size
                   min_threshold,   // current value
                   "min_threshold") // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "s_trackbar") {
            // When s_trackbar is changed
            s_trackbar = newValue
        }else if(currentProperty === "min_threshold") {
            // When min_threshold is changed
            min_threshold = newValue
        }
    }
}
