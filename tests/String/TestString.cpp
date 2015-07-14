#include <QtTest/QtTest>

#include <libxtypes/String.h>
#include <QObject>
#include <iostream>
#include <memory>

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

#define COMPARE(A, B) QVERIFY(A == B)

void TestString::test()
{
	{
		X::String wee(u16);

		COMPARE(wee.utf8(), u8);
		COMPARE(wee.utf16(), u16);
		COMPARE(wee.utf32(), u32);
	}

	auto wee = std::make_unique<X::String>(u16);

	auto utf8 = wee->utf8();
	auto utf16 = wee->utf16();
	auto utf32 = wee->utf32();

	wee = {};

	COMPARE(utf8, u8);
	COMPARE(utf16, u16);
	COMPARE(utf32, u32);
}

void TestString::qstring()
{
	{
		QString s(u8);
		X::String wee(s);

		COMPARE(wee.utf8(), u8);
		COMPARE(wee.utf16(), u16);
		COMPARE(wee.utf32(), u32);
		COMPARE(QString(wee), QString(u8));
	}

	auto s = std::make_unique<QString>(u8);
	X::String wee(*s);
	s = {};

	COMPARE(wee.utf8(), u8);
	COMPARE(wee.utf16(), u16);
	COMPARE(wee.utf32(), u32);
	COMPARE(QString(wee), QString(u8));
}

QTEST_MAIN(TestString)
#include "TestString.moc"
