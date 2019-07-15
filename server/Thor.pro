TEMPLATE = app

CONFIG += c++17

QT += qml quick serialport testlib

TARGET = Thor

CONFIG += c++11 console

DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    Thor.qrc

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

unix:!macx{
    SPDLOG_INCLUDE = $$PWD/libs
}

INCLUDEPATH += \
    $$SPDLOG_INCLUDE \
    $$PROTOBUF_INCLUDE

SOURCES += \
    src/main.cpp \
    src/parammanager.cpp \
    src/logger.cpp \
    src/actionmodule.cpp \
    src/proto/zss_cmd.pb.cc \
    src/crc.cpp \
    src/interaction.cpp \
    src/paraminterface.cpp \
    src/communicator.cpp \
    src/interaction.cpp

HEADERS += \
    src/parammanager.h \
    src/singleton.hpp \
    src/logger.h \
    src/actionmodule.h \
    src/proto/zss_cmd.pb.h \
    src/crc.h \
    src/interaction.h \
    src/paraminterface.h \
    src/communicator.h \
    src/interaction.h \
    src/staticparam.h \
    src/zsingleton.h

INCLUDEPATH += \
    src/

LIBS += \
    $$PROTOBUF_LIB

DISTFILES += \
    TODO.md
