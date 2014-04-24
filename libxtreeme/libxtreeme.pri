libxtreeme = $$PWD

HEADERS += $$libxtreeme/RDF.h
HEADERS += $$libxtreeme/OWL.h
HEADERS += $$libxtreeme/DC.h

HEADERS += $$libxtreeme/Database.h
SOURCES += $$libxtreeme/Database.cpp

HEADERS += $$libxtreeme/BackendFactory.h

HEADERS += $$libxtreeme/Backend.h
SOURCES += $$libxtreeme/Backend.cpp

HEADERS += $$libxtreeme/Graph.h
SOURCES += $$libxtreeme/Graph.cpp

HEADERS += $$libxtreeme/Resource.h
SOURCES += $$libxtreeme/Resource.cpp

HEADERS += $$libxtreeme/Statement.h
SOURCES += $$libxtreeme/Statement.cpp

HEADERS += $$libxtreeme/StatementPattern.h
SOURCES += $$libxtreeme/StatementPattern.cpp

HEADERS += $$libxtreeme/Expression.h
SOURCES += $$libxtreeme/Expression.cpp

HEADERS += $$libxtreeme/DataStream.h

HEADERS += $$libxtreeme/RemoteQuery.h

HEADERS += $$libxtreeme/Response.h
SOURCES += $$libxtreeme/Response.cpp

HEADERS += $$libxtreeme/SPARQLParser.h
SOURCES += $$libxtreeme/SPARQLParser.cpp

HEADERS += $$libxtreeme/Solution.h
SOURCES += $$libxtreeme/Solution.cpp

HEADERS += $$libxtreeme/Row.h
SOURCES += $$libxtreeme/Row.cpp
