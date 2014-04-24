#ifndef Xtreeme_ClearParser_h
#define Xtreeme_ClearParser_h

#include "../SpecificParser.h"

#include "MultiGraphSelectorParser.h"
#include "../../queries/Clear.h"

namespace Xtreeme
{
	class ClearParser: public SpecificQueryParser
	{
		Clear* query;
		enum State
		{
			ReadSilent,
			ReadSelector
		} state;

		MultiGraphSelectorParser selector;

		inline bool readSilent(const Xtreeme::Token&, bool& ok, bool& end);
		inline MultiGraphSelector readGraphSelector(const Xtreeme::Token&, bool& ok, bool& end);

	public:
		inline ClearParser(): query(new Clear()), state(ReadSilent) {}

		Query* parse(const Xtreeme::Token&, bool& ok, bool& end);
	}; 
}

#endif
