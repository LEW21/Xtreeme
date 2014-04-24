#ifndef Xtreeme_BackendFactory_h
#define Xtreeme_BackendFactory_h

#include "libxtreeme.h"

#include <QString>
#include <QUrl>

namespace Xtreeme
{
	class Database;
	class Backend;

	class XTREEME_EXPORT BackendFactory
	{
		public:
			virtual bool supports(const QString& scheme) = 0;
			virtual Backend* create(const QUrl& dsn, Database* parent) = 0;
	};
}

Q_DECLARE_INTERFACE(Xtreeme::BackendFactory, "org.xtreeme.BackendFactory")

#endif
