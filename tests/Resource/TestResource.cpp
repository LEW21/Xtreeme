#include <QtTest/QtTest>

#define private public

#include "../../libxtreeme/Resource.h"

#undef private

class TestResource: public QObject
{
	Q_OBJECT

private slots:
	void init();
	void cleanup();

	void null();
	void named();
};

void TestResource::init()
{}

void TestResource::cleanup()
{}

void TestResource::null()
{
	Xtreeme::Resource res;
	QVERIFY(!res.isValid());
}

void TestResource::named()
{
	Xtreeme::Resource res(X::IRI(u"http://lew21.net/"));
qDebug("a");
	QVERIFY(res.value.is<X::IRI>());
	{
		qDebug("b");
		Xtreeme::Resource copy(res);
		qDebug("c");
		QVERIFY(res.value.is<X::IRI>());
		qDebug("d");
		QVERIFY(copy.value.is<X::IRI>());
		qDebug("e");
	}

	QVERIFY(res.value.is<X::IRI>());
}

QTEST_MAIN(TestResource)
#include "TestResource.moc"
