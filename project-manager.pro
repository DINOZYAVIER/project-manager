QT       += core gui widgets

TARGET = ProjectManager
TEMPLATE = app

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Generate make file only for certain build type
CONFIG -= debug_and_release

# Set app version
REV = $$system(git rev-list --count HEAD)
BUILD_VERSION = 0.1.0.$$REV
VERSION = $$BUILD_VERSION

PRECOMPILED_HEADER = include/precompiled.h

SOURCES += \
    sources/main.cpp \
    sources/mainwindow.cpp \
    sources/project_handler.cpp

HEADERS += \
    include/mainwindow.h \
    include/precompiled.h \
    include/project_handler.h

FORMS += \
    resources/forms/mainwindow.ui

win32: PLATFORM = "windows"
linux: PLATFORM = "linux"
macx:  PLATFORM = "mac"

CONFIG( debug, debug|release ) {
    # Debug
    BUILD_CONFIG = "debug"
} else {
    # Release
    BUILD_CONFIG = "release"
}

DESTDIR = $$PWD/bin/$${PLATFORM}_$${BUILD_CONFIG}/

# Deployment
win32 {
    DEPLOY_TARGET = $$shell_quote($$DESTDIR/$${TARGET}.exe)
    DEPLOY_COMMAND = windeployqt --no-compiler-runtime --no-opengl-sw
    #RC_ICONS = ./resources/appicon/icon.ico
    QMAKE_TARGET_PRODUCT = Project Management App
    QMAKE_TARGET_DESCRIPTION = Project Management
}

macx {
    DEPLOY_TARGET = $$shell_quote($$DESTDIR/$${TARGET}.app)
    DEPLOY_COMMAND = macdeployqt
    #ICON = ./resources/appicon/icon.icns
}

win32|macx {
    # Generate release
    CONFIG(release, debug|release): QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${DEPLOY_TARGET}
}
