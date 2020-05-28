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
 * This file defines control for Contrast & Brightness              *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version implements for control: Contrast,         *
 *        Brightness                                                *
 *******************************************************************/

import QtQuick 2.0

BasicControl {

    // Properties to control Contrast & Brightness
    property double alpha: 1.0
    property int beta: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Contrast",  // name
                   1.0,         // minimum value
                   3.0,         // maximum value
                   0.1,         // slider step size
                   alpha,       // current value
                   "contrast")  // property name

        addControl("Brightness",    // name
                   0,               // minimum value
                   100,             // maximum value
                   1,               // slider step size
                   beta,            // current value
                   "brightness")    // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "contrast") {
            // When contrast is changed
            alpha = newValue
        }else if(currentProperty === "brightness") {
            // When brightness is changed
            beta = newValue
        }
    }
}
