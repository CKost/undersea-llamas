#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T21:53:00
#
#-------------------------------------------------

QT       += core gui network
QT       += core gui multimedia



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnderseaLlamas
TEMPLATE = app


SOURCES += main.cpp \
        ulmainwindow.cpp \
        riddle.cpp \
        stateengine.cpp \
        worldgenerator.cpp \
        world.cpp \
        networkengine.cpp \
        moviedisplay.cpp


HEADERS  += \
    world.h \
    llama.h \
    worldgenerator.h \
    stateengine.h \
    riddle.h \
    ulmainwindow.h \
    llamalabel.h \
    chestlabel.h \
    networkengine.h \
    moviedisplay.h \
    chest.h

FORMS    += ulmainwindow.ui \
    moviedisplay.ui

QMAKE_CXXFLAGS += -std=c++0x


RESOURCES += \
    resources.qrc
