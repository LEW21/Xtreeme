TEMPLATE = lib
TARGET = xtreeme

MOD = libxtreeme

include(../config.pri)

//include.path = /usr/include/Xtreeme
//include.files = include/*
//INSTALLS += include

QT = core testlib
LIBS += -lxtypes

DEFINES += XTREEME_EXPORT_LIB

contains(memory, static) {
	DEFINES += XTREEME_INCLUDE_MEMORY
	LIBS += -lxtreeme_memory
}

contains(memory, shared) {
	DEFINES += XTREEME_LINK_MEMORY
	LIBS += -lxtreeme_memory
}

contains(remote, static) {
	DEFINES += XTREEME_EXPORT_REMOTE
	LIBS += -lxtreeme_remote
}

contains(remote, shared) {
	DEFINES += XTREEME_LINK_REMOTE
	LIBS += -lxtreeme_remote
}

include(libxtreeme.pri)
include(util/util.pri)
include(expressions/expressions.pri)
include(parser/parser.pri)
include(parser/queries/queries.pri)

INCLUDEPATH += ../../Yield/
