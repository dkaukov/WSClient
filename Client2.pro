
QT += qml quick sql core widgets quickcontrols2 network mqtt core5compat

CONFIG+=sdk_no_version_check
CONFIG += c++latest # add support of c++17
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        client.cpp \
        main.cpp \
        WebSocket.cpp

HEADERS += \
        WebSocket.h \
        client.h

macx {
    # Note: This is required because we use advanced C++ features such as std::optional
    # which requires newer Mojave+ C++ libs.  On a recent compiler SDK, this will
    # compile ok even on High Sierra with latest Xcode for High Sierra, so this requirement
    # isn't too bad.  It just affects what C++ runtime we link to on MacOS.
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.14
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
