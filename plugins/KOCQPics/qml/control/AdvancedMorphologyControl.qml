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
 * This file defines control for Advanced Morphology                *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version implements for control: Morph Elem,       *
 *        Morph Size, Morph Operator                                *
 *******************************************************************/

import QtQuick 2.0

BasicControl {
    // Properties to control Advanced Morphology
    property int morph_elem: 0
    property int morph_size: 0
    property int morph_operator: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Morph Elem",    // name
                   0,               // minimum value
                   2,               // maximum value
                   1,               // slider step size
                   morph_elem,      // current value
                   "morph_elem")    // property name

        addControl("Morph Size",    // name
                   0,               // minimum value
                   21,              // maximum value
                   1,               // slider step size
                   morph_size,      // current value
                   "morph_size")    // property name

        addControl("Morph Operator",    // name
                   0,                   // minimum value
                   4,                   // maximum value
                   1,                   // slider step size
                   morph_operator,      // current value
                   "morph_operator")    // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "morph_elem") {
            // When morph elem is changed
            morph_elem = newValue
        } else if(currentProperty === "morph_size") {
            // When morph size is changed
            morph_size = newValue
        } else if(currentProperty === "morph_operator") {
            // When morph operator is changed
            morph_operator = newValue
        }
    }
}
