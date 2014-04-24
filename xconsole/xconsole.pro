TEMPLATE = app
TARGET = xconsole

MOD = xconsole

include(../config.pri)

QT = core gui widgets network
LIBS += -lxcore -lxtypes -lxtreeme

CONFIG += debug
CONFIG -= release

SOURCES += main.cpp

HEADERS += Console.h
SOURCES += Console.cpp

HEADERS += StreamHandler.h

HEADERS += StreamHandlerQt.h
SOURCES += StreamHandlerQt.cpp

HEADERS += StreamHandlerIO.h
SOURCES += StreamHandlerIO.cpp

HEADERS += SolutionViewer.h
SOURCES += SolutionViewer.cpp
