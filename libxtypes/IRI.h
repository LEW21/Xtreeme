#ifndef X_IRI_h
#define X_IRI_h

#include "X.h"

#include "String.h"

#ifdef QT4
#include <QString>
#include <QUrl>
#endif

namespace X
{
	class IRI
	{
		String v;

	public:
		inline IRI() throw(std::bad_alloc);

		inline IRI(const IRI&) throw();

		explicit IRI(const String&) throw();
		explicit operator String() const throw();

#ifdef QT4
		explicit inline IRI(const QString&) throw();
		explicit inline operator QString() const throw();

		inline IRI(const QUrl&) throw();
		inline operator QUrl() const throw();
#endif

		inline bool operator==(const IRI& other) const throw() { return v == other.v; }
		inline bool operator!=(const IRI& other) const throw() { return v != other.v; }
	};

	typedef IRI iri;

	template<> struct isX<IRI> : public std::true_type {};
	template<> struct isStorable<IRI> : public std::true_type {};
	template<> struct isTemporary<IRI> : public std::false_type {};

	template<> struct canConvert<IRI, String> : public std::true_type {};
	template<> struct canConvert<String, IRI> : public std::true_type {};
}

namespace X
{
	inline IRI::IRI() throw(std::bad_alloc)
	{}

	inline IRI::IRI(const IRI& other) throw()
		: v(other.v)
	{}

	inline IRI::IRI(const String& value) throw()
		: v(value)
	{}

	inline IRI::operator String() const throw()
	{
		return v;
	}

#ifdef QT4
	inline IRI::IRI(const QString& value) throw()
		: v(value)
	{}

	inline IRI::operator QString() const throw()
	{
		return v;
	}

	inline IRI::IRI(const QUrl& value) throw()
		: v(value.toString())
	{}

	inline IRI::operator QUrl() const throw()
	{
		return QString(v);
	}
#endif
}

namespace std
{
	template<>
	struct hash<X::IRI>
	{
		size_t operator()(const X::IRI& v) const
		{
			return std::hash<X::String>()(X::String(v));
		}
	};
}

#endif
