#ifndef X_Text_h
#define X_Text_h

#include "X.h"

#include "String.h"

#ifdef QT4
#include <QString>
#endif

namespace X
{
	class Text
	{
		String v;
		String l;

	public:
		inline Text();

		inline Text(const Text&);

		explicit inline Text(const String&, const String& lang = String()) throw();
		explicit inline operator String() const throw();
		inline String content() const throw();
		inline String lang() const throw();

#ifdef QT4
		explicit inline Text(const QString& value, const QString& lang = QString());
		explicit inline operator QString() const;
		inline QString qlang() const;
#endif

		inline bool operator==(const Text& other) const throw()
		{ return v == other.v && l == other.l; }
		inline bool operator!=(const Text& other) const throw()
		{ return v != other.v || l != other.l; }
	};

	typedef Text text;

	template<> struct isX<Text> : public std::true_type {};
	template<> struct isStorable<Text> : public std::true_type {};
	template<> struct isTemporary<Text> : public std::false_type {};

	template<> struct canConvert<Text, String> : public std::true_type {};
	template<> struct canConvert<String, Text> : public std::true_type {};
}

namespace X
{
	inline Text::Text()
	{}

	inline Text::Text(const Text& other)
		: v(other.v)
		, l(other.l)
	{}

	inline Text::Text(const String& value, const String& lang) throw()
		: v(value)
		, l(lang)
	{}

	inline Text::operator String() const throw()
	{
		return v;
	}

	inline String Text::content() const throw()
	{
		return v;
	}

	inline String Text::lang() const throw()
	{
		return l;
	}

#ifdef QT4
	inline Text::Text(const QString& value, const QString& lang)
		: v(value)
		, l(lang)
	{}

	inline Text::operator QString() const
	{
		return v;
	}

	inline QString Text::qlang() const
	{
		return l;
	}
#endif
}

namespace std
{
	template<>
	struct hash<X::Text>
	{
		size_t operator()(const X::Text& v) const
		{
			return (std::hash<X::String>()(v.lang()) >> 1) + (std::hash<X::String>()(v.content()) >> 1);
		}
	};
}

#endif
