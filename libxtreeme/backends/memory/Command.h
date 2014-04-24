#ifndef Xtreeme_Memory_Command_h
#define Xtreeme_Memory_Command_h

#include "memory.h"
#include <libxcore/Object.h>

#include <QHash>
#include "../../Command.h"

namespace Xtreeme
{
	class DataStreamInfo;

	namespace Memory
	{
		class DataDispatcher;

		struct Command: public X::Object
		{
			virtual DataStreamInfo* outputInfo(int id);

			virtual void registerDataAccess(DataDispatcher*);
			virtual void bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings);
		};

		inline DataStreamInfo* resolveSignal(const Xtreeme::Stream& signal, QHash<const Xtreeme::Command*, Command*>* bindings)
		{
			return (*bindings)[signal.creator]->outputInfo(signal.id);
		}
	}
}

#endif
