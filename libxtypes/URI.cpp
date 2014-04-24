#ifndef QT4
#define QT4
#endif

#include "URI.h"

#include <QUrl>

namespace X
{
	URI::URI(const IRI& value) throw()
		: v(QUrl(value).toEncoded())
	{}

	URI::operator IRI() const throw()
	{
		return IRI(QUrl::fromEncoded(v).toString());
	}
}
