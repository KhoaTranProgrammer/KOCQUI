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

// Spatial Filtering
var HomogeneousBlur = "Homogeneous Blur"
var GaussianBlur = "Gaussian Blur"
var MedianBlur = "Median Blur"
var BilateralFilter = "Bilateral Filter"

// Threshold Demo
var ThresholdDemo = "Threshold Demo"

// Transforms
var CopyMakeBorder= "copyMakeBorder"
var SobelDemo = "Sobel"
var LaplaceDemo = "Laplace Demo"
var CannyDetector = "CannyDetector Demo"
var Remapping = "Remapping"

// Hough Transforms
var HoughLineStandard = "Line Standard"
var HoughLineProbabilistic = "Line Probabilistic"
var HoughCircles = "Hough Circles"

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

// Group of Smoothing
var group_smoothing = [
    /* GroupItem */ "Smoothing", GroupItem, "",
    /* FeatureItem */ HomogeneousBlur, "SmoothingControl.qml", "Applying Homogeneous Blur for smoothing image",
    /* FeatureItem */ GaussianBlur, "SmoothingControl.qml", "Applying Gaussian Blur for smoothing image",
    /* FeatureItem */ MedianBlur, "SmoothingControl.qml", "Applying Median Blur for smoothing image",
    /* FeatureItem */ BilateralFilter, "SmoothingControl.qml", "bilateralFilter can reduce unwanted noise very well while keeping edges fairly sharp",
]

// Group of Threshold Demo
var group_thresholdDemo = [
    /* GroupItem */ "ThresholdDemo", GroupItem, "",
    /* FeatureItem */ ThresholdDemo, "ThresholdControl.qml", "The simplest segmentation method \nType: \n 0: Binary - 1: Binary Inverted - 2: Truncate - 3: To Zero - 4: To Zero Inverted",
]

// Group of Transforms
var group_Transforms = [
    /* GroupItem */ "Transforms", GroupItem, "",
    /* FeatureItem */ CopyMakeBorder, "CopyMakeBorderControl.qml", "Use the OpenCV function copyMakeBorder() to set the borders (extra padding to your image) \nBorder Type: 0 - BORDER_CONSTANT, 1 - BORDER_REPLICATE, 2 - BORDER_REFLECT, 3 - BORDER_WRAP",
    /* FeatureItem */ SobelDemo, "SobelControl.qml", "Sample code uses Sobel or Scharr OpenCV functions for edge detection",
    /* FeatureItem */ LaplaceDemo, "SobelControl.qml", "Sample code showing how to detect edges using the Laplace operator",
    /* FeatureItem */ CannyDetector, "CannyControl.qml", "Sample code showing how to detect edges using the Canny Detector",
    /* FeatureItem */ Remapping, "RemappingControl.qml", "Use the OpenCV function cv::remap to implement simple remapping routines.\n0 - Reducing it to half the size and centering it \n1 - Turning it upside down \n2 - Reflecting it in the x direction \n3 - Reflecting it in both directions",
]

// Group of Hough Transforms
var group_HoughTransforms = [
    /* GroupItem */ "Hough Transforms", GroupItem, "",
    /* FeatureItem */ HoughLineStandard, "HoughLineStandardControl.qml", "demonstrates line finding with the Standard Hough Line Transform",
    /* FeatureItem */ HoughLineProbabilistic, "HoughLineProbabilisticControl.qml", "demonstrates line finding with the Probabilistic Hough Line Transform",
    /* FeatureItem */ HoughCircles, "HoughCirclesControl.qml", "demonstrates circles finding with the Hough Circles Transform",
]

// List of all groups. It is directly used by application to add feature list
var group_list = [
    /* Group of Drawing */ group_basicDrawing,
    /* Group of Basic Intensity */ group_basicintensity,
    /* Group of Morphological */ group_morphological,
    /* Group of Smoothing */ group_smoothing,
    /* Group of Threshold Demo */ group_thresholdDemo,
    /* Group of Transforms */ group_Transforms,
    /* Group of Hough Transforms */ group_HoughTransforms,
]
