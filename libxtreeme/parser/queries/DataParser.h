#ifndef Xtreeme_DataParser_h
#define Xtreeme_DataParser_h

#include "../SpecificParser.h"

#include "../TurtleParser.h"

namespace Xtreeme
{
	class DataStream;

	class DataParser: public SpecificQueryParser
	{
		bool started;
		uint level;
		TurtleParser turtle;

	public:
		DataParser();

		DataStream* stream;

		Query parse(const Xtreeme::Token&, bool& ok, bool& end);
	};
}

#endif
