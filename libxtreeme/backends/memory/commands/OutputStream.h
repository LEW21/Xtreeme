#ifndef Xtreeme_Memory_OutputStream_h
#define Xtreeme_Memory_OutputStream_h

#include "../Command.h"

namespace Xtreeme
{
	namespace Memory
	{
		class OutputStream: public Command
		{
			DataStream* stream;

		public:
			OutputStream();

			void bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings);
		};
	}
}

#endif
