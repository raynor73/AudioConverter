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
    filesselectionpage.cpp \
    wavsettingspage.cpp \
    riffreader/riffreader.cpp \
    riffreader/riffchunkheader.cpp \
	wavdecoder/wavdecoder.cpp \
	wavdecoder/wavformat.cpp \
    mp3settingspage.cpp \
    audioconverter/audioconverter.cpp \
audioconverter/resampler.cpp \
audioconverter/soundbuffer.cpp

HEADERS  += mainwindow.h \
    converterwizard.h \
    startpage.h \
    converterwizardviewmodel.h \
    filesselectionpage.h \
    wavsettingspage.h \
    riffreader/riffreader.h \
    riffreader/riffchunkheader.h \
	wavdecoder/wavdecoder.h \
	wavdecoder/wavformat.h \
    mp3settingspage.h \
    audioconverter/audioconverter.h \
audioconverter/resampler.h \
audioconverter/soundbuffer.h \
    audioconverter/soundbufferparams.h

FORMS    += mainwindow.ui \
startpage.ui \
    filesselectionpage.ui \
    wavsettingspage.ui \
    mp3settingspage.ui

TRANSLATIONS += audioconverter.ts

INCLUDEPATH += riffreader

CONFIG += c++11

unix:!macx: LIBS += -lmp3lame

macx: LIBS += -L$$PWD/libs/macos/lamemp3/ -lmp3lame.0

INCLUDEPATH += $$PWD/libs/include
DEPENDPATH += $$PWD/libs/include
