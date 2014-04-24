#ifndef X_Binary_h
#define X_Binary_h

#include "X.h"

#include <libxcore/Array.h>
#include "String.h"

#ifdef QT4
#include <QByteArray>
#endif

namespace X
{
	class Binary
	{
		BinaryString p;

	public:
		inline Binary() throw(std::bad_alloc);

		inline Binary(const Binary&) throw();
		
		inline Binary(const String&) throw();
		inline operator String() const throw();

		inline Binary(const BinaryString&) throw();
		inline operator BinaryString() const throw();

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
	inline Binary::Binary() throw(std::bad_alloc)
		: p(0, 0, (const char*) 0)
	{}

	inline Binary::Binary(const Binary& other) throw()
		: p(other.p)
	{}

	inline Binary::Binary(const String& value) throw()
		: p(value.utf8())
	{}

	inline Binary::operator String() const throw()
	{
		return String::fromUtf8(p);
	}

	inline Binary::Binary(const BinaryString& value) throw()
		: p(value)
	{}

	inline Binary::operator BinaryString() const throw()
	{
		return p;
	}

#ifdef QT4
	inline Binary::Binary(const QByteArray& value) throw()
		: p(value.size())
	{
		p.copy(value, value.size());
	}

	inline Binary::operator QByteArray() const throw()
	{
		return (const char*) p;
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
			return std::hash<const char*>()(X::BinaryString(v));
		}
	};
}

#endif
