#ifndef Xtreeme_QueryParser_h
#define Xtreeme_QueryParser_h

#include "../libxtreeme.h"

#include <libxcore/Object.h>

#include "Token.h"
#include "../Query.h"

namespace Xtreeme
{
	class TokenParser;

	class QueryParserP;
	class QueryParser: public X::Object
	{
		QueryParserP* p;

	public:
		QueryParser(const TokenParser&);
		QueryParser();
		~QueryParser();

		void parseToken(const Xtreeme::Token&);
		void end();

		X::Signal<Query> query;
		X::Signal<> queryEnded;
		X::Signal<> finished;
	};
}

#endif
