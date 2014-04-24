#ifndef X_EventLoop_h
#define X_EventLoop_h

#include "EventQueue.h"
#include "Signal.h"
#include "Object.h"
#include "Event.h"
#include <cassert>
#include <mutex>
#include <condition_variable>

namespace X
{
	class EventLoop: public Object
	{
		EventQueue* _queue;

	public:
		EventLoop(EventQueue* queue = 0);

		EventLoop(const EventLoop&) = delete;
		EventLoop(EventLoop&&) = delete;

		inline EventQueue* queue() const {return _queue;}

		void startAsThread();

		int exec();
		void quit(int exitCode = 0);

		Signal<> started;
		Signal<> finished;

		inline static void call(const Event& event, const Signal<>& finished, std::thread::id thread)
		{
			assert(thread != std::this_thread::get_id());

			std::mutex mutex;
			std::condition_variable cond;

			finished.connect([&]() {
				std::lock_guard<std::mutex> lock(mutex);
				cond.notify_all();
			}, X::DirectConnection);

			std::unique_lock<std::mutex> lock(mutex);
			postEvent(event, thread);
			cond.wait(lock);
		}
	};
}

#endif
