TEMPLATE = lib
TARGET = xcore

MOD = libxcore

include(../config.pri)

glib {
	CONFIG += link_pkgconfig
	PKGCONFIG += glib-2.0
	DEFINES += USE_GLIB
}

DEFINES += XCORE_EXPORT_LIB

include(libxcore.pri)
