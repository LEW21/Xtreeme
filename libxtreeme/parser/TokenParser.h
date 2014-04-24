#ifndef Xtreeme_TokenParser_h
#define Xtreeme_TokenParser_h

#include "Token.h"

#include <libxcore/Object.h>

#include <QUrl>
#include <QStack>

namespace Xtreeme
{
	class Tokenizer;

	class TokenParser: public X::Object
	{
		enum State
		{
			Normal,
			Prefix,
			Namespace,
			Base,
			Lang,
			LiteralType,
			LiteralLang,
			Dot,
			ListNode
		} state;

		QStack<int> collections;

		Token prev;
		QString temp;

		QHash<QString, QString> namespaces;
		QUrl base;
		QString lang;

		uint genId;

	public:
		TokenParser(const QUrl& base);
		TokenParser(const Tokenizer&, const QUrl& base);

		void parseToken(const Xtreeme::Token& token);
		void end();

		X::Signal<Token> token;
		X::Signal<> finished;
	};
}

#endif
