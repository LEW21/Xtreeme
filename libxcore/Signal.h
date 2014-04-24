#ifndef X_Signal_h
#define X_Signal_h

#include <functional>
#include <thread>
#include <mutex>
#include <vector>
#include "Method.h"
#include "SharedDataPointer.h"

namespace X
{
	class Object;

	template <class T> struct Vector: public SharedData, public std::vector<T>
	{
		Vector<T>* copy() const
		{
			return new Vector<T>(*this);
		}

		inline void append(const T& val)
		{
			push_back(val);
		}
	};

	enum ConnectionType
	{
		AutoConnection,
		DirectConnection,
		QueuedConnection
	};

	template <typename... P> class Signal
	{
	public:
		inline Signal();

		typedef std::function<void (P...)> Slot;

		inline void connect(const Slot&, ConnectionType = AutoConnection) const;
		inline void connect(const Slot&, const Object*, ConnectionType = AutoConnection) const;
		inline void connect(const Slot&, const Object&, ConnectionType = AutoConnection) const;

		inline void disconnect(const Slot&) const;

		inline void operator()(const P&... params) const;

		inline operator std::function<void (P...)>();

	private:
		mutable SharedDataPointer<Vector<Slot>> connections;
		mutable std::mutex mutex;
	};

	template <typename... P> class SharedSignal: public Shared, public Signal<P...>
	{
	public:
		typedef SharedAutoPointer<SharedSignal<P...>> Pointer;
	};
}

#include "Object.h"
#include "EventQueue.h"

namespace X
{
	void postEvent(const std::function<void ()>& event, std::thread::id targetThread);

	template <typename... P>
	inline Signal<P...>::Signal()
		: connections(new Vector<Slot>())
	{}

	template <typename... P>
	inline void Signal<P...>::connect(const Slot& slot, ConnectionType type) const
	{
		Slot copy;
		if (type == AutoConnection)
		{
			std::thread::id creationThread = std::this_thread::get_id();

			copy = [=](P... params) {
				if (creationThread == std::this_thread::get_id())
					slot(params...);
				else
					postEvent(std::bind(slot, params...), creationThread);
			};
		}
		else if (type == DirectConnection)
		{
			copy = slot;
		}
		else if (type == QueuedConnection)
		{
			std::thread::id creationThread = std::this_thread::get_id();

			copy = [=](P... params) {
				postEvent(std::bind(slot, params...), creationThread);
			};
		}

		std::lock_guard<std::mutex> lock(mutex);
		connections.editable()->push_back(copy);
	}

	template <typename... P>
	inline void Signal<P...>::connect(const Slot& slot, const Object* object, ConnectionType type) const
	{
		Slot copy;
		if (type == AutoConnection)
		{
			copy = [=](P... params) {
				if (object->thread == std::this_thread::get_id())
					slot(params...);
				else
					postEvent(std::bind(slot, params...), object->thread);
			};
		}
		else if (type == DirectConnection)
		{
			copy = slot;
		}
		else if (type == QueuedConnection)
		{
			copy = [=](P... params) {
				postEvent(std::bind(slot, params...), object->thread);
			};
		}

		std::lock_guard<std::mutex> lock(mutex);
		connections.editable()->push_back(copy);
	}

	template <typename... P>
	inline void Signal<P...>::connect(const Slot& slot, const Object& object, ConnectionType type) const
	{
		connect(slot, &object, type);
	}

	template <typename... P>
	inline void Signal<P...>::operator()(const P&... params) const
	{
		SharedDataPointer<Vector<Slot>> c;

		{
			std::lock_guard<std::mutex> lock(mutex);
			c = connections;
		}

		for (Slot slot : *c)
			slot(params...);
	}

	template <typename... P>
	inline Signal<P...>::operator std::function<void (P...)>()
	{
		return [=](P... params) {
			(*this)(params...);
		};
	}
}

#endif
