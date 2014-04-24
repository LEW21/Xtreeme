#include "EventLoop.h"

#include "EventQueue.h"
#if USE_GLIB
#include "glib/MainContextRef.h"
#include "glib/ScopedContextChange.h"
#endif

namespace X
{
	EventLoop::EventLoop(EventQueue* q)
		: _queue(q)
	{
		if (!_queue)
			_queue = new EventQueue(this);
	}

	void EventLoop::startAsThread()
	{
		std::thread* thread = new std::thread([=]() {
#if USE_GLIB
			ScopedContextChange c(MainContextRef::New);
#endif
			this->exec();
		});

		destroyed.connect([=]() {
			thread->join();
			delete thread;
		});
	}

	int EventLoop::exec()
	{
		ScopedPush<std::thread::id> push(thread, std::this_thread::get_id());

		EventQueue::ScopedPush queuePush(_queue);

		started();

		int exitCode;

		try
		{
			for(;;)
				_queue->dispatch(true);
		}
		catch (int eC)
		{
			exitCode = eC;
		}

		finished();

		return exitCode;
	}

	void EventLoop::quit(int exitCode)
	{
		_queue->push([=]() {throw exitCode;});
	}
}
