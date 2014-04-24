#include "BackendFactory.h"

#include "Database.h"

#include <QtPlugin>

namespace Xtreeme
{
	namespace Remote
	{
		bool BackendFactory::supports(const QString& scheme)
		{
			return scheme == "local" || scheme == "tcp" || scheme == "ssl" || scheme == "udp";
		}

		Backend* BackendFactory::create(const QUrl& dsn, Xtreeme::Database* parent)
		{
			qDebug("Opening remote database.");
			return new Database(dsn, parent);
		}
	}
}

Q_EXPORT_PLUGIN2(xtreeme_remote, Xtreeme::Remote::BackendFactory)
