#include "GGPParser.h"

namespace Xtreeme
{
	GGPParser::GGPParser()
		: started(false)
		, level(0)
	{
		turtle.statement.connect([=](const Xtreeme::StatementPattern& pattern) {
			this->data << pattern;
		});
	}

	QVector<StatementPattern> GGPParser::parse(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		bool doTurtle = true;

		if (!started)
		{
			doTurtle = false;

			if (t.code != QS("{"))
				return QVector<StatementPattern>();

			started = true;
			ok = true;
		}

		if (level)
			ok = true;
		else if (!ok)
			return QVector<StatementPattern>();

		if (t.code == QS("{"))
			++level;
		else if (t.code == QS("}"))
			--level;

		if (!level)
		{
			end = true;
			turtle.end();
			return data;
		}

		if (doTurtle)
			turtle.parseToken(t);

		return QVector<StatementPattern>();
	}

/*
	class GroupPattern
	{
	protected:
		SharedDataPointer<GroupPatternP> p;

	public:
		enum Type
		{
			Basic,
			Group,
			Optional,
			Union,
			Graph
		};
	};

	struct BasicGraphPatternP
	{
		QVector<Statement> statements;
	}

	struct GroupGraphPatternP
	{
		QVector<GroupGraphPattern> patterns;
	}

	struct OptionalGraphPatternP
	{
		GroupGraphPattern pattern;
	}

	struct UnionGraphPatternP
	{
		QVector<GroupGraphPattern> patterns;
	}

	struct GraphGraphPatternP
	{
		Resource graph;
		GroupGraphPattern pattern;
	}
*/ 
}