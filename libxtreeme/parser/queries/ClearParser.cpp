#include "ClearParser.h"

#include "../ParseError.h"

namespace Xtreeme
{
	bool ClearParser::readSilent(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (t.code == QS("SILENT"))
		{
			ok = true;
			end = true;
			return true;
		}

		return false;
	}

	MultiGraphSelector ClearParser::readGraphSelector(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		return selector.parse(t, ok, end);
	}

	Query* ClearParser::parse(const Xtreeme::Token& t, bool& ok, bool& end)
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
					throw new ParseError(ParseError::QueryParser, "Expected multi graph selector.");

				if (subEnd)
					query->setWhat(sel);

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
