import QtQuick 2.0

BasicControl {

    // Properties to control Crop
    property double alpha: 1.0
    property int beta: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Contrast", // name
                   1.0,           // minimum value
                   3.0, // maximum value
                   0.1,           // slider step size
                   alpha,    // current value
                   "contrast")  // property name

        addControl("Brightness",  // name
                   0,               // minimum value
                   100,      // maximum value
                   1,               // slider step size
                   beta,        // current value
                   "brightness")      // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "contrast") {
            // When contrast is changed
            alpha = newValue
        }else if(currentProperty === "brightness") {
            // When brightness is changed
            beta = newValue
        }
    }
}
