#ifndef Xtreeme_TurtleParser_h
#define Xtreeme_TurtleParser_h

#include "../libxtreeme.h"

#include <libxcore/Object.h>

#include "Token.h"
#include "../StatementPattern.h"

namespace Xtreeme
{
	class TurtleParserP;
	class TurtleParser: public X::Object
	{
		TurtleParserP* p;

	public:
		TurtleParser();
		~TurtleParser();

		bool inStatement();

		void parseToken(const Xtreeme::Token& token);
		void reset();
		void end();

		X::Signal<StatementPattern> statement;
		X::Signal<> finished;
	};
}

#endif
