QT += quick
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

RESOURCES += qml.qrc

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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

INCLUDEPATH += \
    $$SPDLOG_INCLUDE \
    $$PROTOBUF_INCLUDE


HEADERS += \
    interaction.h \
    communicator.h \
    staticparam.h \
    singleton.hpp \
    proto/zss_cmd.pb.h

SOURCES += main.cpp \
    interaction.cpp \
    communicator.cpp \
    proto/zss_cmd.pb.cc

DISTFILES += \
    android-sources/AndroidManifest.xml \
    icon.png \

LIBS += \
    $$PROTOBUF_LIB

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources
