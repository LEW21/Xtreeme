memory = $$PWD

HEADERS += $$memory/Statements.h
SOURCES += $$memory/Statements.cpp

HEADERS += $$memory/Data.h

HEADERS += $$memory/Reasoner.h
SOURCES += $$memory/Reasoner.cpp

HEADERS += $$memory/BackendFactory.h
SOURCES += $$memory/BackendFactory.cpp

HEADERS += $$memory/Database.h
SOURCES += $$memory/Database.cpp

HEADERS += $$memory/QueryStream.h
SOURCES += $$memory/QueryStream.cpp

HEADERS += $$memory/Command.h
SOURCES += $$memory/Command.cpp

include(commands/commands.pri)
