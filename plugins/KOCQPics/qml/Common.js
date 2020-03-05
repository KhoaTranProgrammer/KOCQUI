// Name of features are used by QML
// current_feature will be updated each time user selects feature
var GroupItem = "GroupItem"
var BaLiTrans = "BasicLinearTransforms"

/*
 Group format
  + GroupItem: this is parent of group, just display group name
  + FeatureItem(s): they are detail Features in group
*/

/*
 GroupItem format
  + GroupName: this is the name of Feature
  + Control: group do not need control GUI
  + Description: group do not need description
*/

/*
 FeatureItem format
  + FeatureName: this is the name of Feature
  + Control: this is GUI to contron Feature arguments
  + Description: this is the introduction about Feature
*/

// Group of Transforms Features
var group_convert = [
    /* GroupItem */ "Transforms", GroupItem, "",
    /* FeatureItem */ BaLiTrans, "BasicLinearTransforms.qml", "Simple program to change contrast and brightness"
]

// List of all groups. It is directly used by application to add feature list
var group_list = [
    /* Group of Transforms Features */ group_convert,
]
