#ifndef X_String_h
#define X_String_h

#include "X.h"

#include <string>

#ifdef QT4
#include <QString>
#endif

namespace X
{
	class String
	{
		std::u16string p;

		String(std::u16string) throw();

	public:
		inline String() throw(std::bad_alloc);

		inline String(const String&) = default;

		inline String(const char16_t* constData) throw(std::bad_alloc);
		inline String(char16_t* data, bool = false) throw(std::bad_alloc);

		inline String(const char16_t* constData, Size size) throw(std::bad_alloc);
		inline String(char16_t* data, Size size, bool = false) throw(std::bad_alloc);

		inline static String copy(const char16_t* data, Size size = 0) throw(std::bad_alloc);

		inline String(bool) throw();
		operator bool() const throw(X::ConversionErrorBase);

#ifdef QT4
		inline String(const QString&) throw();
		inline operator QString() const throw();
#endif

		std::string utf8() const throw();
		std::u16string utf16() const throw();
		std::u32string utf32() const throw();

		static String fromUtf8(const std::string&);
		static String fromUtf16(const std::u16string&);
		static String fromUtf32(const std::u32string&);

		inline bool operator==(const String& other) const throw() { return p == other.p; }
		inline bool operator!=(const String& other) const throw() { return p != other.p; }
	};

	typedef String string;

	template<> struct isX<String> : public std::true_type {};
	template<> struct isStorable<String> : public std::true_type {};
	template<> struct isTemporary<String> : public std::false_type {};

	template<> struct canConvert<bool, String> : public std::true_type {};
	template<> struct canConvert<String, bool> : public std::true_type {};
}

namespace X
{
	inline String::String() throw(std::bad_alloc)
		: p{}
	{}

	inline String::String(const char16_t* constData) throw(std::bad_alloc)
		: p(constData)
	{}

	inline String::String(char16_t* data, bool) throw(std::bad_alloc)
		: p(data)
	{}

	inline String::String(const char16_t* constData, Size size) throw(std::bad_alloc)
		: p(constData, size)
	{}

	inline String::String(char16_t* data, Size size, bool) throw(std::bad_alloc)
		: p(data, size)
	{}

	inline String String::copy(const char16_t* data, Size size) throw(std::bad_alloc)
	{
		return String(data, size);
	}

	inline String::String(bool v) throw()
		: p(v ? u"true" : u"false")
	{}

#ifdef QT4
	inline String::String(const QString& value) throw()
		: p((const char16_t*) value.unicode(), value.size())
	{
	}

	inline String::operator QString() const throw()
	{
		return QString::fromRawData((const QChar*) p.data(), p.size());
	}
#endif
}

namespace std
{
	template<>
	struct hash<X::String>
	{
		size_t operator()(const X::String& v) const
		{
			return std::hash<std::u16string>()(std::u16string{v.utf16(), v.utf16().size()});
		}
	};
}

#endif
