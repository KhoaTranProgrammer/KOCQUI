#-------------------------------------------------
#
# Project created by QtCreator 2020-04-16T06:48:00
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
#* 1.1.0: Apr-25-2020                                               *
#*        Support build for Android                                 *
#********************************************************************

QT       += qml quick

TARGET = KOCQDraw
TEMPLATE = lib

DEFINES += KOCQDRAW_LIBRARY

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
        KOCQDraw.cpp

HEADERS += \
        KOCQDraw.h \
    KOCQDraw_Global.h

win32 {
    DESTDIR = $$PWD/../../lib/plugins
}

INCLUDEPATH += $$PWD/../../include
DEPENDPATH += $$PWD/../../include
LIBS += -L$$PWD/../../lib -lKOCQCore

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

DEFINES += DEFAULT_PATH=\\\"$$PWD\\\"

RESOURCES += \
    qml.qrc

android {
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/*.so
    targetLibrary.path += $$PWD/../../lib/plugins/
    INSTALLS += targetLibrary
}
