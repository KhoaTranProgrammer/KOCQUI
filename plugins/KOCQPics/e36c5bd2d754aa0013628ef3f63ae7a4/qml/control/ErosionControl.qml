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
 * This file defines control for Erosion                              *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version implements for control: Erosion Elem,     *
 *        Erosion Size                                              *
 *******************************************************************/

import QtQuick 2.0

BasicControl {
    // Properties to control Erosion
    property int  erosion_elem: 0
    property int  erosion_size: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Erosion Elem",  // name
                   0,               // minimum value
                   2,               // maximum value
                   1,               // slider step size
                   erosion_elem,    // current value
                   "erosion_elem")  // property name

        addControl("Erosion Size",  // name
                   0,               // minimum value
                   21,              // maximum value
                   1,               // slider step size
                   erosion_size,    // current value
                   "erosion_size")  // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "erosion_elem") {
            // When erosion elem is changed
            erosion_elem = newValue
        }else if(currentProperty === "erosion_size") {
            // When erosion_size is changed
            erosion_size = newValue
        }
    }
}
