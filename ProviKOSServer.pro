QT += core network xml concurrent
QT -= gui

CONFIG += c++11

TARGET = ProviKOSServer
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    kosclient.cpp \
    kosserver.cpp

HEADERS += \
    kosclient.h \
    kosserver.h
