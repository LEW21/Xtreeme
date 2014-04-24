TEMPLATE = lib
CONFIG += plugin
TARGET = xtreeme_memory

MOD = memory

include(../../../config.pri)

contains(memory, no) {
	TEMPLATE = subdirs
	SUBDIRS  =
} else {
	contains(memory, static) {
		CONFIG += static
	}

	QT = core

	DEFINES += XTREEME_MEMORY XTREEME_EXPORT_MEMORY

	include(memory.pri)
}
