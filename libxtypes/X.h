#ifndef X_h
#define X_h

#include <type_traits>

#ifdef QT_CORE_LIB
# ifndef QT4
#  define QT4
# endif
#endif

#define X_NS u"http://xtreeme.org/X/"

#include <libxcore/Type.h>

namespace X
{
	template<class T> struct isX : public std::false_type {};
	template<class T> struct isStorable : public std::false_type {};
	template<class T> struct isTemporary : public std::false_type {};

	template<class F, class T> struct canConvert : public std::false_type {};
	template<class T> struct canConvert<T, T> : public std::true_type {};

	struct ConversionErrorBase
	{
		TypeID from;
		TypeID to;

		ConversionErrorBase(TypeID from, TypeID to) throw();
	};

	void init();
}

#endif
