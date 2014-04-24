#ifndef X_EventQueue_h
#define X_EventQueue_h

#include "Event.h"
#include <thread>
#include <cassert>
#include "ScopedPush.h"

#ifdef USE_GLIB
#include "glib/MainContextRef.h"
#include "glib/ScopedSource.h"
#include "glib/EventQueueSource.h"
#endif

#include "Object.h"

namespace X
{
	class EventQueueP;
	class EventQueue: public Object
	{
		EventQueueP* p;

	public:
#ifdef USE_GLIB
		MainContextRef context;
#endif

		EventQueue(Object* parent = 0);
		~EventQueue();

		void push(const Event& e);

		bool isEmpty();
		Event pop();

		void dispatch(bool wait);

		static EventQueue*& instance(std::thread::id thread = std::this_thread::get_id());
		static void forgetThread(std::thread::id thread = std::this_thread::get_id());

		inline static void push(const Event& event, std::thread::id thread);

		class ScopedPush: public X::ScopedPush<EventQueue*>
		{
		#ifdef USE_GLIB
			X::ScopedPush<MainContextRef> contextPush;
			ScopedSource source;
		#endif
			
		public:
			inline ScopedPush(EventQueue* queue)
				: X::ScopedPush<EventQueue*>(EventQueue::instance(), queue)
			#ifdef USE_GLIB
				, contextPush(queue->context, MainContextRef::Default)
				, source(EventQueueSource::create(queue))
			#endif
			{}
		}; 
	};

	inline void EventQueue::push(const Event& event, std::thread::id thread)
	{
		EventQueue* queue = instance(thread);
		assert(queue != 0);
		queue->push(event);
	}

	inline void postEvent(const std::function<void ()>& event, std::thread::id targetThread)
	{
		X::EventQueue::push(event, targetThread);
	}
}

#endif
