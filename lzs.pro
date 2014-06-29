#-------------------------------------------------
#
# Project created by QtCreator 2012-09-23T21:14:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = lzs

configUNLZS {
    TARGET = unlzs
    DEFINES += UNLZS
}

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    lzs/LZS.cpp \
    Arguments.cpp \
    lzs/LZSObserver.cpp

HEADERS += \
    lzs/LZS.h \
    Arguments.h \
    lzs/LZSObserver.h

OTHER_FILES += README.md
