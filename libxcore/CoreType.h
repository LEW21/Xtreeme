#ifndef X_CoreType_h
#define X_CoreType_h

#include "Types.h"
#include "Type.h"

namespace X
{
	class CoreType;
	extern TypeRegistry<CoreType*> coreTypes;

	class Unit;
	typedef Unit* Word;

	struct CoreType
	{
		virtual void construct(Word*) const = 0;
		virtual void destruct(Word*) const = 0;

		virtual void construct(Word*, const Unit& nativeValue) const = 0;
		virtual void construct(Word*, Unit&& nativeValue) const = 0;

		virtual void construct(Word*, const Word& value) const = 0;
		virtual void construct(Word*, Word&& value) const = 0;

		virtual void set(Word*, const Unit& nativeValue) const = 0;
		virtual void set(Word*, Unit&& nativeValue) const = 0;

		virtual void set(Word*, const Word& value) const = 0;
		virtual void set(Word*, Word&& value) const = 0;

		virtual bool compare(const Word& a, const Word& b) const = 0;

		virtual size_t hash(const Word&) const = 0;
	};

	template <class T>
	inline const T& word_cast(const Word& that)
	{
		if (sizeof(T) <= sizeof(Word))
			return reinterpret_cast<const T&>(that);
		else
			return reinterpret_cast<const T&>(*that);
	}

	template <class T>
	inline T& word_cast(Word& that)
	{
		if (sizeof(T) <= sizeof(Word))
			return reinterpret_cast<T&>(that);
		else
			return reinterpret_cast<T&>(*that);
	}

	template <class T>
	inline T&& word_cast(Word&& that)
	{
		if (sizeof(T) <= sizeof(Word))
			return reinterpret_cast<T&&>(std::forward<Word>(that));
		else
			return reinterpret_cast<T&&>(*std::forward<Word>(that));
	}

	struct Unit
	{
		template <class T>
		T& cast()
		{
			return *reinterpret_cast<T*>(this);
		}

		template <class T>
		const T& cast() const
		{
			return *reinterpret_cast<const T*>(this);
		}

		template <class T>
		static Unit& create(T& value)
		{
			return *reinterpret_cast<Unit*>(&value);
		}

		template <class T>
		static const Unit& create(const T& value)
		{
			return *reinterpret_cast<const Unit*>(&value);
		}

		template <class T>
		static Unit&& create(T&& value)
		{
			return std::move(*reinterpret_cast<Unit*>(&value));
		}
	};
}

#endif
