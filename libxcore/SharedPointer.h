#ifndef X_SharedPointer_h
#define X_SharedPointer_h

#include "Shared.h"
#include <utility>

namespace X
{
	template <class T> class SharedPointer
	{
	protected:
		T* p;

		inline Shared* data() { return reinterpret_cast<Shared*>(p); }
		inline const Shared* constData() const { return reinterpret_cast<const Shared*>(p); }

	public:
		inline SharedPointer(T* _p = 0)
			: p(_p)
		{
			if (p)
				constData()->refs++;
		}

		inline SharedPointer(const SharedPointer& other)
			: p(other.p)
		{
			if (p)
				constData()->refs++;
		}

		inline SharedPointer(SharedPointer&& other)
			: p(other.p)
		{
			if (p)
				constData()->refs++;

			other = 0;
		}

		inline ~SharedPointer()
		{
			if (p)
			{
				const Shared* d = constData();
				if (!--d->refs)
					delete d;
			}
		}

		inline SharedPointer<T>& operator=(T* newData)
		{
			if (newData)
				reinterpret_cast<const Shared*>(newData)->refs++;

			if (p)
			{
				const Shared* d = constData();
				if (!--d->refs)
					delete d;
			}

			p = newData;
			return *this;
		}

		inline SharedPointer<T>& operator=(const SharedPointer<T>& other)
		{
			return *this = other.p;
		}

		inline SharedPointer<T>& operator=(SharedPointer<T>&& other)
		{
			*this = other.p; other = 0; return *this;
		}

		inline bool isValid() const { return p; }
		inline bool isNull() const { return !p; }

		inline operator const T*() const { return p; }
		inline const T& operator*() const { return *p; }
		inline const T* operator->() const { return p; }
	};

	template <typename T>
	struct SharedAutoPointer: public SharedPointer<T>
	{
		template <typename... P>
		inline SharedAutoPointer(P... params)
			: SharedPointer<T>(new T(params...))
		{}

		inline SharedAutoPointer(T* val)
			: SharedPointer<T>(val)
		{}

		inline SharedAutoPointer(SharedAutoPointer<T>&& other)
			: SharedPointer<T>(std::forward<SharedAutoPointer>(other))
		{}

		inline SharedAutoPointer(const SharedAutoPointer<T>& other)
			: SharedPointer<T>(other)
		{}
	};
}

#endif
