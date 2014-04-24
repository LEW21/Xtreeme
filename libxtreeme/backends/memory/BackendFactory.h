#ifndef Xtreeme_Memory_BackendFactory_h
#define Xtreeme_Memory_BackendFactory_h

#include "memory.h"

#include <QObject>
#include "../../BackendFactory.h"

namespace Xtreeme
{
	namespace Memory
	{
		class MEMORY_EXPORT BackendFactory: public QObject, public Xtreeme::BackendFactory
		{
			Q_OBJECT
			Q_INTERFACES(Xtreeme::BackendFactory)
			Q_PLUGIN_METADATA(IID "org.xtreeme.BackendFactory") //  FILE "memory.json"

		public:
			bool supports(const QString& scheme);
			Backend* create(const QUrl& dsn, Xtreeme::Database* parent = 0);
		};
	}
}

#endif
