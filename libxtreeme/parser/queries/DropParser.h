#ifndef Xtreeme_DropParser_h
#define Xtreeme_DropParser_h

#include "../SpecificParser.h"

#include "MultiGraphSelectorParser.h"
#include "../../queries/Drop.h"

namespace Xtreeme
{
	class DropParser: public SpecificQueryParser
	{
		Drop* query;
		enum State
		{
			ReadSilent,
			ReadSelector
		} state;

		MultiGraphSelectorParser selector;

		inline bool readSilent(const Xtreeme::Token&, bool& ok, bool& end);
		inline MultiGraphSelector readGraphSelector(const Xtreeme::Token&, bool& ok, bool& end);

	public:
		inline DropParser(): query(new Drop()), state(ReadSilent) {}

		Query* parse(const Xtreeme::Token&, bool& ok, bool& end);
	}; 
}

#endif
