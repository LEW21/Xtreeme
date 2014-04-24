#include "Tokenizer.h"

typedef QLatin1String QS;
typedef QLatin1Char   QC;

QString special = "<>'\"?$,;.()[]{}@";

#define CHECK(char, test)\
	{\
		if (backslashed)\
		{\
			backslashed = false;\
			continue;\
		}\
\
		QChar c = char;\
		if (test)\
		{\
			found = true;\
			break;\
		}\
		else if (c == '\\')\
		{\
			backslashed = true;\
		}\
	}

void find(const QChar& wanted, const QString& buffer, int& offset)
{
	bool backslashed = false;
	bool found = false;

	for (; offset < buffer.size(); ++offset)
		CHECK(buffer[offset], c == wanted)

	++offset;

	if (!found)
		offset = -1;
}

void findSpace(const QString& buffer, int& offset)
{
	bool backslashed = false;
	bool found = false;

	for (; offset < buffer.size(); ++offset)
		CHECK(buffer[offset], c.isSpace() || special.contains(c))

	if (!found)
		offset = -1;
}

void findEndl(const QString& buffer, int& offset)
{
	bool backslashed = false;
	bool found = false;

	for (; offset < buffer.size(); ++offset)
		CHECK(buffer[offset], c == '\n' || c == '\r')

	if (!found)
		offset = -1;
}

const QString sign     = QS("[+-]?");
const QString exponent = QS("[eE]") + sign + QS("[0-9]+");

#include <QRegExp>
const QRegExp integer  = QRegExp(sign + QS("[0-9]+"));
const QRegExp decimal  = QRegExp(sign + QS("([0-9]+\\.[0-9]*|\\.[0-9]+)"));
const QRegExp floating = QRegExp(sign + QS("([0-9]+(\\.[0-9]*)?") + exponent + QS("|\\.[0-9]+") + exponent + QS(")"));;

using Xtreeme::Token;

void parseUnknown(const QString& buffer, Token& t, int& offset, bool end = false)
{
	t.code = buffer.left(offset);

	if (t.code == QS("true") || t.code == QS("false"))
		t.type = Token::Boolean;
	else if (t.code.contains(QC(':')))
		t.type = Token::QName;
	else
	{
		if (t.code[0] == QC('+') || t.code[0] == QC('-'))
			t.type = Token::SignedNumber;
		else
			t.type = Token::UnsignedNumber;

		if (::integer.exactMatch(t.code))
		{
			if (end)
				goto isInt;

			if (buffer.size() <= offset + 1)
			{
				offset = -1;
				return;
			}

			if (buffer[offset] == '.')
			{
				++offset;
				findSpace(buffer, offset);
				t.code = buffer.left(offset);
			}
			else
			{
				isInt:
				t.type = (Token::ResourceType) (int) (t.type | Token::Integer);
				goto afterMatchNum;
			}
		}

		if (::decimal.exactMatch(t.code))
			t.type = (Token::ResourceType) (int) (t.type | Token::Decimal);
		else if (::floating.exactMatch(t.code))
			t.type = (Token::ResourceType) (int) (t.type | Token::Float);
		else
			t.type = Token::None;

		afterMatchNum: {}
	}
}

namespace Xtreeme
{
	X_DEFINE_METATYPE(Xtreeme::Token, Token)

	void Tokenizer::tokenizeData(const QString& data)
	{
		buffer += data;

		while (!buffer.isEmpty())
		{
			Token t;

			int offset;

			QChar first = buffer[0];
			offset = 1;

			if (first.isSpace())
			{
				// TODO faster
				buffer = buffer.mid(1);
				continue;
			}

			switch (first.toLatin1())
			{
			case '#':
				findEndl(buffer, offset);

				if (offset == -1)
					return;

				buffer = buffer.mid(offset);
				continue;
			break;

			case '<':
				t.type = Token::IRI;

				find('>', buffer, offset);

				if (offset == -1)
					return;
			break;

			case '\'':
			case '"':
			{
				t.type = Token::String;

				bool longString = false;

				if (buffer[offset] == first && buffer[offset+1] == first)
				{
					longString = true;
					offset += 2;
				}

				forever
				{
					find(first, buffer, offset);

					if (offset == -1)
						return;

					if (longString)
					{
						if (buffer[offset] == first && buffer[offset+1] == first)
						{
							offset += 2;
							break;
						}
					}
					else break;
				}

				if (buffer[offset] == '@')
					offset += 1;
				else if (buffer[offset] == '^' && buffer[offset + 1] == '^')
					offset += 2;

				if (offset == -1)
					return;
			}
			break;

			case '?':
			case '$':
				t.type = Token::Variable;
				findSpace(buffer, offset);
			break;

			case '.':
			case ';':
			case ',':
			case '(':
			case ')':
			case '[':
			case ']':
			case '{':
			case '}':
			break;

			case '@':
				findSpace(buffer, offset);

				if (offset == -1)
					return;
			break;

			default:
				findSpace(buffer, offset);

				if (offset == -1)
					return;

				parseUnknown(buffer, t, offset);
			break;
			}

			if (t.code.isEmpty())
				t.code = buffer.left(offset);

			emit token(t);
			buffer = buffer.mid(offset);
		}
	}

	void Tokenizer::end()
	{
		if (!buffer.isEmpty())
		{
			Token t;
			int offset = buffer.size();
			parseUnknown(buffer, t, offset, true);
			emit token(t);
			buffer = QString();
		}

		emit finished();
	}
}
