#include <QtTest/QtTest>

#include <libxtypes/String.h>

#include "../../libxtreeme/parser/Tokenizer.h"
#include "../../libxtreeme/parser/TokenParser.h"
#include "../../libxtreeme/parser/TurtleParser.h"
#include "../../libxtreeme/parser/Turtle.h"
#include "../../libxtreeme/parser/ParseError.h"

#include "../../libxtreeme/expressions/Constant.h"
#include "../../libxtreeme/expressions/Variable.h"

#include "../../libxtreeme/Statement.h"
#include "../../libxtreeme/debug.h"

typedef QLatin1String QS;
typedef QLatin1Char QC;

class TestTurtleParser: public QObject
{
	Q_OBJECT

private slots:
	void test();
	void test_data();
};

QString fileContent(const QString& filename)
{
	QFile file("tests/" + filename);
	file.open(QIODevice::ReadOnly);
	return QString::fromUtf8(file.readAll());
}

#define TEST(num) QTest::newRow("test-" #num) << QString("test-" #num ".ttl") << fileContent("test-" #num ".ttl") << fileContent("test-" #num ".out");

void TestTurtleParser::test_data()
{
	QTest::addColumn<QString>("name");
	QTest::addColumn<QString>("turtle");
	QTest::addColumn<QString>("result");

	TEST(00)
	TEST(01)
	TEST(02)
	TEST(03)
	TEST(04)
	TEST(05)
	TEST(06)
	TEST(07)
	TEST(08)
	TEST(09)
	TEST(10)
	TEST(11)
	TEST(12)
	TEST(13)
	TEST(14)
	TEST(15)
	TEST(16)
	TEST(17)
	TEST(18)
	TEST(19)
	TEST(20)
	TEST(21)
	TEST(22)
	TEST(23)
	TEST(24)
	TEST(25)
	TEST(26)
	TEST(27)
	TEST(28)
	TEST(29)
	TEST(30)
}

QString parseSlashes(const QString& turtle)
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
				case 'u':
					if (i + 4 >= N)
						break; // Error!

					// '\u' hex hex hex hex
					// A Unicode codepoint in the range U+0 to U+FFFF inclusive corresponding to the encoded hexadecimal value.
					{
						bool ok;
						QChar c = turtle.mid(i+1, 4).toUShort(&ok, 16);
						if (ok)
						{
							if (c == '>')
								parsed += '\\';
							else if (c == '"')
								parsed += '\\';

							parsed += c;
						}
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
					parsed += '\\' + turtle[i];
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

#if 0
QVector<Xtreeme::StatementPattern> parse(const QString& turtle, const QUrl& base)
{
	Xtreeme::Tokenizer tokenizer;
	Xtreeme::TokenParser tokenParser(base);
	Xtreeme::TurtleParser turtleParser;

	tokenizer.token.connect([&](const Xtreeme::Token& token) {
		tokenParser.parseToken(token);
	});
	tokenizer.finished.connect([&]() {
		tokenParser.end();
	});
	
	tokenParser.token.connect([&](const Xtreeme::Token& token) {
		turtleParser.parseToken(token);
	});
	tokenParser.finished.connect([&]() {
		turtleParser.end();
	});

	QVector<Xtreeme::StatementPattern> statements;

	turtleParser.statement.connect([&](const Xtreeme::StatementPattern& statement) {
		statements << statement;
	});

	tokenizer.tokenizeData(turtle);
	tokenizer.end();

	return statements;
}
#else
Generated<Xtreeme::Token> parseTokens(const QString& turtle, const QUrl& base)
{
	return Generated<Xtreeme::Token>([=](Yield<Xtreeme::Token>&& yield) {
		Xtreeme::Tokenizer tokenizer;
		Xtreeme::TokenParser tokenParser(base);

		tokenizer.token.connect([&](const Xtreeme::Token& token) {
			tokenParser.parseToken(token);
		});
		tokenizer.finished.connect([&]() {
			tokenParser.end();
		});

		tokenParser.token.connect([&](const Xtreeme::Token& token) {
			qDebug() << "T: " << token.code;
			yield(token);
		});

		tokenizer.tokenizeData(turtle);
		tokenizer.end();
	});
}

Generated<Xtreeme::StatementPattern> parse(const QString& turtle, const QUrl& base)
{
	return parseTurtle(parseTokens(turtle, base));
}
#endif

void TestTurtleParser::test()
{
	QFETCH(QString, name);
	QFETCH(QString, turtle);
	QFETCH(QString, result);

	X::init();

	qDebug() << name;

	try
	{
		auto S = parse(turtle, QS("http://www.w3.org/2001/sw/DataAccess/df1/tests/") + name);

		QString myResult;
/*
		if (name == "test-05.ttl")
			qSwap(S[2], S[3]);

		if (name == "test-07.ttl")
		{
			// Just a swap, nothing illegal.
			QVector<Xtreeme::StatementPattern> my = S;
			S[0] = my[3];
			S[1] = my[4];
			S[2] = my[1];
			S[3] = my[2];
			S[4] = my[0];
		}
*/
		for (const Xtreeme::StatementPattern& s : S)
		{
			Xtreeme::Statement statement;
			statement.subject = Xtreeme::Constant(s.subject).resource();
			statement.predicate = Xtreeme::Constant(s.predicate).resource();
			statement.object = Xtreeme::Constant(s.object).resource();
			statement.context = Xtreeme::Constant(s.context).resource();
			myResult += statement.asTurtle() + '\n';
			qDebug(".");
		}
		qDebug("!");

		if (name == "test-07.ttl")
		{
			myResult.replace("_:genid1", QString(QChar('\0')));
			myResult.replace("_:genid2", "_:genid1");
			myResult.replace(QString(QChar('\0')), "_:genid2");
		}

		QCOMPARE(myResult, parseSlashes(result));
	}
	catch (Xtreeme::ParseError* e)
	{
		QFAIL(QString(*e).toUtf8());
	}
	catch (X::ConversionError e)
	{
		QFAIL(X::String(e).utf8());
	}
}

QTEST_MAIN(TestTurtleParser)
#include "TestTurtleParser.moc"
