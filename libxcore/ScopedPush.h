#ifndef X_ScopedPush_h
#define X_ScopedPush_h

namespace X
{
	template <class T>
	class ScopedPush
	{
		T* a;
		T b;

	public:
		inline ScopedPush(T& first, const T& second)
			: a(&first)
			, b(second)
		{
			std::swap(*a, b);
		}

		inline ScopedPush(T& first, T&& second)
			: a(&first)
			, b(std::move(second))
		{
			std::swap(*a, b);
		}

		inline ~ScopedPush()
		{
			std::swap(*a, b);
		}

		ScopedPush(const ScopedPush&) = delete;
		ScopedPush& operator=(const ScopedPush&) = delete;
	};
}

#endif
