#ifndef Xtreeme_Memory_InputStream_h
#define Xtreeme_Memory_InputStream_h

#include "../Command.h"

namespace Xtreeme
{
	namespace Memory
	{
		class InputStream: public Command
		{
			DataStream* stream;

		public:
			InputStream();

			void bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings);

			DataStreamInfo* outputInfo(int id);
		};
	}
}

#endif
