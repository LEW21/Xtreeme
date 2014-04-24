#include "Trig.h"

#include "Turtle.h"
#include "ParseError.h"

namespace Xtreeme
{
	Generated<StatementPattern> parseGTurtle(const Iterable<Token>& tokens, StatementPattern tpltpl)
	{
		return Generated<StatementPattern>([=](Yield<StatementPattern>&& yield) {
			auto t = tokens.begin();

			for (;;)
			{
				StatementPattern tpl;

				if (t->expr.isValid())
				{
					tpl.context = t->expr;
					++t;
				}

				if (t->code == u"=")
					++t;

				if (t->code == u"{")
					++t;
				else
					throw ParseError(ParseError::TurtleParser, "Unexpected: " + t->code);

				yield << parseTurtle(pass(t), tpl);

				if (t->code == u"}")
					++t;
				else
					throw ParseError(ParseError::TurtleParser, "Unexpected: " + t->code);

				if (t->code == u".")
					++t;
			}
		});
	}
}
