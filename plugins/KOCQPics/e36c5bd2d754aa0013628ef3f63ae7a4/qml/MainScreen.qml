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
 * This file is the main qml of KOCQPics Plugin                     *
 *******************************************************************/

/********************************************************************
 * VERSION HISTORY                                                  *
 ********************************************************************
 * 1.0.0: Apr-05-2020                                               *
 *        Initial version implements for some algorithms:           *
 *        LinearTransforms, Negatives, GammaCorrection, Erosion,    *
 *        Dilation, Morphology, Drawing, Smoothing, Threshold,      *
 *        Transforms, Hough                                         *
 *******************************************************************/

import QtQuick 2.0
import QtQuick.Dialogs 1.0
import KOCQCoreGUI 1.0
import "Common.js" as Common
import "control"

Rectangle {
    id: root
    anchors.fill: parent

    // Current feature is selected by user
    property string current_feature: ""

    // This property is changed when Feature is updated
    property bool refreshfeature: false

    // Decide input or output is selected
    property bool isChooseInput: false

    // Hold status of detail information is displayed or not
    property bool isClickedDetail: false

    // Default input image
    property string inputimage: ""
    property bool isUsedDefaultInput: true

    QtObject {
        id: id_data

        // Used to indicate the group status is clicked or not
        property var groupstatus: []
        property int numberofgroup: 0
    }

    Component.onCompleted: {
        // Load the Features into the screen
        for (var i = 0 ; i < Common.group_list.length; i++ ) {
            for (var j = 0 ; j < Common.group_list[i].length; j+=3 ) {
                /*
                  Add features to model as template:
                   feature: feature name
                   control: control GUI
                   groupstatusindex: status of parent group
                */
                id_listFeatures.append({"feature": Common.group_list[i][j], "control": Common.group_list[i][j + 1], "groupstatusindex": id_data.numberofgroup, "description": Common.group_list[i][j + 2]})
            }

            // Group status is closed as default
            id_data.groupstatus[id_data.numberofgroup] = false
            id_data.numberofgroup++
        }
    }

    // Background
    gradient: Gradient {
        GradientStop { position: 0.00; color: "#78909C" }
        GradientStop { position: 0.33; color: "#607D8B" }
        GradientStop { position: 0.66; color: "#546E7A" }
        GradientStop { position: 1.00; color: "#455A64" }
    }

    // Area for application name
    Rectangle {
        id: id_appnamearea
        anchors {
            top: root.top
            left: root.left
        }
        width: root.width * 0.2
        height: root.height * 0.1
        color: "transparent"

        Text {
            anchors.fill: parent
            text: "Image Processing In OpenCV"
            font.pixelSize: parent.height / 3
            font.bold: true
            color: "black"
        }
    }

    // Area for input/output selection
    Rectangle {
        id: id_inoutarea
        anchors {
            top: root.top
            horizontalCenter: root.horizontalCenter
        }
        width: root.width * 0.5
        height: root.height * 0.1
        color: "transparent"

        // Button to select Input Image
        Rectangle {
            anchors {
                left: parent.left
                top: parent.top
                margins: parent.height * 0.03
            }
            width: parent.width * 0.25
            height: parent.height * 0.45
            radius: parent.height

            // Static text to display "Choose Input"
            Text {
                anchors.centerIn: parent
                text: "Choose Input"
                font.pixelSize: parent.height * 0.5
                font.bold: true
                color: "black"
            }

            // When user clicks, display FileDialog and announce Input is selected
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_fileDialog.visible = true
                    isChooseInput = true
                }
            }
        }

        // Display Input File Name
        Rectangle {
            anchors {
                right: parent.right
                top: parent.top
                margins: parent.height * 0.03
            }
            width: parent.width * 0.74
            height: parent.height * 0.45
            radius: parent.height

            // Text to display full input image location
            Text {
                id: id_inputlocation
                anchors {
                    left: parent.left
                    leftMargin: parent.height * 0.2
                    verticalCenter: parent.verticalCenter
                }
                text: "../image/lena.jpg"
                font.pixelSize: parent.height * 0.3
                color: "black"
                wrapMode: Text.WordWrap
            }
        }
    }

    // Area to list up features
    Rectangle {
        id: id_featurearea
        anchors {
            top: id_appnamearea.bottom
            left: root.left
            bottom: root.bottom
        }
        width: root.width * 0.12
        color: "transparent"
    }

    // Area to display input image
    Rectangle {
        id: id_inputimagearea
        anchors {
            top: id_appnamearea.bottom
            left: id_featurearea.right
        }
        width: root.width * 0.44
        height: root.height * 0.7
        color: "transparent"

        Image {
            id: id_inputimage
            anchors.fill: parent
            fillMode: Image.PreserveAspectFit
            source: "../image/lena.jpg"
        }
    }

    // Area to display output image
    Rectangle {
        id: id_outputimagearea
        anchors {
            top: id_appnamearea.bottom
            right: root.right
        }
        width: root.width * 0.44
        height: root.height * 0.7
        color: "transparent"

        KOCQMatImage {
            id: id_outputimage
            anchors.fill: parent
        }
    }

    // Area to display information of each feature
    Rectangle {
        id: id_informationarea
        anchors {
            bottom: root.bottom
            left: id_featurearea.right
            top: id_inputimagearea.bottom
        }
        width: root.width * 0.50
        color: "transparent"

        Rectangle {
            anchors{
                fill: parent
                margins: parent.height * 0.05
            }
            color: "white"
            opacity: 0.4
        }

        // Static text displays string "Description"
        Text {
            id: id_textstatic
            anchors {
                top: parent.top
                topMargin: parent.height * 0.05
                horizontalCenter: parent.horizontalCenter
            }
            text: "Description"
            font.pixelSize: parent.height * 0.2
            font.bold: true
            color: "black"
        }

        Rectangle {
            anchors {
                top: id_textstatic.bottom
                left: parent.left
                right: parent.right
                bottom: parent.bottom
                margins: parent.height * 0.06
            }
            color: "transparent"

            // Text to display information of feature
            Text {
                id: id_textdescription
                anchors.fill: parent
                text: ""
                font.pixelSize: id_informationarea.height * 0.1
                color: "black"
                wrapMode: Text.WordWrap
            }
        }
    }

    // Area to control of each feature
    Rectangle {
        id: id_controlarea
        anchors {
            bottom: root.bottom
            left: id_informationarea.right
            top: id_inputimagearea.bottom
            right: root.right
            margins: id_informationarea.height * 0.05
        }
        color: "white"
        opacity: 0.4
        radius: height * 0.2
    }

    // Store the list of Features
    ListModel {
        id: id_listFeatures
    }

    // Display the list of Features
    Component {
        id: id_displayFeatures

        Item {
            // By default, only display GroupItem(parent).
            // The feature(children) will be displayed when user select
            height: (control == Common.GroupItem) ? id_featurearea.height / 20 : 0
            width: id_featurearea.width

            // Button to display Group Icon
            Rectangle {
                id: id_groupicon

                // Internal property to receive Feature list refresh signal
                property bool isRefresh: refreshfeature

                anchors {
                    left: parent.left
                    top: parent.top
                    bottom: parent.bottom
                    leftMargin: 2
                    topMargin: 2
                    bottomMargin: 2
                }
                width: parent.width * 0.1
                // Only visible for GroupItem
                visible: (control == Common.GroupItem) ? true : false

                // Status Image
                Image {
                    id: id_groupiconstatus
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectFit
                    source: '../image/groupclose.png'
                }

                // Processing when user clicks
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        // Update group status
                        id_data.groupstatus[groupstatusindex] = !id_data.groupstatus[groupstatusindex]

                        // Announce feature list is refreshed
                        root.refreshfeature = !root.refreshfeature
                    }
                }

                // Catch up feature list is refreshed
                onIsRefreshChanged: {
                    if(id_data.groupstatus[groupstatusindex]) {
                        // When group is opened
                        id_groupiconstatus.source = '../image/groupopen.png'
                    }else{
                        // When group is closed
                        id_groupiconstatus.source = '../image/groupclose.png'
                    }
                }
            }

            // Button to display Group Item or Feature Item
            Rectangle {
                // Internal property to receive Feature list refresh signal
                property bool isRefresh: refreshfeature

                anchors {
                    left: id_groupicon.right
                    top: parent.top
                    bottom: parent.bottom
                    right: parent.right
                    rightMargin: 2
                    topMargin: 2
                    bottomMargin: 2
                }
                color: (current_feature == feature) ? "black" : "white"
                // By defaut, only group items are displayed
                visible: (control == Common.GroupItem) ? true : false
                radius: (control == Common.GroupItem) ? 0 : parent.height * 0.5

                // Catch up feature list is refreshed
                onIsRefreshChanged: {
                    if(control == Common.GroupItem){
                        // visible when GroupItem is selected
                        visible = true
                    }else if(id_data.groupstatus[groupstatusindex]){
                        // visible when GroupItem status is opened
                        visible = true
                        parent.height = id_featurearea.height / 20
                    }else{
                        // invisible when GroupItem status is closed
                        visible = false
                        parent.height = 0
                    }
                }

                // Text to display feature name
                Text {
                    anchors.centerIn: parent
                    text: feature
                    font.pixelSize: 20
                    font.bold: (control == Common.GroupItem) ? true : false
                    color: (current_feature == feature) ? "white" : "black"
                }

                // Processing when user clicks
                MouseArea {
                    anchors.fill: parent

                    onClicked: {
                        if(control == Common.GroupItem){
                            // Click on GroupItem
                            id_data.groupstatus[groupstatusindex] = !id_data.groupstatus[groupstatusindex]
                        }

                        // Update and refresh feature
                        root.refreshfeature = !root.refreshfeature
                        current_feature = feature

                        // Load feature
                        if(control != Common.GroupItem){ // Click on none group item
                            // Clear old control
                            id_loaderControl.source = ""
                            id_textdescription.text = description
                            if(control != ""){
                                // Setting new control
                                id_loaderControl.source = "control/" + control

                                // Initialize data for new control
                                var scene = null
                                scene = id_loaderControl.item
                                scene.parent = root
                                scene.anchors.fill = id_controlarea
                                // Connect signal controlInfor with slot controlInformationUpdate
                                scene.controlInfor.connect(controlInformationUpdate)
                                // Call initializeControls function
                                scene.initializeControls()
                            }
                            executeDIPFeatures()
                        }
                    }
                }
            }
        }
    }

    // Apply Scroll View for Features List
    Flickable {
        id: id_scrollview
        anchors.fill: id_featurearea
        contentHeight: id_listFeatures.count * (id_featurearea.height / 20)
        clip: true

        Column {
            anchors.fill: parent
            Repeater {
                model: id_listFeatures // ListModel
                delegate: id_displayFeatures // Component delegate
            }
        }
    }

    // Using to open control
    Loader {
        id: id_loaderControl
    }

    // FileDialog to select file
    FileDialog {
        id: id_fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            var path = id_fileDialog.fileUrl.toString()
            path = path.replace(/^(file:\/{3})/, "")
            // Update Input image location
            inputimage = decodeURIComponent(path)
            isUsedDefaultInput = false
            id_inputimage.source = id_fileDialog.fileUrl
            id_inputlocation.text = inputimage
        }
    }

    // Function to call Digital Image Processing features
    function executeDIPFeatures() {
        // In case of use default input image
        if(isUsedDefaultInput){
            inputimage = defaultinput + "/image/lena.jpg"
        }

        // Variable to get input arguments for DIP features
        var scene = null
        scene = id_loaderControl.item

        // The feature is decided by global property current_feature
        if(current_feature == Common.BaLiTrans){
            id_outputimage.image = dipObject.basicLinearTransforms(inputimage, scene.alpha, scene.beta)
        } else if (current_feature == Common.Negative) {
            id_outputimage.image = dipObject.imageNegatives(inputimage)
        } else if (current_feature == Common.GammaCor) {
            id_outputimage.image = dipObject.gammaCorrection(inputimage, scene.gamma_cor)
        } else if (current_feature == Common.Erosion) {
            id_outputimage.image = dipObject.erosion(inputimage, scene.erosion_elem, scene.erosion_size)
        } else if (current_feature == Common.Dilation) {
            id_outputimage.image = dipObject.dilation(inputimage, scene.dilation_elem, scene.dilation_size)
        } else if (current_feature == Common.AdvMorpho) {
            id_outputimage.image = dipObject.morphologyOperations(inputimage, scene.morph_elem, scene.morph_size, scene.morph_operator)
        } else if (current_feature == Common.Drawing1) {
            id_outputimage.image = dipObject.simpleDrawing1()
        } else if (current_feature == Common.Drawing2) {
            id_outputimage.image = dipObject.simpleDrawing2()
        } else if (current_feature == Common.HomogeneousBlur) {
            id_outputimage.image = dipObject.homogeneousBlur(inputimage, scene.kernel_length)
        } else if (current_feature == Common.GaussianBlur) {
            id_outputimage.image = dipObject.gaussianBlur(inputimage, scene.kernel_length)
        } else if (current_feature == Common.MedianBlur) {
            id_outputimage.image = dipObject.medianFilterBlur(inputimage, scene.kernel_length)
        } else if (current_feature == Common.BilateralFilter) {
            id_outputimage.image = dipObject.bilateralFilterBlur(inputimage, scene.kernel_length)
        } else if (current_feature == Common.ThresholdDemo) {
            id_outputimage.image = dipObject.threshold_Demo(inputimage, scene.threshold_value, scene.threshold_type)
        } else if (current_feature == Common.CopyMakeBorder) {
            id_outputimage.image = dipObject.copyMakeBorder_Demo(inputimage, scene.borderType)
        } else if (current_feature == Common.SobelDemo) {
            id_outputimage.image = dipObject.sobel_Demo(inputimage, scene.ksize, scene.scale, scene.delta)
        } else if (current_feature == Common.LaplaceDemo) {
            id_outputimage.image = dipObject.laplacian_Demo(inputimage, scene.ksize, scene.scale, scene.delta)
        } else if (current_feature == Common.CannyDetector) {
            id_outputimage.image = dipObject.canny_Demo(inputimage, scene.threshold)
        } else if (current_feature == Common.HoughLineStandard) {
            id_outputimage.image = dipObject.standardHoughLines(inputimage, scene.s_trackbar, scene.min_threshold)
        } else if (current_feature == Common.HoughLineProbabilistic) {
            id_outputimage.image = dipObject.probabilisticHoughLines(inputimage, scene.p_trackbar, scene.min_threshold)
        } else if (current_feature == Common.HoughCircles) {
            id_outputimage.image = dipObject.houghCirclesDetection(inputimage, scene.cannyThreshold, scene.accumulatorThreshold)
        } else if (current_feature == Common.Remapping) {
            id_outputimage.image = dipObject.remapping(inputimage, scene.types)
        }
    }

    // This is processing slot for signal controlInfor
    function controlInformationUpdate() {
        executeDIPFeatures()
    }
}
