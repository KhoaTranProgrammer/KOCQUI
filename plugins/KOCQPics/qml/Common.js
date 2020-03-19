// Name of features are used by QML
// current_feature will be updated each time user selects feature
var GroupItem = "GroupItem"

// Basic drawing
var Drawing1 = "Drawing 1"
var Drawing2 = "Drawing 2"

// Some Basic Intensity Transformation Functions
var BaLiTrans = "Contrast&Brightness"
var Negative = "ImageNegative"
var GammaCor = "GammaCorrection"

// Morphological Image Processing
var Erosion = "Erosion"
var Dilation = "Dilation"
var AdvMorpho = "Advanced Morphology"

/*
 Group format
  + GroupItem: this is parent of group, just display group name
  + FeatureItem(s): they are detail Features in group
*/

/*
 GroupItem format
  + GroupName: this is the name of Feature
  + Control: group do not need control GUI
  + Description: group do not need description
*/

/*
 FeatureItem format
  + FeatureName: this is the name of Feature
  + Control: this is GUI to contron Feature arguments
  + Description: this is the introduction about Feature
*/

// Group of Drawing
var group_basicDrawing = [
    /* GroupItem */ "Basic Drawing", GroupItem, "",
    /* FeatureItem */ Drawing1, "", "Simple drawing 1",
    /* FeatureItem */ Drawing2, "", "Simple drawing 2",
]

// Group of Basic Intensity
var group_basicintensity = [
    /* GroupItem */ "Basic Intensity", GroupItem, "",
    /* FeatureItem */ Negative, "", "Inverts every bit of an array",
    /* FeatureItem */ GammaCor, "GammaCorrectionControl.qml", "Gamma correction can be used to correct the brightness of an image by using a non linear transformation between the input values and the mapped output values",
    /* FeatureItem */ BaLiTrans, "ContrastBrightness.qml", "Simple program to change contrast and brightness"
]

// Group of Morphological
var group_morphological = [
    /* GroupItem */ "Morphological", GroupItem, "",
    /* FeatureItem */ Erosion, "ErosionControl.qml", "The erosion operation usually uses a structuring element for probing and reducing the shapes contained in the input image",
    /* FeatureItem */ Dilation, "DilationControl.qml", "The dilation operation usually uses a structuring element for probing and expanding the shapes contained in the input image",
    /* FeatureItem */ AdvMorpho, "AdvancedMorphologyControl.qml", "The function cv::morphologyEx can perform advanced morphological transformations using an erosion and dilation as basic operations",
]

// List of all groups. It is directly used by application to add feature list
var group_list = [
    /* Group of Drawing */ group_basicDrawing,
    /* Group of Basic Intensity */ group_basicintensity,
    /* Group of Morphological */ group_morphological,
]
