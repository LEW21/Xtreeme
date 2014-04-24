#ifndef Xtreeme_GGPParser_h
#define Xtreeme_GGPParser_h

#include "../SpecificParser.h"

#include <QVector>
#include "../../StatementPattern.h"
#include "../TurtleParser.h"

namespace Xtreeme
{
	class GGPParser: public SpecificParser<QVector<StatementPattern>>
	{
		QVector<StatementPattern> data;
		bool started;
		uint level;
		TurtleParser turtle;

	public:
		GGPParser();

		QVector<StatementPattern> parse(const Xtreeme::Token&, bool& ok, bool& end);
	};
}

#endif
