#ifndef X_Array_h
#define X_Array_h

#include <cstring>
#include "SharedDataPointer.h"
#include "Types.h"

namespace X
{
	template <class T> class ArrayP;
	template <class T> class Array
	{
		SharedDataPointer<ArrayP<T>> p;

	public:
		inline Array(Size size);

		inline Array(T* data, bool toDelete = true);
		inline Array(const T* data);

		inline Array(Size size, Size alloc, T* data, bool toDelete = true);
		inline Array(Size size, Size alloc, const T* data);

		inline Size size() const;
		inline Size capacity() const;

		inline const T* constData() const;
		inline T* data();

		inline operator const T*() const { return constData(); }

		inline void copy(const T* data, Size size);

		inline bool operator==(const Array<T>& other) const { return *p == *other.p; }
		inline bool operator!=(const Array<T>& other) const { return *p != *other.p; }
	};

	template<typename T> inline Size len(const T* s);

	typedef Array<Byte> BinaryString;
	typedef Array<UTF8Char> UTF8String;
	typedef Array<UTF16Char> UTF16String;
	typedef Array<UTF32Char> UTF32String;
}

#include <string> // for std::char_traits
#include "SharedData.h"

namespace X
{
	template <class T>
	struct MemArray
	{
		Size size;
		union {
			T* data;
			const T* constData;
		};
		U64 isMutable: 1;
		U64 toDelete: 1;
		T value[0];

		inline MemArray(Size s, T* d, bool toD)
			: size(s)
			, data(d)
			, isMutable(true)
			, toDelete(toD)
		{}

		inline MemArray(Size s, const T* d)
			: size(s)
			, constData(d)
			, isMutable(false)
			, toDelete(false)
		{}

		inline ~MemArray()
		{
			if (toDelete)
				delete data;
		}
	};

	template <class T>
	struct ArrayP: public SharedData
	{
		Size size;
		MemArray<T> data;

		inline ArrayP(Size s, Size a, T* d, bool toD)
			: size(s)
			, data(a, d, toD)
		{}

		inline ArrayP(Size s, Size a, const T* d)
			: size(s)
			, data(a, d)
		{}

		inline static ArrayP* create(Size alloc);
		inline void copy(const T* constData, Size s);

		inline ArrayP* copy() const;

		inline bool operator==(const ArrayP<T>& other) const;
		inline bool operator!=(const ArrayP<T>& other) const { return !(*this == other); }
	};

	template<typename T> inline std::size_t len(const T* s)
	{
		return std::char_traits<T>::length(s);
	}

	template <class T>
	inline Array<T>::Array(Size size)
		: p(ArrayP<T>::create(size + 1))
	{}

	template <class T>
	inline Array<T>::Array(T* data, bool toDelete)
	{
		Size size = len(data);
		p = new ArrayP<T>(size, size + 1, data, toDelete);
	}

	template <class T>
	inline Array<T>::Array(const T* data)
	{
		Size size = len(data);
		p = new ArrayP<T>(size, size + 1, data);
	}

	template <class T>
	inline Array<T>::Array(Size size, Size alloc, T* data, bool toDelete)
		: p(new ArrayP<T>(size, alloc, data, toDelete))
	{}

	template <class T>
	inline Array<T>::Array(Size size, Size alloc, const T* data)
		: p(new ArrayP<T>(size, alloc, data))
	{}

	template <class T>
	inline Size Array<T>::size() const
	{
		return p->size;
	}

	template <class T>
	inline Size Array<T>::capacity() const
	{
		return p->data.size;
	}

	template <class T>
	inline const T* Array<T>::constData() const
	{
		return p->data.constData;
	}
	
	template <class T>
	inline T* Array<T>::data()
	{
		return p->data.isMutable ? p->data.data : 0;
	}

	template <class T>
	inline void Array<T>::copy(const T* data, Size size)
	{
		if (!p->data.isMutable)
			p = ArrayP<T>::create(size + 1);

		ArrayP<T>* a = p.editable();
		a->copy(data, size);
	}

	template <class T>
	inline ArrayP<T>* ArrayP<T>::create(Size alloc)
	{
		ArrayP<T>* data = (ArrayP<T>*) malloc(sizeof(ArrayP<T>) + alloc * sizeof(T));
		if (!data)
			throw std::bad_alloc();
		new (data) ArrayP<T>(0, alloc, data->data.value, false);
		return data;
	}

	template <class T>
	inline void ArrayP<T>::copy(const T* constData, Size s)
	{
		size = s;
		memcpy(data.data, constData, size * sizeof(T));
		data.data[size] = '\0';
	}

	template <class T>
	ArrayP<T>* ArrayP<T>::copy() const
	{
		ArrayP<T>* copy = create(size + 1);
		copy->copy(data.constData, size);
		return copy;
	}

	template <class T>
	inline bool ArrayP<T>::operator==(const ArrayP<T>& other) const
	{
		if (size != other.size)
			return false;

		for (Size i = 0; i < size; ++i)
			if (data.constData[i] != other.data.constData[i])
				return false;

			return true;
	}
}

#endif
