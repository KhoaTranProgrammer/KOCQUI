import QtQuick 2.0

BasicControl {
    // Properties to control Gamma Correction
    property int gamma_cor: 100

    // Function to initialize controls
    function initializeControls() {
        addControl("Gamma correction",  // name
                   0,                   // minimum value
                   200,                 // maximum value
                   1,                   // slider step size
                   gamma_cor,           // current value
                   "gamma_cor")         // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "gamma_cor") {
            // When contrast is changed
            gamma_cor = newValue
        }
    }
}
