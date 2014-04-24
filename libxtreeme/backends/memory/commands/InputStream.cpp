#include "InputStream.h"

#include "../../../DataStream.h"

namespace Xtreeme
{
	namespace Memory
	{
		InputStream::InputStream()
		{}

		DataStreamInfo* InputStream::outputInfo(int id)
		{
			switch (id)
			{
				case 0:
					return stream;

				default:
					return 0;
			}
		}

		void InputStream::bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>*)
		{
			const Xtreeme::InputStream* c = static_cast<const Xtreeme::InputStream*>(that);

			stream = c->stream;
		}
	}
}
