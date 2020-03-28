import QtQuick 2.0

BasicControl {
    // Properties to control copy Make Border
    property int borderType: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Border Type",   // name
                   0,               // minimum value
                   3,               // maximum value
                   1,               // slider step size
                   borderType,      // current value
                   "borderType")    // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "borderType") {
            // When border Type is changed
            borderType = newValue
        }
    }
}
