#ifndef Xtreeme_QueryP_h
#define Xtreeme_QueryP_h

#include "../Expression.h"
#include "../util/SharedData.h"

namespace Xtreeme
{
	struct ExpressionP: public SharedData
	{
		ExpressionP(Expression::Type type);

		Expression::Type type;
	};
}

#endif
