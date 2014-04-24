#include <QtTest/QtTest>

#include "../../libxtreeme/parser/Tokenizer.h"
#include "../../libxtreeme/parser/TokenParser.h"
#include "../../libxtreeme/expressions/Constant.h"
#include "../../libxtreeme/expressions/Variable.h"
#include "../../libxtreeme/parser/ParseError.h"

class TestTokenParser: public QObject
{
	Q_OBJECT

private slots:
	void test();
	void withTokenizer();
};

void TestTokenParser::test()
{
	Xtreeme::TokenParser parser(QUrl("http://xtreeme.org/"));
	QVector<Xtreeme::Token> tokens;

	parser.token.connect([&](const Xtreeme::Token& token) {
		tokens << token;
	});

	try
	{
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::IRI,    "<http://lew21.net>"));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::String, "\"weee\""));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::None,   "."));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::None,   "@prefix"));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::QName,  "lol:"));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::IRI,    "<http://lol/>"));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::None,   "."));
		parser.parseToken(Xtreeme::Token(Xtreeme::Token::QName,  "lol:a"));
		parser.end();
	}
	catch (Xtreeme::ParseError* e)
	{
		qDebug() << QString(*e);
		throw e;
	}

	Xtreeme::Expression e1 = tokens[0].expr;
	QVERIFY(e1.isConstant());
	QCOMPARE(QString(Xtreeme::Constant(e1).resource().value.as<X::IRI>()), QString("http://lew21.net"));

	Xtreeme::Expression e2 = tokens[1].expr;
	QVERIFY(e2.isConstant());
	QCOMPARE(QString(Xtreeme::Constant(e2).resource().value.as<X::String>()), QString("weee"));

	Xtreeme::Expression e3 = tokens[2].expr;
	QVERIFY(!e3.isValid());

	Xtreeme::Expression e4 = tokens[3].expr;
	QVERIFY(e4.isConstant());
	QCOMPARE(QString(Xtreeme::Constant(e4).resource().value.as<X::IRI>()), QString("http://lol/a"));
}

void TestTokenParser::withTokenizer()
{
	Xtreeme::Tokenizer tokenizer;
	Xtreeme::TokenParser parser(QUrl("http://xtreeme.org/"));
	QVector<Xtreeme::Token> tokens;

	tokenizer.token.connect([&](const Xtreeme::Token& token) {
		parser.parseToken(token);
	});

	tokenizer.finished.connect([&]() {
		parser.end();
	});

	parser.token.connect([&](const Xtreeme::Token& token) {
		tokens << token;
	});

	tokenizer.tokenizeData("<http://lew21.net> \"weee\".");
	tokenizer.end();

	QVERIFY(tokens[0].code == "<http://lew21.net>");
	QVERIFY(tokens[1].code == "\"weee\"");
	QVERIFY(tokens[2].code == ".");

	QVERIFY(tokens[0].type == Xtreeme::Token::IRI);
	QVERIFY(tokens[1].type == Xtreeme::Token::String);
	QVERIFY(tokens[2].type == Xtreeme::Token::None);

	Xtreeme::Expression e1 = tokens[0].expr;
	QVERIFY(e1.isConstant());

	QCOMPARE(QString(Xtreeme::Constant(e1).resource().value.as<X::IRI>()), QString("http://lew21.net"));
}

QTEST_MAIN(TestTokenParser)
#include "TestTokenParser.moc"
