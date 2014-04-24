#ifndef QT4
#define QT4
#endif

#include "String.h"

#include "MetaType.h"

// :<
#include <QString>
#include <QVector>

namespace X
{
	String::String(UTF16String _p) throw()
		: p(_p)
	{}

	String::operator bool() const throw(X::ConversionErrorBase)
	{
		if (*this == u"true")
			return true;
		else if (*this == u"false")
			return false;
		else if (*this == u"1")
			return true;
		else if (*this == u"0")
			return false;
		else
			throw ConversionError(typeOf<String>::type, typeOf<bool>::type);
	}

	UTF8String String::utf8() const throw()
	{
		QByteArray utf8 = QString(*this).toUtf8();
		UTF8String p(utf8.size());
		p.copy(utf8.constData(), utf8.size());
		return p;
	}

	String String::fromUtf8(const UTF8String& utf8)
	{
		QString s = QString::fromUtf8(utf8);
		UTF16String p(s.size());
		p.copy((const char16_t*) s.unicode(), s.size());
		return String(p);
	}

	UTF16String String::utf16() const throw()
	{
		return p;
	}
	
	String String::fromUtf16(const UTF16String& utf16)
	{
		return String(utf16);
	}

	UTF32String String::utf32() const throw()
	{
		QVector<uint> utf32 = QString(*this).toUcs4();
		UTF32String p(utf32.size());
		p.copy((const char32_t*) utf32.constData(), utf32.size());
		return p;
	}

	String String::fromUtf32(const UTF32String& utf32)
	{
		QString s = QString::fromUcs4((const uint*) (const char32_t*) utf32);
		UTF16String p(s.size());
		p.copy((const char16_t*) s.unicode(), s.size());
		return String(p);
	}
}
