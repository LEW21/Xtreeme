#ifndef X_Method_h
#define X_Method_h

#include <functional>

namespace X
{
	template <typename A, typename R, typename... P>
	std::function<R (P...)> Method(A* object, R (A::*method)(P...))
	{
		return [object, method](P... p) {
			return (object->*method)(p...);
		};
	}
}

#endif
