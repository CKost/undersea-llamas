#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T21:53:00
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnderseaLlamas
TEMPLATE = app


SOURCES += main.cpp \
        ulmainwindow.cpp \
        riddle.cpp \
        stateengine.cpp \
        worldgenerator.cpp \
        world.cpp \
    chests.cpp

HEADERS  += \
    world.h \
    llama.h \
    ulmainwindow.h \
    worldgenerator.h \
    stateengine.h \
    chests.h \
    riddle.h

FORMS    += ulmainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
