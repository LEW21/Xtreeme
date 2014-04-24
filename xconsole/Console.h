#include <libxcore/Signal.h>

class QString;

namespace Xtreeme
{
	class Database;
	class SPARQLParser;
	class DataStream;
}

class Console
{
	Xtreeme::Database* db;
	Xtreeme::SPARQLParser* parser;

	Xtreeme::SPARQLParser* newParser();

public:
	Console(Xtreeme::Database* db);
	~Console();

	void evaluateFragment(const QString&);

	X::Signal<const Xtreeme::DataStream*> stream;
};
