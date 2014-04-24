#include "MultiGraphSelectorParser.h"

#include "../ParseError.h"
#include "../../expressions/Constant.h"

namespace Xtreeme
{
	MultiGraphSelector MultiGraphSelectorParser::parse(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (isGraph)
		{
			if (!t.expr.isConstant())
				throw new ParseError(ParseError::QueryParser, "Expected constant expression.");

			ok = true;
			end = true;

			return Constant(t.expr).resource();
		}

		if (t.code == QS("GRAPH"))
		{
			ok = true;
			isGraph = true;
			return MultiGraphSelector();
		}
		else if (t.code == QS("DEFAULT"))
		{
			ok = true;
			end = true;
			return MultiGraphSelector::Default;
		}
		else if (t.code == QS("NAMED"))
		{
			ok = true;
			end = true;
			return MultiGraphSelector::Named;
		}
		else if (t.code == QS("ALL"))
		{
			ok = true;
			end = true;
			return MultiGraphSelector::All;
		}

		return MultiGraphSelector();
	}
}
