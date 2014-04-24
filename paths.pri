QT =
QMAKE_CXXFLAGS += -std=gnu++1y -fdiagnostics-color=auto

contains(TEMPLATE, lib) {
	DESTDIR = $$PWD/lib
	target.path = /usr/lib
	INSTALLS += target
} else {
	DESTDIR = $$PWD/bin
	target.path = /usr/bin
	INSTALLS += target
}

INCLUDEPATH += $$PWD

OBJECTS_DIR = $$PWD/tmp/$$MOD/obj
MOC_DIR     = $$PWD/tmp/$$MOD/moc
RCC_DIR     = $$PWD/tmp/$$MOD/rcc
UI_DIR      = $$PWD/tmp/$$MOD/ui

LIBS       += -L$$PWD/lib
