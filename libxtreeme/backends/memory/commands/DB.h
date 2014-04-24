#ifndef Xtreeme_Memory_DB_h
#define Xtreeme_Memory_DB_h

#include "../Command.h"

#include "../../../DataStream.h"

namespace Xtreeme
{
	namespace Memory
	{
		class Database;

		class DB: public Command
		{
		public:
			DataStreamInfo data;
			DataStreamInfo* outputInfo(int id);

			void registerDataAccess(DataDispatcher*);
		};
	}
}

#endif
