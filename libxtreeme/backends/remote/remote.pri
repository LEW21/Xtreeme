remote = $$PWD

QT += network

HEADERS += $$remote/BackendFactory.h
SOURCES += $$remote/BackendFactory.cpp

HEADERS += $$remote/Database.h
SOURCES += $$remote/Database.cpp

HEADERS += $$remote/QueryStream.h
SOURCES += $$remote/QueryStream.cpp
