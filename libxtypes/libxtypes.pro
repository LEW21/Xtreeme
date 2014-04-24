TEMPLATE = lib
TARGET = xtypes

MOD = libxtypes

include(../config.pri)

//include.path = /usr/include/Xtreeme
//include.files = include/*
//INSTALLS += include

QT = core

DEFINES += XTYPES_EXPORT_LIB
LIBS += -lxcore

include(libxtypes.pri)

QT += testlib
