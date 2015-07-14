#ifndef X_Binary_h
#define X_Binary_h

#include "X.h"

#include <string>
#include "String.h"

#ifdef QT4
#include <QByteArray>
#endif

namespace X
{
	class Binary
	{
		std::string p;

	public:
		inline Binary() = default;
		inline Binary(const Binary&) = default;
		
		inline Binary(const String&) throw();
		inline operator String() const throw();

		inline Binary(const std::string&) throw();
		inline operator std::string() const throw();

#ifdef QT4
		inline Binary(const QByteArray&) throw();
		inline operator QByteArray() const throw();
#endif

		inline bool operator==(const Binary& other) const throw() {return p == other.p;}
		inline bool operator!=(const Binary& other) const throw() {return p != other.p;}
	};

	typedef Binary binary;

	template<> struct isX<Binary> : public std::true_type {};
	template<> struct isStorable<Binary> : public std::true_type {};
	template<> struct isTemporary<Binary> : public std::false_type {};
}

namespace X
{
	inline Binary::Binary(const String& value) throw()
		: p(value.utf8())
	{}

	inline Binary::operator String() const throw()
	{
		return String::fromUtf8(p);
	}

	inline Binary::Binary(const std::string& value) throw()
		: p(value)
	{}

	inline Binary::operator std::string() const throw()
	{
		return p;
	}

#ifdef QT4
	inline Binary::Binary(const QByteArray& value) throw()
		: p((const char*) value, value.size())
	{}

	inline Binary::operator QByteArray() const throw()
	{
		return p.data();
	}
#endif
}

namespace std
{
	template<>
	struct hash<X::Binary>
	{
		size_t operator()(const X::Binary& v) const
		{
			return std::hash<std::string>()(v);
		}
	};
}

#endif
