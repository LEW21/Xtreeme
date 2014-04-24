#include "PlainType.h"

namespace X
{
	void PlainType::construct(Word* that) const
	{
		*that = 0;
	}

	void PlainType::destruct(Word*) const
	{}

	void PlainType::construct(Word* that, const Unit& nativeValue) const
	{
		*that = nativeValue.cast<Word>();
	}

	void PlainType::construct(Word* that, Unit&& nativeValue) const
	{
		std::swap(*that, nativeValue.cast<Word>());
	}

	void PlainType::construct(Word* that, const Word& value) const
	{
		*that = value;
	}

	void PlainType::construct(Word* that, Word&& value) const
	{
		std::swap(*that, value);
	}

	void PlainType::set(Word* that, const Unit& nativeValue) const
	{
		*that = nativeValue.cast<Word>();
	}

	void PlainType::set(Word* that, Unit&& nativeValue) const
	{
		std::swap(*that, nativeValue.cast<Word>());
	}

	void PlainType::set(Word* that, const Word& value) const
	{
		*that = value;
	}

	void PlainType::set(Word* that, Word&& value) const
	{
		std::swap(*that, value);
	}

	bool PlainType::compare(const Word& a, const Word& b) const
	{
		return a == b;
	}

	size_t PlainType::hash(const Word& that) const
	{
		std::hash<Word> hashfunc;
		return hashfunc(that);
	}
}
