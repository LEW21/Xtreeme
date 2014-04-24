#include "DataParser.h"

#include "../ParseError.h"
#include "../../DataStream.h"

namespace Xtreeme
{
	DataParser::DataParser()
		: started(false)
		, level(0)
		, stream(new DataStream())
	{}

	Query DataParser::parse(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		bool doTurtle = true;

		if (!started)
		{
			stream->header({"ID", "S", "P", "O", "C"});

			turtle.statement.connect([=](const StatementPattern& statement) {
				if (!statement.isConstant())
					throw new ParseError(ParseError::QueryParser, "Unexpected variable statement pattern, expected constant statement.");
				
				stream->data(statement.constant());
			}, stream);

			doTurtle = false;

			if (t.code != QS("{"))
				return Query();

			started = true;
			ok = true;
		}

		if (level)
			ok = true;
		else if (!ok)
			return Query();

		if (t.code == QS("{"))
			++level;
		else if (t.code == QS("}"))
			--level;

		if (!level)
		{
			end = true;
			turtle.end();
			stream->end();
			delete stream;
			return Query();
		}

		if (doTurtle)
			turtle.parseToken(t);

		return Query();
	}
}
