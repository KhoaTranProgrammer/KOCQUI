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

TEMPLATE = lib
TARGET = KOCQCoreGUI
QT += qml quick
CONFIG += plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.kocqui.kocqcoregui

win32 {
    DESTDIR = $$PWD/../../lib/KOCQCoreGUI
}

# Input
SOURCES += \
        KOCQCoreGUI_Plugin.cpp \
    CpuInfo.cpp \
    KOCQMatImage.cpp

HEADERS += \
        KOCQCoreGUI_Plugin.h \
    CpuInfo.h \
    KOCQMatImage.h

DISTFILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

# Copy the qmldir file to the same folder as the plugin binary
cpqmldir.files = qmldir
cpqmldir.path = $$PWD/../../lib/KOCQCoreGUI
COPIES += cpqmldir

android {
    CONFIG(debug, debug|release):targetLibrary.files += $$OUT_PWD/*.so
    targetLibrary.path += $$PWD/../../lib/KOCQCoreGUI
    INSTALLS += targetLibrary
}
