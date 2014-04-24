#include "OutputStream.h"

#include "../../../DataStream.h"

namespace Xtreeme
{
	namespace Memory
	{
		OutputStream::OutputStream()
		{}

		void OutputStream::bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings)
		{
			auto c = static_cast<const Xtreeme::OutputStream*>(that);

			Xtreeme::DataStream* stream = c->stream;

			DataStreamInfo* output = resolveSignal(c->toClient, bindings);

			output->header.connect(stream->header);
			output->data.connect(stream->data);
			output->end.connect(stream->end);
		}
	}
}
