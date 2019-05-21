#-------------------------------------------------
#
# Project created by QtCreator 2019-04-08T18:31:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoraApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    console.cpp

LIBS += -lwiringPi \
        -lcrypt

HEADERS  += mainwindow.h \
    controller.h \
    logic.h \
    constants.h \
    console.h \
    logic_console.h

FORMS    += mainwindow.ui
