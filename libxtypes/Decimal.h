#ifndef X_Decimal_h
#define X_Decimal_h

#include "X.h"

#include "Text.h"
#include "Boolean.h"
#include "Integer.h"

namespace X
{
	class Decimal
	{
	public:
		Decimal(const Decimal&);

		Decimal(long long, long long exponent = 0);
		operator long long() const;

		Decimal(const String&);
		operator String() const;

		Decimal(const Integer&, const Integer& exponent = 0);
		operator Integer() const;

		Decimal(const Boolean&);
		operator Boolean() const;

		bool operator==(const Decimal&) const throw();
		inline bool operator!=(const Decimal& other) const throw()
		{ return !operator==(other); }
	};

	typedef Decimal decimal;

	template<> struct isX<Decimal> : public std::true_type {};
	template<> struct isStorable<Decimal> : public std::true_type {};
	template<> struct isTemporary<Decimal> : public std::false_type {};
}

#endif
