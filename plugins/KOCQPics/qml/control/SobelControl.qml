import QtQuick 2.0

BasicControl {
    // Properties to control Sobel edge detection
    property int ksize: 1
    property int scale: 1
    property int delta: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Ksize", // name
                   1,       // minimum value
                   7,       // maximum value
                   2,       // slider step size
                   ksize,   // current value
                   "ksize") // property name

        addControl("Scale", // name
                   1,       // minimum value
                   255,     // maximum value
                   1,       // slider step size
                   scale,   // current value
                   "scale") // property name

        addControl("Delta", // name
                   0,       // minimum value
                   255,     // maximum value
                   1,       // slider step size
                   delta,   // current value
                   "delta") // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "ksize") {
            // When ksize is changed
            ksize = newValue
        }else if(currentProperty === "scale") {
            // When scale is changed
            scale = newValue
        }else if(currentProperty === "delta") {
            // When delta is changed
            delta = newValue
        }
    }
}
