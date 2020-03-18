import QtQuick 2.0

BasicControl {
    // Properties to control Advanced Morphology
    property int morph_elem: 0
    property int morph_size: 0
    property int morph_operator: 0

    // Function to initialize controls
    function initializeControls() {
        addControl("Morph Elem",    // name
                   0,               // minimum value
                   2,               // maximum value
                   1,               // slider step size
                   morph_elem,      // current value
                   "morph_elem")    // property name

        addControl("Morph Size",    // name
                   0,               // minimum value
                   21,              // maximum value
                   1,               // slider step size
                   morph_size,      // current value
                   "morph_size")    // property name

        addControl("Morph Operator",    // name
                   0,                   // minimum value
                   4,                   // maximum value
                   1,                   // slider step size
                   morph_operator,      // current value
                   "morph_operator")    // property name
    }

    // Function to update properties
    function updateProperties() {
        if(currentProperty === "morph_elem") {
            // When morph elem is changed
            morph_elem = newValue
        } else if(currentProperty === "morph_size") {
            // When morph size is changed
            morph_size = newValue
        } else if(currentProperty === "morph_operator") {
            // When morph operator is changed
            morph_operator = newValue
        }
    }
}
