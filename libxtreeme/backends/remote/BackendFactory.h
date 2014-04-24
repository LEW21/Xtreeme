#ifndef Xtreeme_Remote_BackendFactory_h
#define Xtreeme_Remote_BackendFactory_h

#include "remote.h"

#include <QObject>
#include "../../BackendFactory.h"

namespace Xtreeme
{
	namespace Remote
	{
		class REMOTE_EXPORT BackendFactory: public QObject, public Xtreeme::BackendFactory
		{
			Q_OBJECT
			Q_INTERFACES(Xtreeme::BackendFactory)

		public:
			bool supports(const QString& scheme);
			Backend* create(const QUrl& dsn, Xtreeme::Database* parent = 0);
		};
	}
}

#endif
