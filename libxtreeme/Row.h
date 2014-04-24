#ifndef Xtreeme_Row_h
#define Xtreeme_Row_h

#include "libxtreeme.h"

#include <QVector>
#include "Resource.h"

namespace Xtreeme
{
	class Row: public QVector<Resource>
	{
	public:
		inline Row() {}
		inline Row(const std::initializer_list<Resource>& row)
		{
			for (auto it = row.begin(); it < row.end(); ++it)
				(*this) << *it;
		}

		inline bool matches(const Row& pattern) const;
	};
}

namespace Xtreeme
{
	inline bool Row::matches(const Row& pattern) const
	{
		if (size() != pattern.size())
			return false;

		for (int i = 0; i < size(); ++i)
			if (pattern[i] != Resource() && pattern[i] != (*this)[i])
				return false;

		return true;
	}
}

#endif
