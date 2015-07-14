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
	String::String(std::u16string _p) throw()
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

	std::string String::utf8() const throw()
	{
		QByteArray utf8 = QString(*this).toUtf8();
		return {utf8.constData(), size_t(utf8.size())};
	}

	String String::fromUtf8(const std::string& utf8)
	{
		QString s = QString::fromStdString(utf8);
		std::u16string p{(const char16_t*) s.unicode(), size_t(s.size())};
		return String(p);
	}

	std::u16string String::utf16() const throw()
	{
		return p;
	}
	
	String String::fromUtf16(const std::u16string& utf16)
	{
		return String(utf16);
	}

	std::u32string String::utf32() const throw()
	{
		QVector<uint> utf32 = QString(*this).toUcs4();
		return {(const char32_t*) utf32.constData(), size_t(utf32.size())};
	}

	String String::fromUtf32(const std::u32string& utf32)
	{
		QString s = QString::fromUcs4((const uint*) utf32.data());
		std::u16string p{(const char16_t*) s.unicode(), size_t(s.size())};
		return String(p);
	}
}
