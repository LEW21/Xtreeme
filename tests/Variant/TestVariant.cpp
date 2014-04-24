#include <QtTest/QtTest>

#include <libxcore/Variant.h>
#include <libxcore/PlainType.h>
#include <libxcore/ComplexType.h>
#include <QObject>
#include <ATL/queue.h>

struct ComplexObjectStateQueue
{
	ATL::Queue<const char*> actions;
	ATL::Queue<const void*> pointers;

	ComplexObjectStateQueue& operator<<(const char* action)
	{
		actions.push(action);
		return *this;
	}

	ComplexObjectStateQueue& operator<<(const void* pointer)
	{
		pointers.push(pointer);
		return *this;
	}
};

ComplexObjectStateQueue* stateQueue = 0;

struct ComplexSmallObject
{
	X::Word val;

	ComplexSmallObject()
	{
		if (stateQueue)
			*stateQueue << "()" << this;
	}

	ComplexSmallObject(X::Word v): val(v)
	{
		if (stateQueue)
			*stateQueue << "(Word)" << this;
	}

	ComplexSmallObject(const ComplexSmallObject& other): val(other.val)
	{
		if (stateQueue)
			*stateQueue << "(const&)" << this;
	}

	ComplexSmallObject(ComplexSmallObject&& other): val(other.val)
	{
		if (stateQueue)
			*stateQueue << "(&&)" << this;
	}

	~ComplexSmallObject()
	{
		if (stateQueue)
			*stateQueue << "~()";// << this;
	}

	ComplexSmallObject& operator=(const ComplexSmallObject& other)
	{
		if (stateQueue)
			*stateQueue << "=(const&)" << this << &other;
		val = other.val;
		return *this;
	}

	ComplexSmallObject& operator=(ComplexSmallObject&& other)
	{
		if (stateQueue)
			*stateQueue << "=(&&)" << this << &other;
		val = other.val;
		return *this;
	}

	bool operator==(const ComplexSmallObject& other) const
	{
		if (stateQueue)
			*stateQueue << "==" << this << &other;
		return val == other.val;
	}
};

struct ComplexBigObject
{
	X::Word val1;
	X::Word val2;

	ComplexBigObject()
	{
		if (stateQueue)
			*stateQueue << "()" << this;
	}

	ComplexBigObject(X::Word v1, X::Word v2): val1(v1), val2(v2)
	{
		if (stateQueue)
			*stateQueue << "(Word, Word)" << this;
	}

	ComplexBigObject(const ComplexBigObject& other): val1(other.val1), val2(other.val2)
	{
		if (stateQueue)
			*stateQueue << "(const&)" << this;
	}

	ComplexBigObject(ComplexBigObject&& other): val1(other.val1), val2(other.val2)
	{
		if (stateQueue)
			*stateQueue << "(&&)" << this;
	}

	~ComplexBigObject()
	{
		if (stateQueue)
			*stateQueue << "~()";// << this;
	}

	ComplexBigObject& operator=(const ComplexBigObject& other)
	{
		if (stateQueue)
			*stateQueue << "=(const&)" << this << &other;
		val1 = other.val1;
		val2 = other.val2;
		return *this;
	}

	ComplexBigObject& operator=(ComplexBigObject&& other)
	{
		if (stateQueue)
			*stateQueue << "=(&&)" << this << &other;
		val1 = other.val1;
		val2 = other.val2;
		return *this;
	}

	bool operator==(const ComplexBigObject& other) const
	{
		if (stateQueue)
			*stateQueue << "==" << this << &other;
		return val1 == other.val1 && val2 == other.val2;
	}
};

namespace std
{
	template<>
	struct hash<ComplexSmallObject>
	{
		size_t operator()(const ComplexSmallObject& v) const
		{
			return 0;
		}
	};
}

namespace std
{
	template<>
	struct hash<ComplexBigObject>
	{
		size_t operator()(const ComplexBigObject& v) const
		{
			return 0;
		}
	};
}

namespace X
{
	template<> TypeID typeOf<char>::type = newType();
	template<> TypeID typeOf<const char*>::type = newType();
	template<> TypeID typeOf<ComplexSmallObject>::type = newType();
	template<> TypeID typeOf<ComplexBigObject>::type = newType();
}

void init()
{
	X::coreTypes[X::typeOf<char>::type] = new X::PlainType();
	X::coreTypes[X::typeOf<const char*>::type] = new X::PlainType();
	X::coreTypes[X::typeOf<ComplexSmallObject>::type] = new X::ComplexType<ComplexSmallObject>();
	X::coreTypes[X::typeOf<ComplexBigObject>::type] = new X::ComplexType<ComplexBigObject>();
}

template <class T>
void createCopyTest(T value)
{
	X::Variant v(value);
	QVERIFY(v.is<T>());
	QCOMPARE(v.as<T>(), value);
}

template <class T>
void createCopyComplexTest(T value)
{
	stateQueue = new ComplexObjectStateQueue;

	X::Variant* v = new X::Variant(value);
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "(const&)");
	QVERIFY(stateQueue->actions.isEmpty());

	QVERIFY(v->is<T>());
	QVERIFY(stateQueue->actions.isEmpty());
	QCOMPARE(v->as<T>(), value);
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "(const&)");
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "==");
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "~()");
	QVERIFY(stateQueue->actions.isEmpty());

	delete v;
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "~()");
	QVERIFY(stateQueue->actions.isEmpty());

	delete stateQueue;
}

template <class T>
void createMoveTest(T value)
{
	T valueCopy = value;

	X::Variant v(std::move(valueCopy));

	QVERIFY(v.is<T>());
	QCOMPARE(v.as<T>(), value);
}

template <class T>
void createMoveComplexTest(T value)
{
	stateQueue = new ComplexObjectStateQueue;
{
	T valueCopy = value;

	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "(const&)");
	QVERIFY(stateQueue->actions.isEmpty());

	X::Variant* v = new X::Variant(std::move(valueCopy));
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "(&&)");
	QVERIFY(stateQueue->actions.isEmpty());

	QVERIFY(v->is<T>());
	QVERIFY(stateQueue->actions.isEmpty());

	QCOMPARE(v->as<T>(), value);
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "(const&)");
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "==");
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "~()");
	QVERIFY(stateQueue->actions.isEmpty());

	delete v;
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "~()");
	QVERIFY(stateQueue->actions.isEmpty());
}
	QVERIFY(!stateQueue->actions.isEmpty());
	QCOMPARE(stateQueue->actions.pop(), "~()");
	QVERIFY(stateQueue->actions.isEmpty());

	delete stateQueue;
}

template <class T>
void copyTest(T value)
{
	X::Variant v(value);
	X::Variant c = v;

	QVERIFY(c.is<T>());
	QCOMPARE(c.as<T>(), value);
}

template <class T>
void moveTest(T value)
{
	X::Variant v(value);
	X::Variant c = std::move(v);

	QVERIFY(c.is<T>());
	QCOMPARE(c.as<T>(), value);
}

class TestVariant: public QObject
{
	Q_OBJECT

public:
	inline TestVariant() { init(); }

private slots:
	void createCopy();
	void createMove();
	void copy();
	void move();
};

void TestVariant::createCopy()
{
	createCopyTest(true);
	createCopyTest(false);
	createCopyTest('a');
	createCopyTest("Weeee");
	createCopyComplexTest(ComplexSmallObject(X::Word(10)));
	createCopyComplexTest(ComplexBigObject(X::Word(10), X::Word(20)));
}

void TestVariant::createMove()
{
	createMoveTest(true);
	createMoveTest(false);
	createMoveTest('a');
	createMoveTest("Weeee");
	createMoveComplexTest(ComplexSmallObject(X::Word(10)));
	createMoveComplexTest(ComplexBigObject(X::Word(10), X::Word(20)));
}

void TestVariant::copy()
{
	copyTest(true);
	copyTest(false);
	copyTest('a');
	copyTest("Weeee");
	copyTest(ComplexSmallObject(X::Word(10)));
	copyTest(ComplexBigObject(X::Word(10), X::Word(20)));
}

void TestVariant::move()
{
	moveTest(true);
	moveTest(false);
	moveTest('a');
	moveTest("Weeee");
	moveTest(ComplexSmallObject(X::Word(10)));
	moveTest(ComplexBigObject(X::Word(10), X::Word(20)));
}

QTEST_MAIN(TestVariant)
#include "TestVariant.moc"
