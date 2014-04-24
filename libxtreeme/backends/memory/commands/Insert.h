#ifndef Xtreeme_Memory_Insert_h
#define Xtreeme_Memory_Insert_h

#include "../Command.h"

#include "../Data.h"

namespace Xtreeme
{
	namespace Memory
	{
		class Data;

		class Insert: public Command
		{
			DataDispatcher* dispatcher;
			Data::Pointer db;

		public:
			void registerDataAccess(DataDispatcher*);
			void bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings);
		};
	}
}

#endif
