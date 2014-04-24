#include <QtTest/QtTest>

#include <libxtypes/String.h>
#include <QObject>
#include <iostream>

class TestString: public QObject
{
	Q_OBJECT

private slots:
	void init();
	void cleanup();

	void test();
	void qstring();
};

void TestString::init()
{}

void TestString::cleanup()
{}

const char* u8 = "Lorem ipsum";
const char16_t* u16 = u"Lorem ipsum";
const char32_t* u32 = U"Lorem ipsum";

void TestString::test()
{
	{
		X::String wee(u16);

		QCOMPARE((const char*) wee.utf8(), u8);
		QVERIFY(wee.utf16() == X::UTF16String(11, 12, u16));
		QVERIFY(wee.utf32() == X::UTF32String(11, 12, u32));
	}

	X::String* wee = new X::String(u16);

	X::UTF8String utf8 = wee->utf8();
	X::UTF16String utf16 = wee->utf16();
	X::UTF32String utf32 = wee->utf32();

	delete wee;

	QCOMPARE((const char*) utf8, u8);
	QVERIFY(utf16 == X::UTF16String(11, 12, u16));
	QVERIFY(utf32 == X::UTF32String(11, 12, u32));
}

void TestString::qstring()
{
	{
		QString s(u8);
		X::String wee(s);

		QCOMPARE((const char*) wee.utf8(), u8);
		QVERIFY(wee.utf16() == X::UTF16String(11, 12, u16));
		QVERIFY(wee.utf32() == X::UTF32String(11, 12, u32));
		QCOMPARE(QString(wee), QString(u8));
	}

	QString* s = new QString(u8);
	X::String wee(*s);
	delete s;

	QCOMPARE((const char*) wee.utf8(), u8);
	QVERIFY(wee.utf16() == X::UTF16String(11, 12, u16));
	QVERIFY(wee.utf32() == X::UTF32String(11, 12, u32));
	QCOMPARE(QString(wee), QString(u8));
}

QTEST_MAIN(TestString)
#include "TestString.moc"
