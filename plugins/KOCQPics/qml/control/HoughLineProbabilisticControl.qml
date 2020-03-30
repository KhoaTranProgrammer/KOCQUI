import QtQuick 2.0

BasicControl {
    // Properties to control Hough Line Standard
    property int p_trackbar: 150
    property int min_threshold: 50

    // Function to initialize controls
    function initializeControls() {
        addControl("Probabilistic trackbar",    // name
                   0,                           // minimum value
                   150,                         // maximum value
                   1,                           // slider step size
                   p_trackbar,                  // current value
                   "p_trackbar")                // property name

        addControl("Min threshold", // name
                   0,               // minimum value
                   100,             // maximum value
                   1,               // slider step size
                   min_threshold,   // current value
                   "min_threshold") // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "p_trackbar") {
            // When p_trackbar is changed
            p_trackbar = newValue
        }else if(currentProperty === "min_threshold") {
            // When min_threshold is changed
            min_threshold = newValue
        }
    }
}
