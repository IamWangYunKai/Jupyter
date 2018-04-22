TEMPLATE = app

CONFIG += c++11

QT += qml quick serialport testlib

TARGET = Thor

CONFIG += c++11 console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += \
    Thor.qrc

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

macx {
#    SPDLOG_INCLUDE = C:\usr\local\spdlog\include
    SPDLOG_INCLUDE = $$PWD/libs
    PROTOBUF_INCLUDE = /usr/local/include
    CONFIG(release,debug|release){
        PROTOBUF_LIB = /usr/local/lib/libprotobuf.13.dylib
    }
    CONFIG(debug,debug|release){
        PROTOBUF_LIB = /usr/local/lib/libprotobuf.13.dylib
    }
}

win32 {
    SPDLOG_INCLUDE = $$PWD/libs
    PROTOBUF_INCLUDE = C:\usr\local\protobuf\3.3.0\include
    CONFIG(release,debug|release){
        PROTOBUF_LIB = C:\usr\local\protobuf\3.3.0\lib\vs14.0\libprotobuf.lib
    }
    CONFIG(debug,debug|release){
        PROTOBUF_LIB = C:\usr\local\protobuf\3.3.0\lib\vs14.0\libprotobufd.lib
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
    src/test.cpp \
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
    src/translator.hpp \
    src/test.h \
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
