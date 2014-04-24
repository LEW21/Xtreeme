#include "Solve.h"

#include "../../../expressions/Constant.h"
#include "../../../Solution.h"

namespace Xtreeme
{
	namespace Memory
	{
		struct SubPattern
		{
			Xtreeme::RowPattern pattern;
			Xtreeme::Row simplePattern;
			Xtreeme::Solution solution;

			SubPattern(const Xtreeme::RowPattern& pattern);
			SubPattern() {}
		};

		static inline Header makeHeader(const Xtreeme::RowPattern& pattern)
		{
			Header header;
			
			foreach (const Expression& e, pattern)
				if (e.isVariable())
					header << Variable(e).name();

			return header;
		}

		SubPattern::SubPattern(const Xtreeme::RowPattern& p)
			: pattern(p)
			, solution(makeHeader(p))
		{
			foreach (const Expression& e, pattern)
				simplePattern << Constant(e).resource();
		}

		struct SolveP
		{
			QVector<SubPattern> subPatterns;
		};

		Solve::Solve()
			: p(new SolveP())
		{}

		DataStreamInfo* Solve::outputInfo(int id)
		{
			switch (id)
			{
				case 0:
					return &output;

				default:
					return 0;
			}
		}

		void Solve::bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings)
		{
			const Xtreeme::Solve* c = static_cast<const Xtreeme::Solve*>(that);

			DataStreamInfo* input = resolveSignal(c->input, bindings);

			input->header.connect([=](const Xtreeme::Header& header) {
				this->inputHeader(header);
			}, this);

			input->data.connect([=](const Xtreeme::Row& row) {
				this->input(row);
			}, this);

			input->end.connect([=]() {
				this->inputEnd();
			}, this);

			foreach (const RowPattern& single, c->pattern)
				p->subPatterns << SubPattern(single);
		}

		void Solve::inputHeader(const Xtreeme::Header& oldHeader)
		{
			Header header;

			foreach (const SubPattern& sub, p->subPatterns)
				foreach (const QString& column, sub.solution.header())
					if (!header.contains(column))
						header << column;

			output.header(header);
		}

		void Solve::input(const Xtreeme::Row& row)
		{
			foreach (const SubPattern& sub, p->subPatterns)
			{
				if (!row.matches(sub.simplePattern))
					continue;

				Row newRow;

				int i = 0;
				foreach (const Expression& e, sub.pattern)
				{
					if (e.isVariable())
						newRow << row[i];
					++i;
				}

				const_cast<Solution*>(&sub.solution)->addRow(newRow);
			}
		}

		void Solve::inputEnd()
		{
			QVector<Solution> subsolutions;
			foreach (const SubPattern& sub, p->subPatterns)
				subsolutions << sub.solution;

			foreach (const Row& r, Solution::join(subsolutions).rows())
			{
				output.data(r);
			}

			output.end();

			delete this;
		}
	}
}
