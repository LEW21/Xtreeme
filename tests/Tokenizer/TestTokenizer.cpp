#include <QtTest/QtTest>

#include "../../libxtreeme/parser/Tokenizer.h"
#include "../../libxtreeme/expressions/Constant.h"
#include "../../libxtreeme/expressions/Variable.h"

class TestTokenizer: public QObject
{
	Q_OBJECT

private slots:
	void test();
};

void TestTokenizer::test()
{
	Xtreeme::Tokenizer tokenizer;
	QVector<Xtreeme::Token> tokens;
	
	tokenizer.token.connect([&](const Xtreeme::Token& token) {
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
}

QTEST_MAIN(TestTokenizer)
#include "TestTokenizer.moc"
