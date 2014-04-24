#ifndef X_URI_h
#define X_URI_h

#include "X.h"

#include "Binary.h"
#include "String.h"
#include "IRI.h"

#ifdef QT4
#include <QByteArray>
#include <QUrl>
#endif

namespace X
{
	class URI
	{
		Binary v;

	public:
		inline URI() throw(std::bad_alloc);

		inline URI(const URI&) throw();
		
		explicit inline URI(const Binary&) throw();
		explicit inline operator Binary() const throw();
		
		explicit inline URI(const String&) throw();
		explicit inline operator String() const throw();

		explicit URI(const IRI&) throw();
		explicit operator IRI() const throw();

#ifdef QT4
		explicit inline URI(const QByteArray&) throw();
		explicit inline operator QByteArray() const throw();

		inline URI(const QUrl&) throw();
		inline operator QUrl() const throw();
#endif

		inline bool operator==(const URI& other) const throw() { return v == other.v; }
		inline bool operator!=(const URI& other) const throw() { return v != other.v; }
	};

	typedef URI uri;

	template<> struct isX<URI> : public std::true_type {};
	template<> struct isStorable<URI> : public std::false_type {};
	template<> struct isTemporary<URI> : public std::true_type {};
}

namespace X
{
	inline URI::URI() throw(std::bad_alloc)
	{}

	inline URI::URI(const URI& other) throw()
		: v(other.v)
	{}

	inline URI::URI(const Binary& val) throw()
		: v(val)
	{}

	inline URI::operator Binary() const throw()
	{
		return v;
	}

	inline URI::URI(const String& val) throw()
		: v(val)
	{}

	inline URI::operator String() const throw()
	{
		return v;
	}

#ifdef QT4
	inline URI::URI(const QByteArray& val) throw()
		: v(val)
	{}

	inline URI::operator QByteArray() const throw()
	{
		return v;
	}

	inline URI::URI(const QUrl& val) throw()
		: v(val.toEncoded())
	{}

	inline URI::operator QUrl() const throw()
	{
		return QUrl::fromEncoded(v);
	}
#endif
}

namespace std
{
	template<>
	struct hash<X::URI>
	{
		size_t operator()(const X::URI& v) const
		{
			return std::hash<X::Binary>()(X::Binary(v));
		}
	};
}

#endif
