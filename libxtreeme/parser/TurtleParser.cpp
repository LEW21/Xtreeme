#include "TurtleParser.h"

typedef QLatin1String QS;
typedef QLatin1Char   QC;

using Xtreeme::Token;

#include "../RDF.h"

#include "ParseError.h"

#include <QStack>

namespace Xtreeme
{
	enum StateType
	{
		Normal,
		Description,
		Value,
		EndOfStatement,
		Graph,
		Open
	};

	struct State
	{
		StateType type;
		StatementPattern tpl;
	};

	struct TurtleParserP
	{
		QStack<State> states;
		QStack<Expression> graphs;
	};

	TurtleParser::TurtleParser()
		: p(new TurtleParserP())
	{
		State s;
		s.type = Normal;
		s.tpl.context = Resource();
		p->states.push(s);
	}

	TurtleParser::~TurtleParser()
	{
		delete p;
	}

	void TurtleParser::reset()
	{
		p->states.clear();
		p->graphs.clear();

		State s;
		s.type = Normal;
		s.tpl.context = Resource();
		p->states.push(s);
	}

	bool TurtleParser::inStatement()
	{
		return p->states.size() > 1 || p->states.top().type != Normal;
	}

	void TurtleParser::parseToken(const Xtreeme::Token& c)
	{
		bool expected = false;

		switch (p->states.top().type)
		{
			case Normal:
				if (c.expr.isValid())
				{
					p->states.top().tpl.subject = c.expr;
					p->states.top().type = Description;
					expected = true;
				}
				else if (c.code == QS("GRAPH"))
				{
					p->states.top().type = Graph;
					expected = true;
				}
				else if (c.code == QS("}") && !p->graphs.isEmpty())
				{
					p->graphs.pop();
					expected = true;
				}
			break;

			case Graph:
				if (c.expr.isValid())
				{
					p->graphs.push(c.expr);
					p->states.top().type = Open;
					expected = true;
				}
			break;

			case Open:
				if (c.code == QS("{"))
				{
					p->states.top().type = Normal;
					expected = true;
				}
			break;

			case Description:
				if (c.expr.isValid())
				{
					p->states.top().tpl.predicate = c.expr;
					p->states.top().type = Value;
					expected = true;
				}
				else if (c.code == QS("]") && p->states.size() >= 2)
				{
					p->states.pop();
					expected = true;
				}
			break;

			case Value:
				if (c.expr.isValid())
				{
					p->states.top().tpl.object = c.expr;
					p->states.top().type = EndOfStatement;
					if (!p->graphs.isEmpty()) p->states.top().tpl.context = p->graphs.top();
					emit statement(p->states.top().tpl);
					expected = true;
				}
			break;

			case EndOfStatement:
				if (c.code == QS(".") && p->states.size() == 1) // Dot is not allowed in [ ... ] statements
				{
					p->states.top().type = Normal;
					expected = true;
				}
				else if (c.code == QS(";"))
				{
					p->states.top().type = Description;
					expected = true;
				}
				else if (c.code == QS(","))
				{
					p->states.top().type = Value;
					expected = true;
				}
				else if (c.code == QS("}") && !p->graphs.isEmpty())
				{
					p->graphs.pop();
					expected = true;
				}
				else if (c.code == QS("]") && p->states.size() >= 2)
				{
					p->states.pop();
					expected = true;
				}
			break;
		}

		if (c.code == QS("["))
		{
			State s;
			s.type = Description;
			s.tpl.subject = c.expr;
			p->states.push(s);
		}

		if (!expected)
			throw new ParseError(ParseError::TurtleParser, "Unexpected: " + c.code);
	}

	void TurtleParser::end()
	{
		emit finished();
	}
}
