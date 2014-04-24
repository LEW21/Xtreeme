#ifndef Xtreeme_Query_h
#define Xtreeme_Query_h

#include <QVector>

namespace Xtreeme
{
	class Command;
	class Query: public QVector<Command*> {};
}

#endif
