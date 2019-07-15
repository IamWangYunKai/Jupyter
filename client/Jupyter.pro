QT += quick
CONFIG += c++17

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

unix:android{
    SPDLOG_INCLUDE = $$PWD/libs
    PROTOBUF_INCLUDE += C:\usr\local\protobuf\2.6.1\include
    CONFIG(release,debug|release){
        PROTOBUF_LIB += C:\usr\local\protobuf\2.6.1\lib\android\libprotobuf.a
        PROTOBUF_LIB += C:\usr\local\protobuf\2.6.1\lib\android\libprotobuf-lite.a
        PROTOBUF_LIB += C:\usr\local\protobuf\2.6.1\lib\android\libprotoc.a
    }
}

win32 {
    SPDLOG_INCLUDE = $$PWD/libs
    PROTOBUF_INCLUDE = D:\usr\local\protobuf\include
    CONFIG(release,debug|release){
        PROTOBUF_LIB = D:\usr\local\protobuf\lib\x64\libprotobuf.lib
    }
    CONFIG(debug,debug|release){
        PROTOBUF_LIB = D:\usr\local\protobuf\lib\x64\libprotobufd.lib
    }
}
INCLUDEPATH += \
    $$SPDLOG_INCLUDE \
    $$PROTOBUF_INCLUDE


HEADERS += \
    $$PWD/src/interaction.h \
    $$PWD/src/communicator.h \
    $$PWD/src/staticparam.hpp \
    $$PWD/src/singleton.hpp \
    $$PWD/src/proto/zss_cmd.pb.h

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/interaction.cpp \
    $$PWD/src/communicator.cpp \
    $$PWD/src/proto/zss_cmd.pb.cc

DISTFILES += \
    android-sources/AndroidManifest.xml \
    icon.png \

LIBS += \
    $$PROTOBUF_LIB

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
