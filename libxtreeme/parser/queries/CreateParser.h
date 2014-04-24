#ifndef Xtreeme_CreateParser_h
#define Xtreeme_CreateParser_h

#include "../SpecificParser.h"

#include "MultiGraphSelectorParser.h"
#include "../../queries/Create.h"

namespace Xtreeme
{
	class CreateParser: public SpecificQueryParser
	{
		Create* query;
		enum State
		{
			ReadSilent,
			ReadSelector
		} state;

		MultiGraphSelectorParser selector;

		inline bool readSilent(const Xtreeme::Token&, bool& ok, bool& end);
		inline MultiGraphSelector readGraphSelector(const Xtreeme::Token&, bool& ok, bool& end);

	public:
		inline CreateParser(): query(new Create()), state(ReadSilent) {}

		Query* parse(const Xtreeme::Token&, bool& ok, bool& end);
	}; 
}

#endif
