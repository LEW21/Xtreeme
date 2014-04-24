#ifndef X_Array_h
#define X_Array_h

#include "util/SharedData.h"

namespace X
{
	template<typename T> inline std::size_t len(const T* s);

	template <class T>
	class Array: public SharedData
	{
		quint64 _size;
		quint64 _alloc;
		union {
			T* _data;
			const T* _constData;
			quint64 p;
		};
		quint64 isOwner: 1;
		quint64 canModify: 1;
		T value[0];

	public:
		inline static Array* create(quint64 alloc);
		
		inline Array(T* d, bool iO = true);
		inline Array(const T* d);

		inline Array(quint64 s, quint64 a, T* d, bool iO = true);
		inline Array(quint64 s, quint64 a, const T* d);

		inline ~Array();

		inline void copy(const T* constData, quint64 s);

		inline Array* detach() const;

		inline quint64 size() const { return _size; }
		inline quint64 allocatedSize() const { return _alloc; }

		inline operator const T*() const { return _constData; }
		inline const T* constData() const { return _constData; }
		inline T* data() { return canModify ? _data : 0; }

		inline bool operator==(const Array<T>& other) const;

		inline operator const T*() const;
		inline operator T*();

		inline const T* constData() const;
		inline T* data();
	};
	
	typedef Array<char> BinaryString;
	typedef Array<char> UTF8String;
	typedef Array<char16_t> UTF16String;
	typedef Array<char32_t> UTF32String;
}

#include <string> // for std::char_traits

namespace X
{
	template<typename T> inline std::size_t len(const T* s)
	{
		return std::char_traits<T>::length(s);
	}
	
	template <class T>
	inline Array<T>* Array<T>::create(quint64 alloc)
	{
		Array<T>* data = (Array<T>*) malloc(sizeof(Array<T>) + alloc * sizeof(T));
		if (!data)
			throw std::bad_alloc();
		new (data) Array<T>(0, alloc, data->value);
		return data;
	}
	
	template <class T>
	inline Array<T>::Array(T* d, bool iO)
		: _size(len(d))
		, _alloc(_size + 1)
		, _data(d)
		, isOwner(iO)
		, canModify(true)
	{}
	
	template <class T>
	inline Array<T>::Array(const T* d)
		: _size(len(d))
		, _alloc(_size + 1)
		, _constData(d)
		, isOwner(false)
		, canModify(false)
	{}
	
	template <class T>
	inline Array<T>::Array(quint64 s, quint64 a, T* d, bool iO)
		: _size(s)
		, _alloc(a)
		, _data(d)
		, isOwner(iO)
		, canModify(true)
	{}
	
	template <class T>
	inline Array<T>::Array(quint64 s, quint64 a, const T* d)
		: _size(s)
		, _alloc(a)
		, _constData(d)
		, isOwner(false)
		, canModify(false)
	{}
	
	template <class T>
	inline Array<T>::~Array()
	{
		if (isOwner && _constData != value)
			delete _constData;
	}
	
	template <class T>
	inline void Array<T>::copy(const T* constData, quint64 s)
	{
		_size = s;
		memcpy(_data, constData, _size * sizeof(T));
		_data[_size] = '\0';
	}
	
	template <class T>
	Array<T>* Array<T>::detach() const
	{
		Array<T>* copy = create(_size + 1);
		copy->copy(_constData, _size);
		return copy;
	}
	
	template <class T>
	inline bool Array<T>::operator==(const Array<T>& other) const
	{
		if (size() != other.size())
			return false;
		
		for (quint64 i = 0; i < size(); ++i)
			if (constData()[i] != other.constData()[i])
				return false;
			
			return true;
	}
}

#endif
