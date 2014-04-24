#include "EventQueueSource.h"

#include "EventQueue.h"

namespace X
{
	static gboolean sourceCheck(GSource* s)
	{
		EventQueue* queue = static_cast<EventQueueSource*>(s)->queue;
		return !queue->isEmpty();
	}

	static gboolean sourcePrepare(GSource* s, gint *timeout)
	{
		*timeout = -1;
		return sourceCheck(s);
	}

	static gboolean sourceDispatch(GSource* s, GSourceFunc, gpointer)
	{
		EventQueue* queue = static_cast<EventQueueSource*>(s)->queue;

		while (!queue->isEmpty())
			(queue->pop())();

		return true;
	}

	static GSourceFuncs sourceFuncs = {
		sourcePrepare,
		sourceCheck,
		sourceDispatch,
		NULL,
		NULL,
		NULL
	};

	EventQueueSource* EventQueueSource::create(EventQueue* queue)
	{
		EventQueueSource* source = static_cast<EventQueueSource*>(g_source_new(&sourceFuncs, sizeof(EventQueueSource)));
		source->queue = queue;
		return source;
	}
}
