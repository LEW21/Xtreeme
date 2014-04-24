TEMPLATE = lib
CONFIG += plugin
TARGET = xtreeme_remote

MOD = remote

include(../../../config.pri)

contains(remote, no) {
	TEMPLATE = subdirs
	SUBDIRS  =
} else {
	contains(remote, static) {
		CONFIG += static
	}

	QT = core

	DEFINES += XTREEME_REMOTE XTREEME_EXPORT_REMOTE

	include(remote.pri)
}
