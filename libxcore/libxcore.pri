libxcore = $$PWD

SOURCES += $$libxcore/Shared.cpp
SOURCES += $$libxcore/SharedData.cpp
SOURCES += $$libxcore/EventLoop.cpp
SOURCES += $$libxcore/EventQueue.cpp
SOURCES += $$libxcore/Type.cpp
SOURCES += $$libxcore/CoreType.cpp
SOURCES += $$libxcore/PlainType.cpp

glib {
	include(glib/glib.pri)
}
