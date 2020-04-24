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
#* 1.1.0: Apr-25-2020                                               *
#*        Support build for Android                                 *
#********************************************************************

QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

RESOURCES += qml.qrc

win32 {
    DESTDIR = $$PWD/../../lib
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = $$PWD/../../lib

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
LIBS += -L$$PWD/../../lib -lKOCQCore -lKOCQPluginManager

# Default location for library
DEFINES += LIBRARY_PATH=\\\"$$PWD\\\"

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_EXTRA_LIBS = \
        $$PWD/../../lib/libKOCQPluginManager.so \
        $$PWD/../../lib/libKOCQCore.so \
        $$PWD/../../lib/plugins/libKOCQDraw.so \
        $$PWD/../../lib/opencv/libopencv_core.so \
        $$PWD/../../lib/opencv/libopencv_imgcodecs.so \
        $$PWD/../../lib/opencv/libopencv_imgproc.so \
        $$PWD/../../lib/opencv/libopencv_highgui.so \
        $$PWD/../../lib/opencv/libopencv_videoio.so \
}

android {
    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
}
