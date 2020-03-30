import QtQuick 2.0

BasicControl {
    // Properties to control Hough Circle
    property int cannyThreshold: 100
    property int accumulatorThreshold: 50

    // Function to initialize controls
    function initializeControls() {
        addControl("Canny Threshold",   // name
                   0,                   // minimum value
                   255,                 // maximum value
                   1,                   // slider step size
                   cannyThreshold,      // current value
                   "cannyThreshold")    // property name

        addControl("Accumulator Threshold", // name
                   0,                       // minimum value
                   200,                     // maximum value
                   1,                       // slider step size
                   accumulatorThreshold,    // current value
                   "accumulatorThreshold")  // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "cannyThreshold") {
            // When cannyThreshold is changed
            cannyThreshold = newValue
        }else if(currentProperty === "accumulatorThreshold") {
            // When accumulatorThreshold is changed
            accumulatorThreshold = newValue
        }
    }
}
