#ifndef X_PlainType_h
#define X_PlainType_h

#include "CoreType.h"

namespace X
{
	struct PlainType: public CoreType
	{
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
}

#endif
