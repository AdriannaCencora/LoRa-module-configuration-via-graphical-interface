#-------------------------------------------------
#
# Project created by QtCreator 2019-04-08T18:31:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LoraApp
TEMPLATE = app


SOURCES +=      mainwindow.cpp \
    controller.cpp \
    tests/controllerTest.cpp

LIBS += -lwiringPi \
        -lcrypt

HEADERS  += mainwindow.h \
    controller.h \
    logic.h \
    constants.h \
    tests/controllerTest.h

FORMS    += mainwindow.ui

QT += testlib
