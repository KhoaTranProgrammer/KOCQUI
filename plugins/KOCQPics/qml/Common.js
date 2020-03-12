// Name of features are used by QML
// current_feature will be updated each time user selects feature
var GroupItem = "GroupItem"
var BaLiTrans = "Contrast&Brightness"

// Some Basic Intensity Transformation Functions
var Negative = "ImageNegative"
var GammaCor = "GammaCorrection"

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

// Group of Basic Intensity
var group_basicintensity = [
    /* GroupItem */ "Basic Intensity", GroupItem, "",
    /* FeatureItem */ Negative, "", "Inverts every bit of an array",
    /* FeatureItem */ GammaCor, "GammaCorrectionControl.qml", "Gamma correction can be used to correct the brightness of an image by using a non linear transformation between the input values and the mapped output values",
    /* FeatureItem */ BaLiTrans, "ContrastBrightness.qml", "Simple program to change contrast and brightness"
]

// List of all groups. It is directly used by application to add feature list
var group_list = [
    /* Group of Basic Intensity */ group_basicintensity,
]
