#include "SelectParser.h"

#include "../../Command.h"

namespace Xtreeme
{
	Distinct* SelectParser::readDistinct(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (t.code == QS("DISTINCT"))
		{
			ok = true;
			end = true;
			return new Distinct(Stream());
		}
		return 0;
	}

	Reduced* SelectParser::readReduced(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (t.code == QS("REDUCED"))
		{
			ok = true;
			end = true;
			return new Reduced(Stream());
		}
		return 0;
	}

	Project* SelectParser::readProjection(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (t.code == QS("*"))
		{
			ok = true;
			end = true;
			return 0;
		}

		// TODO read Projection...
		return 0;
	}

	void SelectParser::readWhereWord(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		if (t.code == QS("WHERE"))
		{
			ok = true;
			end = true;
		}
	}

	QVector<StatementPattern> SelectParser::readGGP(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		return ggp.parse(t, ok, end);
	}
	
#define ENDSTATE \
{\
	if (subEnd || !ok)\
		state = State(int(state) + 1);\
\
	if (ok)\
		break;\
}

	Query SelectParser::parse(const Xtreeme::Token& t, bool& ok, bool& end)
	{
		bool subEnd = false;

		switch (state)
		{
			case ReadDistinctReduced:
			{
//				qDebug("ReadDistinctReduced");
				Distinct* d = readDistinct(t, ok, subEnd);

				if (d)
					distinct = d;
				else
				{
					Reduced* r = readReduced(t, ok, subEnd);
					
					if (r)
						reduced = r;
				}
			}
			ENDSTATE;

			case ReadProjection:
			{
//				qDebug("ReadProjection");
				Project* mod = readProjection(t, ok, subEnd);

				if (mod)
					project = mod;
			}
			ENDSTATE;

			case ReadWhereWord:
//				qDebug("ReadWhereWord");
				readWhereWord(t, ok, subEnd);
			ENDSTATE;

			case ReadGGP:
			{
//				qDebug("ReadGGP");
				QVector<StatementPattern> p = readGGP(t, ok, subEnd);

				if (!p.isEmpty())
				{
					QVector<RowPattern> pattern;
					foreach (const StatementPattern& s, p)
						pattern << s;
					solve = new Solve(pattern, Stream());
				}
			}
			ENDSTATE;
/*
			case ReadModifiers:
				sth = readModifier(ok);

				if (sth)
					...

				if (ok)
					break;
				else
					++state;
*/
			default:
//				qDebug("default");
				end = true;

				return createPipeline();
		}

		return Query();
	}

#define PIPE(op, in, out)\
{\
	op->input = in;\
	out = op->output();\
	pipeline << op;\
}

	inline Query SelectParser::createPipeline()
	{
		Query pipeline;
		Stream data;

/*		if (dataset)
		{
			
		}
		else*/
		{
			DB* db = new DB();
			data = db->data();
			pipeline << db;
		}

		if (solve)
			PIPE(solve, data, data);

		if (project)
			PIPE(project, data, data);

		if (distinct)
			PIPE(distinct, data, data);

		if (reduced)
			PIPE(reduced, data, data);

		OutputStream* output = new OutputStream(data);
		pipeline << output;

		return pipeline;
	}
}
