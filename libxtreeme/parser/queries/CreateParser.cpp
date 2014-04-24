#include "CreateParser.h"

#include "../ParseError.h"

namespace Xtreeme
{
	bool CreateParser::readSilent(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (t.code == QS("SILENT"))
		{
			ok = true;
			end = true;
			return true;
		}

		return false;
	}

	MultiGraphSelector CreateParser::readGraphSelector(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		return selector.parse(t, ok, end);
	}

	Query* CreateParser::parse(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		bool subEnd = false;

		switch (state)
		{
			case ReadSilent:
			{
				bool silent = readSilent(t, ok, subEnd);

				if (silent)
					query->setSilent(true);

				if (subEnd || !ok)
					state = State(int(state) + 1);

				if (ok)
					break;
			}

			case ReadSelector:
			{
				MultiGraphSelector sel = readGraphSelector(t, ok, subEnd);

				if (!ok)
					throw new ParseError(ParseError::QueryParser, "Expected single graph selector.");

				if (subEnd)
				{
					if (sel.type != MultiGraphSelector::Graph)
						throw new ParseError(ParseError::QueryParser, "Expected single graph selector.");

					query->setGraph(sel.graph);
				}

				if (subEnd || !ok)
					state = State(int(state) + 1);

				if (ok)
					break;
			}

			default:
				end = true;
				return query;
		}

		return 0;
	}
}
