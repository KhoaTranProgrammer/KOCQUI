#-------------------------------------------------
#
# Project created by QtCreator 2020-02-23T15:39:29
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
#********************************************************************

QT       += qml quick

TARGET = KOCQPluginManager
TEMPLATE = lib

DEFINES += KOCQPLUGINMANAGER_LIBRARY

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
        KOCQPluginManager.cpp

HEADERS += \
        KOCQPluginManager.h \
    KOCQPluginManager_Global.h

win32 {
    targetHeader.path += $$PWD/../../include
    targetHeader.files += $$PWD/*.h
    INSTALLS += targetHeader

    targetLibrary.path += $$PWD/../../lib
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/debug/*.dll
    CONFIG(release, debug|release):targetLibrary.files += $$OUT_PWD/release/*.dll
    INSTALLS += targetLibrary
}

# Copy the header to the folder as the plugin binary
targetHeader.files += $$PWD/*.h
targetHeader.path += $$PWD/../../include/
COPIES += targetHeader

android {
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/*.so
    targetLibrary.path += $$PWD/../../lib/
    INSTALLS += targetLibrary
}
