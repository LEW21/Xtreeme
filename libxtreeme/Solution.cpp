#include "Solution.h"

#include "util/SharedData.h"

namespace Xtreeme
{
	struct SolutionP: public SharedData
	{
		Header header;
		QVector<Row> rows;

		inline SolutionP(const Header& h): header(h) {}
		inline SolutionP(const SolutionP* other)
			: header(other->header)
			, rows(other->rows)
		{}
		SharedData* copy() const { return new SolutionP(this); }
	};

	Solution::Solution(const Header& header)
		: p(new SolutionP(header))
		{}

	Solution::Solution()
	{}

	Solution::~Solution()
	{}

	Header Solution::header() const
	{
		return p->header;
	}

	QVector<Row> Solution::rows() const
	{
		return p->rows;
	}

	void Solution::addRow(const Row& row)
	{
		X_EP(SolutionP)
		p->rows << row;
	}

	void Solution::clear()
	{
		X_EP(SolutionP)
		p->rows.clear();
	}

	Solution Solution::join(QVector<Solution> subsolutions)
	{
		if (subsolutions.isEmpty())
			return Solution();

		/* Query Planner
		QMultiHash<QString, Solution> vars;

		foreach (const Solution& sol, unordered)
		{
			foreach (const QString& var, sol.vars())
			{
				vars.insert(var, sol);
			}
		}

		QVector<Solution> ordered;

		foreach (const Solution& sol, unordered)
		{
			if (ordered.contains(sol))
				continue;

			QVector<Solution> related;

			foreach (const QString& var, sol.vars())
			{
				foreach (const Solution& s, vars.values(var))
				{
					if (s != sol && !related.contains(s))
						related += s;
				}
			}


		}
		*/

		Solution solution = subsolutions[0];

		for (int i = 1; i < subsolutions.size(); ++i)
		{
			Solution s1 = solution;
			Solution s2 = subsolutions[i];

			QVector<int> repeated;
			QMap<int, int> toSolution;
			QMap<int, int> toS2;

			Header header;
			int j = 0;
			foreach (const QString& var, s2.header())
			{
				int index = s1.header().indexOf(var);

				if (index < 0)
				{
					index = header.size();
					header << var;
				}
				else
					repeated << index;

				toSolution[j] = index;
				toS2[index] = j;
				++j;
			}

			solution = Solution(header);

			foreach (const Row& r1, s1.rows())
			{
				foreach (const Row& r2, s2.rows())
				{
					foreach (int column, repeated)
					{
						if (r1[column] != r2[toS2[column]])
							goto DropRow;
					}

					{
						Row row = r1;

						QMapIterator<int, int> it(toSolution);
						while (it.hasNext())
						{
							it.next();
							if (!repeated.contains(it.key()))
								row[it.value()] = r2[it.key()];
						}

						solution.addRow(row);

						continue;
					}

					DropRow:
					break;
				}
			}
		}

		return solution;
	}
}
