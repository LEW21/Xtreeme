#include "TokenParser.h"

typedef QLatin1String QS;
typedef QLatin1Char   QC;

using Xtreeme::Token;

#include "Tokenizer.h"

#include "../RDF.h"

#include "ParseError.h"

#include "../Resource.h"
#include "../expressions/Constant.h"
#include "../expressions/Variable.h"

#include <libxtypes/Text.h>
#include <libxtypes/URI.h>

static inline QString parseSlashes(const QString& turtle)
{
	QString parsed;
	parsed.reserve(turtle.size());

	bool backslashed = false;

	int N = turtle.size();
	for (int i = 0; i < N; i++)
	{
		if (backslashed)
		{
			backslashed = false;

			switch (turtle[i].unicode())
			{
				case 't':
					parsed += '\t';
				break;

				case 'n':
					parsed += '\n';
				break;

				case 'r':
					parsed += '\r';
				break;

				case 'u':
					if (i + 4 >= N)
						break; // Error!

					// '\u' hex hex hex hex
					// A Unicode codepoint in the range U+0 to U+FFFF inclusive corresponding to the encoded hexadecimal value.
					{
						bool ok;
						ushort c = turtle.mid(i+1, 4).toUShort(&ok, 16);
						if (ok)
							parsed += QChar(c);
						else
							parsed += QChar(QChar::ReplacementCharacter);
						i += 4;
					}
				break;

				case 'U':
					if (i + 8 >= N)
						break; // Error!

					// '\U' hex hex hex hex hex hex hex hex
					// A Unicode codepoint in the range U+10000 to U+10FFFF inclusive corresponding to the encoded hexadecimal value.
					{
						bool ok;
						uint c = turtle.mid(i+1, 8).toUInt(&ok, 16);
						if (ok)
							parsed += QChar(c);
						else
							parsed += QChar(QChar::ReplacementCharacter);
						i += 8;
					}
				break;

				default:
					parsed += turtle[i];
				break;
			}
		}
		else if (turtle[i] == '\\')
			backslashed = true;
		else
			parsed += turtle[i];
	}

	return parsed;
}

#include <QDebug>

namespace Xtreeme
{
	TokenParser::TokenParser(const Tokenizer& tokenizer, const QUrl& b)
		: state(Normal)
		, base(b)
		, genId(0)
	{
		tokenizer.token.connect([=](const Xtreeme::Token& token) {
			this->parseToken(token);
		}, this);
		tokenizer.finished.connect([=]() {
			this->end();
		}, this);

		namespaces["_"] = QString(QC('\0')) + QC('b');
	}

	TokenParser::TokenParser(const QUrl& b)
		: state(Normal)
		, base(b)
		, genId(0)
	{
		namespaces["_"] = QString(QC('\0')) + QC('b');
	}

	void TokenParser::parseToken(const Xtreeme::Token& c)
	{
		if (state == Dot)
		{
			if (c.code != QS("."))
				throw new ParseError(ParseError::TokenParser, "Expected .");

			state = Normal;
			return;
		}

		Token t = c;

		switch (t.type)
		{
			case Token::IRI:
				t.expr = X::IRI(parseSlashes(t.code.mid(1, t.code.size() - 2)));
			break;

			case Token::QName:
			{
				int pos = t.code.indexOf(QC(':'));
				QString prefix = t.code.left(pos);

				if (state != Prefix && !namespaces.contains(prefix))
					throw new ParseError(ParseError::TokenParser, "Unbound prefix: " + prefix);

				t.expr = X::IRI(namespaces[prefix] + t.code.mid(pos + 1));
			}
			break;

			case Token::Variable:
				t.expr = Variable(t.code.mid(1));
			break;

			case Token::Literal:
			break;

			case Token::String:
			{
				QString code = t.code;

				bool singleToken = true;

				if (code.endsWith(QS("^^")))
				{
					state = LiteralType;
					prev = t;
					code = code.left(code.size() - 2);
					singleToken = false;
				}
				else if (code.endsWith(QC('@')))
				{
					state = LiteralLang;
					prev = t;
					code = code.left(code.size() - 1);
					singleToken = false;
				}

				if (code.startsWith(QS("'''")) || code.startsWith(QS("\"\"\"")))
					temp = parseSlashes(code.mid(3, code.size() - 6));
				else
					temp = parseSlashes(code.mid(1, code.size() - 2));

				if (singleToken)
					t.expr = X::Text(temp, lang);
				else
					return;
			}
			break;

			default:
				if ((t.type & Token::Integer) == Token::Integer)
				{
					t.expr = X::variant_createRuntime(X::IRI(u"http://www.w3.org/2001/XMLSchema#integer"), X::String(t.code));
				}
				else if ((t.type & Token::Decimal) == Token::Decimal)
				{
					t.expr = X::variant_createRuntime(X::IRI(u"http://www.w3.org/2001/XMLSchema#decimal"), X::String(t.code));
				}
				else if ((t.type & Token::Float) == Token::Float)
				{
					t.expr = X::variant_createRuntime(X::IRI(u"http://www.w3.org/2001/XMLSchema#double"), X::String(t.code));
				}
				else if ((t.type & Token::Boolean) == Token::Boolean)
				{
					t.expr = X::variant_createRuntime(X::IRI(u"http://www.w3.org/2001/XMLSchema#boolean"), X::String(t.code));
				}
				else if (t.code == QS("@prefix"))
				{
					state = Prefix;
					return;
				}
				else if (t.code == QS("@base"))
				{
					state = Base;
					return;
				}
				else if (t.code == QS("@lang"))
				{
					state = Lang;
					return;
				}
				else if (t.code == QS("a"))
				{
					t.expr = X::IRI(RDF::type);
				}
				else if (t.code == QS("["))
				{
					t.expr = X::IRI(namespaces["_"] + "genid" + QString::number(++genId));
				}
			break;
		}

		if (t.expr.isConstant())
		{
			X::Variant value = Constant(t.expr).resource().value;

			if (value.is<X::IRI>())
			{
				X::IRI iri = value.as<X::IRI>();
				if (!QString(iri).startsWith(QC('\0')))
					t.expr = X::IRI(base.resolved(iri));
			}
			else if (value.is<X::URI>())
			{
				X::URI uri = value.as<X::URI>();
				if (!QString(QByteArray(uri)).startsWith(QC('\0')))
					t.expr = X::URI(base.resolved(uri));
			}
		}

		switch (state)
		{
			case Prefix:
				temp = t.code.left(t.code.size() - 1);
				state = Namespace;
			break;

			case Namespace:
			{
				if (!t.expr.isConstant())
					throw new ParseError(ParseError::TokenParser, "Namespace: Expected IRI.");

				X::Variant value = Constant(t.expr).resource().value;

				if (!value.is<X::IRI>())
					throw new ParseError(ParseError::TokenParser, "Namespace: Expected IRI.");

				namespaces[temp] = QUrl(value.as<X::IRI>()).toString();
				state = Dot;
			}
			break;

			case Base:
			{
				if (!t.expr.isConstant())
					throw new ParseError(ParseError::TokenParser, "Base: Expected IRI.");

				X::Variant value = Constant(t.expr).resource().value;

				if (!value.is<X::IRI>())
					throw new ParseError(ParseError::TokenParser, "Base: Expected IRI.");

				base = QUrl(value.as<X::IRI>()).toString();
				state = Dot;
			}
			break;

			case Lang:
				lang = t.code;
				state = Dot;
			break;

			case LiteralType:
			{
				if (!t.expr.isConstant())
					throw new ParseError(ParseError::TokenParser, "LiteralType: Expected IRI.");

				X::Variant value = Constant(t.expr).resource().value;

				if (!value.is<X::IRI>())
					throw new ParseError(ParseError::TokenParser, "LiteralType: Expected IRI.");

				t.expr = X::metaTypes[X::namedTypes[value.as<X::IRI>()]]->create(X::String(temp));
				t.code = prev.code + t.code;
				t.type = Token::String;
				state = Normal;
			}
			goto def;

			case LiteralLang:
				t.expr  = X::Variant(X::Text(temp, t.code));
				t.code = prev.code + t.code;
				t.type = Token::String;
				state = Normal;
			goto def;

			default:
			def:
				if (t.code == QS("("))
				{
					collections.push(0);
				}
				else if (!collections.isEmpty())
				{
					if (t.code == QS(")"))
					{
						Token n;
						n.code = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#nil>";
						n.expr = X::IRI(u"http://www.w3.org/1999/02/22-rdf-syntax-ns#nil");
						emit token(n);
						n.expr = X::Variant();

						n.code = ']';

						int i = collections.pop();

						while (i--)
							emit token(n);

						break;
					}

					Token n;
					n.code = '[';
					n.expr = X::IRI(namespaces["_"] + "genid" + QString::number(++genId));
					emit token(n);
					n.expr = X::Variant();

					n.code = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#first>";
					n.expr = X::IRI(u"http://www.w3.org/1999/02/22-rdf-syntax-ns#first");
					emit token(n);
					n.expr = X::Variant();

					emit token(t);

					n.code = ';';
					emit token(n);

					n.code = "<http://www.w3.org/1999/02/22-rdf-syntax-ns#rest>";
					n.expr = X::IRI(u"http://www.w3.org/1999/02/22-rdf-syntax-ns#rest");
					emit token(n);
					n.expr = X::Variant();

					++collections.top();
				}
				else
					emit token(t);
			break;
		}
	}

	void TokenParser::end()
	{
		emit finished();
	}
}
