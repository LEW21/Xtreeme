#ifndef Xtreeme_Header_h
#define Xtreeme_Header_h

#include "libxtreeme.h"

#include <QVector>
#include <QString>

namespace Xtreeme
{
	class Header: public QVector<QString>
	{
	public:
		inline Header() {}
		inline Header(const std::initializer_list<QString>& header)
		{
			for (auto it = header.begin(); it < header.end(); ++it)
				(*this) << *it;
		}
	};
}

#include <QMetaType>
Q_DECLARE_METATYPE(Xtreeme::Header)

#endif
