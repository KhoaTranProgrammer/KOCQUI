import QtQuick 2.0

BasicControl {
    // Properties to control Dilation
    property int  dilation_elem: 0
    property int  dilation_size: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Dilation Elem", // name
                   0,               // minimum value
                   2,               // maximum value
                   1,               // slider step size
                   dilation_elem,   // current value
                   "dilation_elem") // property name

        addControl("Dilation Size", // name
                   0,               // minimum value
                   21,              // maximum value
                   1,               // slider step size
                   dilation_size,   // current value
                   "dilation_size") // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "dilation_elem") {
            // When dilation elem is changed
            dilation_elem = newValue
        }else if(currentProperty === "dilation_size") {
            // When dilation size is changed
            dilation_size = newValue
        }
    }
}
