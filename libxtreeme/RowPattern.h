#ifndef Xtreeme_RowPattern_h
#define Xtreeme_RowPattern_h

#include "libxtreeme.h"

#include <QVector>
#include "Expression.h"

namespace Xtreeme
{
	class Header;
	class Row;

	class RowPattern: public QVector<Expression>
	{
	public:
		inline RowPattern() {}
		inline RowPattern(const std::initializer_list<Expression>& row)
		{
			for (auto it = row.begin(); it < row.end(); ++it)
				(*this) << *it;
		}

		template <class T> inline void bind(const T& bindings);
		template <class T> inline RowPattern bound(const T& bindings);

		inline explicit operator Row() const;
	};
}

#include "expressions/Variable.h"
#include "expressions/Constant.h"

#include "Header.h"
#include "Row.h"

namespace Xtreeme
{
	template <class T>
	inline void RowPattern::bind(const T& bindings)
	{
		for (Expression& expr : *this)
		{
			if (!expr.isVariable())
				continue;
			
			expr = bindings[Variable(expr).name()];
		}
	}

	template <class T>
	inline RowPattern RowPattern::bound(const T& bindings)
	{
		RowPattern copy = *this;
		copy.bind(bindings);
		return copy;
	}

	inline RowPattern::operator Row() const
	{
		Row row;
		for (const Expression& expr : *this)
		{
			if (expr.isVariable())
				throw "Tried to convert non-const RowPattern to a Row.";

			row << Constant(expr).resource();
		}
		return row;
	}

	template <class E, class C> struct BindingsPairImpl
	{
		Header header;
		C row;

		inline BindingsPairImpl(const Header& h, const C& r): header(h), row(r) {}

		inline E operator[](const QString& variable)
		{
			for (int i = 0; i < header.size(); ++i)
				if (header[i] == variable)
					return row[i];
		}
	};

	template <class E> struct BindingsPair {};
	template <> struct BindingsPair<Resource>: public BindingsPairImpl<Resource, Row>
	{
		inline BindingsPair(const Header& h, const Row& r): BindingsPairImpl(h, r) {}
	};
	template <> struct BindingsPair<Expression>: public BindingsPairImpl<Expression, RowPattern>
	{
		inline BindingsPair(const Header& h, const RowPattern& r): BindingsPairImpl(h, r) {}
	};

	template <class E> struct BindingsHash
	{
		QHash<QString, E> hash;

		inline E operator[](const QString& variable)
		{
			return hash[variable];
		}
	};
}

#endif
