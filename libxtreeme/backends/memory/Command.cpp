#include "Command.h"

namespace Xtreeme
{
	namespace Memory
	{
		DataStreamInfo* Command::outputInfo(int)
		{
			return 0;
		}
		
		void Command::registerDataAccess(DataDispatcher*)
		{}

		void Command::bind(const Xtreeme::Command*, QHash<const Xtreeme::Command*, Command*>*)
		{}
	}
}
