import QtQuick 2.0

BasicControl {
    // Properties to control threshold
    property int threshold_value: 0
    property int threshold_type: 3

    // Function to initialize controls
    function initializeControls() {
        addControl("Threshold Type",    // name
                   0,                   // minimum value
                   4,                   // maximum value
                   1,                   // slider step size
                   threshold_type,      // current value
                   "threshold_type")    // property name

        addControl("Threshold Value",   // name
                   0,                   // minimum value
                   255,                 // maximum value
                   1,                   // slider step size
                   threshold_value,     // current value
                   "threshold_value")   // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "threshold_type") {
            // When threshold type is changed
            threshold_type = newValue
        }else if(currentProperty === "threshold_value") {
            // When threshold value is changed
            threshold_value = newValue
        }
    }
}
