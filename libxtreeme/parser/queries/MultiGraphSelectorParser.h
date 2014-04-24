#ifndef Xtreeme_MultiGraphSelectorParser_h
#define Xtreeme_MultiGraphSelectorParser_h

#include "../SpecificParser.h"

#include "../../queries/MultiGraphSelector.h"

namespace Xtreeme
{
	class MultiGraphSelectorParser: public SpecificParser<MultiGraphSelector>
	{
		bool isGraph;

	public:
		inline MultiGraphSelectorParser(): isGraph(false) {}
		MultiGraphSelector parse(const Xtreeme::Token&, bool& ok, bool& end);
	};
}

#endif
