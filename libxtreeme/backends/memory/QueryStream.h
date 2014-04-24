#ifndef Xtreeme_Memory_QueryStream_h
#define Xtreeme_Memory_QueryStream_h

#include "memory.h"
#include <libxcore/Object.h>

#include "DataDispatcher.h"
#include "Data.h"

namespace Xtreeme
{
	class Query;
	class RemoteQuery;

	namespace Memory
	{
		class Database;

		class QueryStream: public X::Object
		{
			friend class Database;

			DataDispatcher dispatcher;
			RemoteQuery* remoteQuery;

			QueryStream(const Data::Pointer&, const Query&);
			~QueryStream();
		};
	}
}

#endif
