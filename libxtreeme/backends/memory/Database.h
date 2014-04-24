#ifndef Xtreeme_Memory_Database_h
#define Xtreeme_Memory_Database_h

#include <libxcore/Object.h>
#include "../../Backend.h"

#include "Data.h"

namespace Xtreeme
{
	namespace Memory
	{
		class Database: public X::Object, public Xtreeme::Backend
		{
			Data::Pointer data;

		public:
			RemoteQuery* query(const Query&);
		};
	}
}

#endif
