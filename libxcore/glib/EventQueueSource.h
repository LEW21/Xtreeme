#ifndef X_EventQueueSource_h
#define X_EventQueueSource_h

#include <glib.h>

namespace X
{
	class EventQueue;

	struct EventQueueSource: public GSource
	{
		EventQueue* queue;

		static EventQueueSource* create(EventQueue*);

		EventQueueSource() = delete;
		~EventQueueSource() = delete;
	};
}

#endif
