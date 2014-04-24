#ifndef X_ComplexType_h
#define X_ComplexType_h

#include <cstdlib>
#include "CoreType.h"

namespace X
{
	template <class T>
	struct ComplexType: public CoreType
	{
		inline void alloc(Word*) const;
		inline void free(Word*) const;

		void construct(Word*) const;
		void destruct(Word*) const;

		void construct(Word*, const Unit& nativeValue) const;
		void construct(Word*, Unit&& nativeValue) const;

		void construct(Word*, const Word& value) const;
		void construct(Word*, Word&& value) const;

		void set(Word*, const Unit& nativeValue) const;
		void set(Word*, Unit&& nativeValue) const;

		void set(Word*, const Word& value) const;
		void set(Word*, Word&& value) const;

		bool compare(const Word& a, const Word& b) const;

		size_t hash(const Word&) const;
	};

	template <class T>
	void ComplexType<T>::alloc(Word* that) const
	{
		if (sizeof(T) > sizeof(Word))
			*that = reinterpret_cast<Word>(::malloc(sizeof(T)));
	}

	template <class T>
	void ComplexType<T>::free(Word* that) const
	{
		if (sizeof(T) > sizeof(Word))
			::free(*that);
	}

	template <class T>
	void ComplexType<T>::construct(Word* that) const
	{
		alloc(that);
		new (&word_cast<T>(*that)) T();
	}

	template <class T>
	void ComplexType<T>::destruct(Word* that) const
	{
		word_cast<T>(*that).~T();
		free(that);
	}

	template <class T>
	void ComplexType<T>::construct(Word* that, const Unit& nativeValue) const
	{
		alloc(that);
		new (&word_cast<T>(*that)) T(nativeValue.cast<T>());
	}

	template <class T>
	void ComplexType<T>::construct(Word* that, Unit&& nativeValue) const
	{
		alloc(that);
		new (&word_cast<T>(*that)) T(std::move(nativeValue.cast<T>()));
	}

	template <class T>
	void ComplexType<T>::construct(Word* that, const Word& value) const
	{
		construct(that);
		word_cast<T>(*that) = word_cast<T>(value);
	}

	template <class T>
	void ComplexType<T>::construct(Word* that, Word&& value) const
	{
		construct(that);
		word_cast<T>(*that) = std::move(word_cast<T>(value));
	}

	template <class T>
	void ComplexType<T>::set(Word* that, const Unit& nativeValue) const
	{
		word_cast<T>(*that) = nativeValue.cast<T>();
	}

	template <class T>
	void ComplexType<T>::set(Word* that, Unit&& nativeValue) const
	{
		word_cast<T>(*that) = std::move(nativeValue.cast<T>());
	}

	template <class T>
	void ComplexType<T>::set(Word* that, const Word& value) const
	{
		word_cast<T>(*that) = word_cast<T>(value);
	}

	template <class T>
	void ComplexType<T>::set(Word* that, Word&& value) const
	{
		word_cast<T>(*that) = std::move(word_cast<T>(value));
	}

	template <class T>
	bool ComplexType<T>::compare(const Word& a, const Word& b) const
	{
		return word_cast<T>(a) == word_cast<T>(b);
	}

	template <class T>
	size_t ComplexType<T>::hash(const Word& that) const
	{
		std::hash<T> hashfunc;
		return hashfunc(word_cast<T>(that));
	}
}

#endif
