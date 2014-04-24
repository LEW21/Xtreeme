#include "SPARQLParser.h"

#include "parser/Tokenizer.h"
#include "parser/TokenParser.h"
#include "parser/QueryParser.h"

namespace Xtreeme
{
	struct SPARQLParserP
	{
		Tokenizer tokenizer;
		TokenParser tokenParser;
		QueryParser queryParser;

		inline SPARQLParserP(const QUrl& base);
	};

	SPARQLParserP::SPARQLParserP(const QUrl& base)
		: tokenParser(tokenizer, base)
		, queryParser(tokenParser)
	{}

	SPARQLParser::SPARQLParser(const QUrl& base)
		: p(new SPARQLParserP(base))
	{
		p->queryParser.query.connect([=](const Xtreeme::Query& query) {
			this->query(query);
		});
		p->queryParser.finished.connect([=]() {
			this->finished();
		});
	}

	SPARQLParser::~SPARQLParser()
	{
		delete p;
	}

	void SPARQLParser::parseFragment(const QString& fragment)
	{
		p->tokenizer.tokenizeData(fragment);
	}

	void SPARQLParser::end()
	{
		p->tokenizer.end();
	}
}
