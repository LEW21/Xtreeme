#ifndef X_Integer_h
#define X_Integer_h

#include "X.h"

#include "Text.h"
#include "Boolean.h"

namespace X
{
	class Integer
	{
	public:
		Integer(const Integer&);

		Integer(long long);
		operator long long() const;

		Integer(const String&);
		operator String() const;

		Integer(const Boolean&);
		operator Boolean() const;

		bool operator==(const Integer&) const throw();
		inline bool operator!=(const Integer& other) const throw()
		{ return !operator==(other); }
	};

	typedef Integer integer;

	template<> struct isX<Integer> : public std::true_type {};
	template<> struct isStorable<Integer> : public std::true_type {};
	template<> struct isTemporary<Integer> : public std::false_type {};
}

#endif
