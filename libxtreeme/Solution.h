#ifndef Xtreeme_Solution_h
#define Xtreeme_Solution_h

#include "libxtreeme.h"

#include "util/SharedDataPointer.h"
#include <QVector>
#include "Header.h"
#include "Row.h"

namespace Xtreeme
{
	class SolutionP;
	class XTREEME_EXPORT Solution
	{
		SharedDataPointer<SolutionP> p;

	public:
		Solution(const Header&);
		Solution();
		~Solution();

		Header header() const;

		QVector<Row> rows() const;
		void addRow(const Row&);
		void clear();

		static Solution join(QVector<Solution> subsolutions);
	};
}

#endif
