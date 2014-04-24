#include "QueryParser.h"

typedef QLatin1String QS;
typedef QLatin1Char   QC;

using Xtreeme::Token;

#include "TokenParser.h"

#include "ParseError.h"

#include "queries/SelectParser.h"
//#include "queries/CreateParser.h"
//#include "queries/DropParser.h"
//#include "queries/ClearParser.h"
#include "queries/DataParser.h"

#include "../Command.h"

namespace Xtreeme
{
	enum State
	{
		Begin,
		ReadData
	};

	struct QueryParserP
	{
		SpecificQueryParser* parser;

		State state;
		bool insert;
		DataStream* stream;

		inline QueryParserP(): parser(0), state(Begin) {}
	};

	QueryParser::QueryParser(const TokenParser& tokenParser)
		: p(new QueryParserP())
	{
		tokenParser.token.connect([=](const Xtreeme::Token& token) {
			this->parseToken(token);
		}, this);
		tokenParser.finished.connect([=]() {
			this->end();
		}, this);
	}

	QueryParser::QueryParser()
		: p(new QueryParserP())
	{}

	QueryParser::~QueryParser()
	{
		delete p;
	}

	void QueryParser::parseToken(const Token& t)
	{
//Specific:
		if (p->parser)
		{
			bool ok = false;
			bool end = false;

			Query q = p->parser->parse(t, ok, end);

			if (q.size())
				emit query(q);

			if (end)
			{
				emit queryEnded();
				delete p->parser;
				p->parser = 0;
			}

			if (ok)
				return;
		}

		switch (p->state)
		{
			case Begin:
				if (t.code == QS(";"))
					return;

				if (t.code == QS("WITH"))
				{
//					p->parser = new ModifyParser();
//					goto Specific;
				}

				if (t.code == QS("SELECT"))
					p->parser = new SelectParser();
//				else if (t.code == QS("CONSTRUCT"))
//					p->parser = new ConstructParser();
//				else if (t.code == QS("DESCRIBE"))
//					p->parser = new DescribeParser();
//				else if (t.code == QS("ASK"))
//					p->parser = new AskParser();
/*				else if (t.code == QS("CREATE"))
					p->parser = new CreateParser();
				else if (t.code == QS("DROP"))
					p->parser = new DropParser();
				else if (t.code == QS("CLEAR"))
					p->parser = new ClearParser();
				else if (t.code == QS("LOAD"))
					p->parser = new LoadParser();*/
				else if (t.code == QS("DELETE"))
				{	p->state = ReadData; p->insert = false; }
				else if (t.code == QS("INSERT"))
				{	p->state = ReadData; p->insert = true; }
			break;

			case ReadData:
				if (t.code == QS("DATA"))
				{
					InputStream* input = new InputStream();
					Command* command;

					if (p->insert)
						command = new Insert(input->toServer());
					else
						command = new Delete(input->toServer());

					DataParser* parser = new DataParser();
					input->stream = parser->stream;
					p->parser = parser;

					Query q;
					q << input << command;
					emit query(q);

					p->state = Begin;
				}
			break;
		}
	}

	void QueryParser::end()
	{
		emit finished();
	}
}
