#-------------------------------------------------
#
# Project created by QtCreator 2017-08-18T14:24:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AudioConverter
TEMPLATE = app

DEFINES += PORTABLE=1
DEFINES += "ORGANIZATION_NAME=\"\\\"Lapin Soft\\\"\""
DEFINES += "APPLICATION_NAME=\"\\\"Audio Converter\\\"\""

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
    mp3settingspage.cpp \
    audioconverter/audioconverter.cpp \
audioconverter/resampler.cpp \
audioconverter/soundbuffer.cpp \
    progresspage.cpp \
    audioconverter/wavtomp3converterthread.cpp \
    audioconverter/mp3towavconverterthread.cpp \
    audioconverter/converterthread.cpp \
    riffwriter/riffwriter.cpp \
    riffwriter/riffoutput.cpp \
    wavencoder/wavencoder.cpp

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
    audioconverter/soundbufferparams.h \
    progresspage.h \
    audioconverter/converterthread.h \
    audioconverter/wavtomp3converterthread.h \
    audioconverter/mp3towavconverterthread.h \
    riffwriter/riffwriter.h \
    riffwriter/riffoutput.h \
    wavencoder/wavencoder.h

FORMS    += mainwindow.ui \
startpage.ui \
    filesselectionpage.ui \
    wavsettingspage.ui \
    mp3settingspage.ui \
    progresspage.ui

TRANSLATIONS += audioconverter.ts

INCLUDEPATH += riffreader \
	wavdecoder \
	audioconverter \
	riffwriter \
	wavencoder

CONFIG += c++11

win32: LIBS += -L$$PWD/libs/win32 -llibmp3lame
unix:!macx: LIBS += -lmp3lame
#macx: LIBS += -L$$PWD/libs/macos/lamemp3/ -lmp3lame.0

INCLUDEPATH += $$PWD/libs/include
DEPENDPATH += $$PWD/libs/include

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/ -llibmp3lame-static
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/ -llibmp3lame-staticd

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/liblibmp3lame-static.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/liblibmp3lame-staticd.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/libs/libmp3lame-static.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/libs/libmp3lame-staticd.lib
