#ifndef Xtreeme_SpecificParser_h
#define Xtreeme_SpecificParser_h

#include "Token.h"

#include "../Query.h"

namespace Xtreeme
{
	template <class T> class SpecificParser
	{
	public:
		virtual ~SpecificParser() {};
		virtual T parse(const Xtreeme::Token&, bool& ok, bool& end) = 0;
	};

	typedef SpecificParser<Query> SpecificQueryParser;
}

#endif
