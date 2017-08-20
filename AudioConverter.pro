#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T14:24:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioConverter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    converterwizard.cpp \
startpage.cpp \
    converterwizardviewmodel.cpp \
    filesselectionpage.cpp

HEADERS  += mainwindow.h \
    converterwizard.h \
    startpage.h \
    converterwizardviewmodel.h \
    filesselectionpage.h

FORMS    += mainwindow.ui \
startpage.ui \
    filesselectionpage.ui

TRANSLATIONS += audioconverter.ts
