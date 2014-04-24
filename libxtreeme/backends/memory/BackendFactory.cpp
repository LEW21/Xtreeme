#include "BackendFactory.h"

#include "Database.h"

#include <QtPlugin>

namespace Xtreeme
{
	namespace Memory
	{
		bool BackendFactory::supports(const QString& scheme)
		{
			return scheme == "memory";
		}

		Backend* BackendFactory::create(const QUrl&, Xtreeme::Database*)
		{
			return new Database();
		}
	}
}
