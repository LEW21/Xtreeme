#ifndef X_SharedDataPointer_h
#define X_SharedDataPointer_h

#include "SharedPointer.h"
#include "SharedData.h"
#include <utility>

namespace X
{
	template <class T> class SharedDataPointer: public SharedPointer<T>
	{
		inline SharedData* data() { return reinterpret_cast<SharedData*>(this->p); }
		inline const SharedData* constData() const { return reinterpret_cast<const SharedData*>(this->p); }

	public:
		inline SharedDataPointer(T* p = 0): SharedPointer<T>(p) {}
		inline SharedDataPointer(const SharedDataPointer& other): SharedPointer<T>(other) {}
		inline SharedDataPointer(SharedDataPointer&& other): SharedPointer<T>(std::forward<SharedPointer<T>>(other)) {}

		inline SharedDataPointer<T>& operator=(T* data)
		{
			SharedPointer<T>::operator=(data);
			return *this;
		}

		inline SharedDataPointer<T>& operator=(const SharedDataPointer<T>& other)
		{
			SharedPointer<T>::operator=(other);
			return *this;
		}

		inline SharedDataPointer<T>& operator=(SharedDataPointer<T>&& other)
		{
			SharedPointer<T>::operator=(std::move(other));
			return *this;
		}

		inline void detach()
		{
			if (data()->refs != 1)
				*this = reinterpret_cast<T*>(data()->copy());
		}

		inline T* editable()
		{
			detach();
			return this->p;
		}
	};
}

#endif
