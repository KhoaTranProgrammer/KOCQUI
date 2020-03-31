import QtQuick 2.0

BasicControl {
    // Properties to control Remapping
    property int types: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("types of mappings", // name
                   0,                   // minimum value
                   3,                   // maximum value
                   1,                   // slider step size
                   types,               // current value
                   "types")             // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "types") {
            // When types is changed
            types = newValue
        }
    }
}
