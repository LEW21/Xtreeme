#ifndef X_ScopedSwap_h
#define X_ScopedSwap_h

namespace X
{
	template <class T>
	class ScopedSwap
	{
		T* a;
		T* b;

	public:
		inline ScopedSwap(T& first, T& second)
			: a(&first)
			, b(&second)
		{
			std::swap(*a, *b);
		}

		inline ~ScopedSwap()
		{
			std::swap(*a, *b);
		}

		ScopedPush(const ScopedPush&) = delete;
		operator=(const ScopedPush&) = delete;
	};
}

#endif
