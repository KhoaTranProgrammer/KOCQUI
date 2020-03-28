import QtQuick 2.0

BasicControl {
    // Properties to control kernel length
    property int kernel_length: 1

    // Function to initialize controls
    function initializeControls() {
        addControl("Kernel Length", // name
                   1,               // minimum value
                   31,              // maximum value
                   2,               // slider step size
                   kernel_length,   // current value
                   "kernel_length") // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "kernel_length") {
            // When kernel length is changed
            kernel_length = newValue
        }
    }
}
