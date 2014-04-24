#ifndef X_String_h
#define X_String_h

#include "X.h"

#include <libxcore/Array.h>

#ifdef QT4
#include <QString>
#endif

namespace X
{
	class String
	{
		UTF16String p;

		String(UTF16String) throw();

	public:
		inline String() throw(std::bad_alloc);

		inline String(const String& other) throw();

		inline String(const char16_t* constData) throw(std::bad_alloc);
		inline String(char16_t* data, bool own = false) throw(std::bad_alloc);

		inline String(const char16_t* constData, Size size) throw(std::bad_alloc);
		inline String(char16_t* data, Size size, bool own = false) throw(std::bad_alloc);

		inline static String copy(const char16_t* data, Size size = 0) throw(std::bad_alloc);

		inline String(bool) throw();
		operator bool() const throw(X::ConversionErrorBase);

#ifdef QT4
		inline String(const QString&) throw();
		inline operator QString() const throw();
#endif

		UTF8String utf8() const throw();
		UTF16String utf16() const throw();
		UTF32String utf32() const throw();

		static String fromUtf8(const UTF8String&);
		static String fromUtf16(const UTF16String&);
		static String fromUtf32(const UTF32String&);

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
		: p(0, 0, (const char16_t*) 0)
	{}

	inline String::String(const String& other) throw()
		: p(other.p)
	{}

	inline String::String(const char16_t* constData) throw(std::bad_alloc)
		: p(constData)
	{}

	inline String::String(char16_t* data, bool own) throw(std::bad_alloc)
		: p(data, own)
	{}

	inline String::String(const char16_t* constData, Size size) throw(std::bad_alloc)
		: p(size, size + 1, constData)
	{}

	inline String::String(char16_t* data, Size size, bool own) throw(std::bad_alloc)
		: p(size, size + 1, data, own)
	{}

	inline String String::copy(const char16_t* data, Size size) throw(std::bad_alloc)
	{
		if (!size)
			size = len(data);

		UTF16String p(size);
		p.copy(data, size);

		return p;
	}

	inline String::String(bool v) throw()
		: p(v ? 4 : 5, v ? 5 : 6, v ? u"true" : u"false")
	{}

#ifdef QT4
	inline String::String(const QString& value) throw()
		: p(value.size())
	{
		p.copy((const char16_t*) value.unicode(), value.size());
	}

	inline String::operator QString() const throw()
	{
		return QString::fromRawData((const QChar*) (const char16_t*) p, p.size());
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
			return std::hash<const char16_t*>()(v.utf16());
		}
	};
}

#endif
