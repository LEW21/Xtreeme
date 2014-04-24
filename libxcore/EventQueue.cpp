#include "EventLoop.h"

#include <ATL/queue.h>
#include <map>

#ifndef USE_GLIB
#include <ATL/semaphore.h>
#endif

namespace X
{
	struct EventQueueP
	{
		ATL::Queue<Event> queue;
		std::thread::id thread;
#ifndef USE_GLIB
		ATL::Semaphore semaphore;
#endif
	};

	EventQueue::EventQueue(Object* parent)
		: Object(parent)
		, p(new EventQueueP())
	{}

	EventQueue::~EventQueue()
	{
		delete p;
	}

	void EventQueue::push(const Event& e)
	{
		p->queue.push(e);
#ifdef USE_GLIB
		g_main_context_wakeup(context);
#else
		p->semaphore.notify();
#endif
	}

	bool EventQueue::isEmpty()
	{
		return p->queue.isEmpty();
	}

	Event EventQueue::pop()
	{
		return p->queue.pop();
	}

	void EventQueue::dispatch(bool wait)
	{
#ifdef USE_GLIB
		g_main_context_iteration(context, wait);
#else
		if (wait)
			p->semaphore.wait();

		while (!isEmpty())
			(pop())();
#endif
	};

	static std::map<std::thread::id, EventQueue**> queues;
	static std::mutex queuesMutex;

	EventQueue*& EventQueue::instance(std::thread::id thread)
	{
		std::lock_guard<std::mutex> lock(queuesMutex);
		EventQueue**& ref = queues[thread];
		if (!ref)
			ref = new EventQueue*();
		return *ref;
	}

	void EventQueue::forgetThread(std::thread::id thread)
	{
		std::lock_guard<std::mutex> lock(queuesMutex);
		delete queues[thread];
		queues.erase(std::this_thread::get_id());
	}
}
