import QtQuick 2.0

BasicControl {
    // Properties to control Erosion
    property int  erosion_elem: 0
    property int  erosion_size: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Erosion Elem",  // name
                   0,               // minimum value
                   2,               // maximum value
                   1,               // slider step size
                   erosion_elem,    // current value
                   "erosion_elem")  // property name

        addControl("Erosion Size",  // name
                   0,               // minimum value
                   21,              // maximum value
                   1,               // slider step size
                   erosion_size,    // current value
                   "erosion_size")  // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "erosion_elem") {
            // When erosion elem is changed
            erosion_elem = newValue
        }else if(currentProperty === "erosion_size") {
            // When erosion_size is changed
            erosion_size = newValue
        }
    }
}
