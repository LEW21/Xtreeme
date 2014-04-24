parser = $$PWD

HEADERS += $$parser/Token.h

HEADERS += $$parser/ParseError.h
SOURCES += $$parser/ParseError.cpp

HEADERS += $$parser/Tokenizer.h
SOURCES += $$parser/Tokenizer.cpp

HEADERS += $$parser/TokenParser.h
SOURCES += $$parser/TokenParser.cpp

HEADERS += $$parser/TurtleParser.h
SOURCES += $$parser/TurtleParser.cpp

HEADERS += $$parser/QueryParser.h
SOURCES += $$parser/QueryParser.cpp

HEADERS += $$parser/SpecificParser.h
