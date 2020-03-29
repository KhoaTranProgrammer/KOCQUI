import QtQuick 2.0

BasicControl {
    // Properties to control Canny
    property int threshold: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Threshold", // name
                   0,           // minimum value
                   100,         // maximum value
                   1,           // slider step size
                   threshold,   // current value
                   "threshold") // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "threshold") {
            // When threshold is changed
            threshold = newValue
        }
    }
}
