#-------------------------------------------------
#
# Project created by QtCreator 2020-01-08T04:49:14
#
#-------------------------------------------------

#******************
#* VERSION: 1.1.0 *
#******************

#********************************************************************
#* PURPOSE                                                          *
#********************************************************************
#* Project configuration                                            *
#********************************************************************

#********************************************************************
#* VERSION HISTORY                                                  *
#********************************************************************
#* 1.0.0: Apr-19-2020                                               *
#*        Initial version supports build for Windows                *
#* 1.1.0: Apr-24-2020                                               *
#*        Support build for Android                                 *
#*        June-04-2020                                              *
#*        Update library version to 1.0.0                           *
#********************************************************************

# Library version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
           "VERSION_MINOR=$$VERSION_MINOR"\
           "VERSION_BUILD=$$VERSION_BUILD"

QT       += qml quick

TARGET = KOCQCore
TEMPLATE = lib

DEFINES += KOCQCORE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    KOCQPluginBase.cpp

HEADERS += \
    KOCQPluginBase.h \
    KOCQCore_Global.h

RESOURCES += \
    qml.qrc

win32 {
    targetHeader.path += $$PWD/../../include
    targetHeader.files += $$PWD/*.h
    INSTALLS += targetHeader

    targetLibrary.path += $$PWD/../../lib
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/debug/*.dll
    CONFIG(release, debug|release):targetLibrary.files += $$OUT_PWD/release/*.dll
    INSTALLS += targetLibrary
}

android {
    # Copy the header to the folder as the plugin binary
    targetHeader.files += *.h
    targetHeader.path += $$PWD/../../include/
    COPIES += targetHeader

    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/*.so
    targetLibrary.path += $$PWD/../../lib/
    INSTALLS += targetLibrary
}
