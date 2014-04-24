#ifndef X_Boolean_h
#define X_Boolean_h

#include "X.h"

namespace X
{
	typedef bool Boolean;
	typedef Boolean boolean;

	template<> struct isX<Boolean> : public std::true_type {};
	template<> struct isStorable<Boolean> : public std::true_type {};
	template<> struct isTemporary<Boolean> : public std::false_type {};
}

#endif
