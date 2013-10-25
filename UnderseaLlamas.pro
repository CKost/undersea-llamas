#-------------------------------------------------
#
# Project created by QtCreator 2013-10-12T21:53:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnderseaLlamas
TEMPLATE = app


SOURCES += main.cpp\
        ulmainwindow.cpp \
    worldgenerator.cpp

HEADERS  += ulmainwindow.hpp \
    worldgenerator.hpp \
    Llama.h \
    chests.h

FORMS    += ulmainwindow.ui

QMAKE_CXXFLAGS += -std=c++0x
