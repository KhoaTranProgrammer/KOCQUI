#-------------------------------------------------
#
# Project created by QtCreator 2020-08-25T05:37:26
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
#* 1.1.0: Feb-10-2021                                               *
#*        Support build for Android                                 *
#********************************************************************

# Application version
VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_BUILD = 0

DEFINES += "VERSION_MAJOR=$$VERSION_MAJOR"\
           "VERSION_MINOR=$$VERSION_MINOR"\
           "VERSION_BUILD=$$VERSION_BUILD"

QT       += qml quick

TARGET = KOCQHISTOGRAM
TEMPLATE = lib

DEFINES += KOCQHISTOGRAM_LIBRARY

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
        KOCQHISTOGRAM.cpp

HEADERS += \
        KOCQHISTOGRAM.h \
    KOCQHISTOGRAM_Global.h

win32 {
    DESTDIR = $$PWD/../../lib/plugins
}

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
LIBS += -L$$PWD/../../lib -lKOCQCore

RESOURCES += \
    qml.qrc

win32 {
    LIBS += -L$$PWD/../../lib/opencv \
            libopencv_core411 \
            libopencv_imgcodecs411 \
            libopencv_imgproc411 \
            libopencv_highgui411 \
}

android {
    LIBS += -L$$PWD/../../lib/opencv \
        -lopencv_core \
        -lopencv_imgcodecs \
        -lopencv_imgproc \
        -lopencv_highgui \
}

INCLUDEPATH += $$PWD/../../include/opencv/
INCLUDEPATH += $$PWD/../../include/opencv/core/include
INCLUDEPATH += $$PWD/../../include/opencv/highgui/include
INCLUDEPATH += $$PWD/../../include/opencv/imgcodecs/include
INCLUDEPATH += $$PWD/../../include/opencv/imgproc/include
INCLUDEPATH += $$PWD/../../include/opencv/features2d/include
INCLUDEPATH += $$PWD/../../include/opencv/video/include
INCLUDEPATH += $$PWD/../../include/opencv/videoio/include

DEPENDPATH += $$PWD/../../include/opencv/
DEPENDPATH += $$PWD/../../include/opencv/core/include
DEPENDPATH += $$PWD/../../include/opencv/highgui/include
DEPENDPATH += $$PWD/../../include/opencv/imgcodecs/include
DEPENDPATH += $$PWD/../../include/opencv/imgproc/include
DEPENDPATH += $$PWD/../../include/opencv/features2d/include
DEPENDPATH += $$PWD/../../include/opencv/video/include
DEPENDPATH += $$PWD/../../include/opencv/videoio/include

win32 {
    targetLibrary.path += $$PWD/../../lib/plugins
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/debug/*.dll
    CONFIG(release, debug|release):targetLibrary.files += $$OUT_PWD/release/*.dll
    INSTALLS += targetLibrary
}

DEFINES += DEFAULT_PATH=\\\"$$PWD\\\"

android {
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/*.so
    targetLibrary.path += $$PWD/../../lib/plugins/
    INSTALLS += targetLibrary
}
