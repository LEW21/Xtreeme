#ifndef Xtreeme_SelectParser_h
#define Xtreeme_SelectParser_h

#include "../SpecificParser.h"

#include "GGPParser.h"

namespace Xtreeme
{
	class Distinct;
	class Reduced;
	class Project;
	class Solve;

	class SelectParser: public SpecificQueryParser
	{
		Distinct* distinct;
		Reduced* reduced;
		Project* project;
		Solve* solve;

		enum State
		{
			ReadDistinctReduced,
			ReadProjection,
			ReadWhereWord,
			ReadGGP,
			ReadModifiers
		} state;

		GGPParser ggp;

		inline Distinct* readDistinct(const Xtreeme::Token&, bool& ok, bool& end);
		inline Reduced* readReduced(const Xtreeme::Token&, bool& ok, bool& end);
		inline Project* readProjection(const Xtreeme::Token&, bool& ok, bool& end);
		inline void readWhereWord(const Xtreeme::Token&, bool& ok, bool& end);
		inline QVector<StatementPattern> readGGP(const Xtreeme::Token&, bool& ok, bool& end);

		inline Query createPipeline();

	public:
		inline SelectParser()
			: distinct(0)
			, reduced(0)
			, project(0)
			, solve(0)
			, state(ReadDistinctReduced)
		{}

		Query parse(const Xtreeme::Token&, bool& ok, bool& end);
	};
}

#endif
