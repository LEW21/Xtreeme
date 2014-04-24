#ifndef Xtreeme_Token_h
#define Xtreeme_Token_h

#include "../libxtreeme.h"

#include <QString>

#include "../Expression.h"

namespace Xtreeme
{
	struct Token
	{
		enum ResourceType
		{
			None            = 0x0000,
			IRI             = 0x0001,
			QName           = 0x0002,
			Variable        = 0x0004,
			Literal         = 0x0008,
			String          = 0x0010 | Literal,
			Boolean         = 0x0020 | Literal,
			Number          = 0x0040 | Literal,
			UnsignedNumber  = 0x0100 | Number,
			SignedNumber    = 0x0200 | Number,
			Integer         = 0x1000 | Number,
			Decimal         = 0x2000 | Number,
			Float           = 0x4000 | Number,
			UnsignedInteger = UnsignedNumber | Integer,
			SignedInteger   = SignedNumber | Integer,
			UnsignedDecimal = UnsignedNumber | Decimal,
			SignedDecimal   = SignedNumber | Decimal,
			UnsignedFloat   = UnsignedNumber | Float,
			SignedFloat     = SignedNumber | Float,
		} type;

		QString code;

		Expression expr;

		inline Token(): type(None) {}
		inline Token(ResourceType t, const QString& c): type(t), code(c) {}
	};
}

inline bool operator==(const QString& a, const char16_t* b)
{
	return a == QString::fromUtf16((const ushort*) b);
}

#include <QMetaType>
Q_DECLARE_METATYPE(Xtreeme::Token)

#endif
