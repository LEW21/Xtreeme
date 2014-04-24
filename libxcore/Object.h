#include "Signal.h"

#ifndef X_Object_h
#define X_Object_h

#include <thread>
#include <cassert>

namespace X
{
	struct Object: public Shared
	{
		inline Object(Object* parent = 0);
		inline ~Object();

		std::thread::id thread;
		Signal<> destroyed;
	};

	inline Object::Object(Object* parent)
		: thread(std::this_thread::get_id())
	{
		if (parent)
			parent->destroyed.connect([=]() {delete this;});
	}

	inline Object::~Object()
	{
		assert(std::this_thread::get_id() == thread);
		destroyed();
	}
}

#endif
