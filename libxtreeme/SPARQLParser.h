#ifndef Xtreeme_SPARQLParser_h
#define Xtreeme_SPARQLParser_h

#include "libxtreeme.h"

#include <libxcore/Object.h>

#include <QUrl>
#include <QString>
#include <libxcore/Signal.h>
#include "Query.h"

namespace Xtreeme
{
	class Database;

	class SPARQLParserP;
	class XTREEME_EXPORT SPARQLParser: public X::Object
	{
		SPARQLParserP* p;

	public:
		SPARQLParser(const QUrl& base);
		~SPARQLParser();

		void parseFragment(const QString&);
		void end();

		inline void parse(const QString& full)
		{
			parseFragment(full);
			end();
		}

		X::Signal<Query> query;
		X::Signal<> finished;
	};
}

#endif
