/*
 * MIT License
 *
 * Copyright (c) 2021 KhoaTran Programmer
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
 * This file is the main qml of KOCQFaceDetection Plugin            *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Feb-13-2021                                               *
 *        Initial version supports for Android                      *
 *******************************************************************/

import QtQuick 2.6
import QtQuick.Dialogs 1.0
import QtQuick.Window 2.2
import KOCQCoreGUI 1.0
import KOCQFaceDetectionCamFilter 1.0
import QtMultimedia 5.8

Rectangle {
    id: root
    anchors.fill: parent
    color: "transparent"

    Camera {
        id: camera
    }

    VideoOutput {
        id: videoOutput
        anchors.fill: parent
        source: camera
        fillMode: VideoOutput.PreserveAspectCrop
        filters: [id_kocqFaceCamFilter]
    }

    KOCQFaceDetectionCamFilter {
        id: id_kocqFaceCamFilter
    }
}