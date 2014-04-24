#include <QtTest/QtTest>

#include <libxcore/SharedDataPointer.h>
#include <libxcore/SharedData.h>

#include <QDebug>

struct TestData: public X::SharedData
{
	bool* deleted;
	TestData(bool* d): deleted(d) {}
	~TestData() {*deleted = true;}

	X::SharedData* copy() const;
};

X::SharedData* TestData::copy() const
{
	return new TestData(new bool(false));
}

class TestSharedData: public QObject
{
	Q_OBJECT

	bool deleted;
	TestData* data;

private slots:
	void init();
	void cleanup();

	void copy();
	void null();
	void editable();
	void editableCopy();
	void move();
};

void TestSharedData::init()
{
	deleted = false;
	data = new TestData(&deleted);
}

void TestSharedData::cleanup()
{
	if (!deleted)
		delete data;
}

void TestSharedData::copy()
{
	{
		X::SharedDataPointer<TestData> p(data);
		X::SharedDataPointer<TestData> copy(p);
		QVERIFY(!p.isNull());
		QVERIFY(p == copy);
		QCOMPARE(p->refs.load(), 2);
	}
	QVERIFY(deleted);
}

void TestSharedData::null()
{
	{
		X::SharedDataPointer<TestData> p(data);
		X::SharedDataPointer<TestData> other(0);
		QVERIFY(!p.isNull());
		QVERIFY(other.isNull());
		QCOMPARE(p->refs.load(), 1);
	}
	QVERIFY(deleted);
}

void TestSharedData::editable()
{
	{
		X::SharedDataPointer<TestData> p(data);
		QVERIFY(p.editable() != 0);
		QVERIFY(p.editable() == data);
		QCOMPARE(p->refs.load(), 1);
	}
	QVERIFY(deleted);
}

void TestSharedData::editableCopy()
{
	{
		X::SharedDataPointer<TestData> p(data);
		X::SharedDataPointer<TestData> copy(p);
		QVERIFY(copy.editable() != data);
		QVERIFY(copy.editable() != 0);
		QVERIFY(p.editable() != 0);
		QVERIFY(p.editable() == data);
		QCOMPARE(p->refs.load(), 1);
	}
	QVERIFY(deleted);
}

void TestSharedData::move()
{
	{
		X::SharedDataPointer<TestData> p(data);
		X::SharedDataPointer<TestData> other = std::move(p);
		QCOMPARE(p.isValid(), false);
		QCOMPARE(other->refs.load(), 1);
	}
	QVERIFY(deleted);
}

QTEST_MAIN(TestSharedData)
#include "TestSharedData.moc"
