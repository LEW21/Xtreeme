#ifndef X_Shared_h
#define X_Shared_h

#include <atomic>

namespace X
{
	struct Shared
	{
		Shared();
		Shared(const Shared&);
		Shared(Shared&&);

		mutable std::atomic<int> refs;

		virtual ~Shared();
	};
}

#endif
