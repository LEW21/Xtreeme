#ifndef Xtreeme_StatementPattern_h
#define Xtreeme_StatementPattern_h

#include "libxtreeme.h"

#include "Expression.h"
#include "Statement.h"
#include "expressions/Constant.h"
#include "RowPattern.h"
#include "Quad.h"

namespace Xtreeme
{
	struct XTREEME_EXPORT StatementPattern: public Quad<Expression>
	{
		using Quad::Quad;
		inline StatementPattern() {}

		inline bool isConstant() const
		{
			return subject.isConstant() && predicate.isConstant() && object.isConstant() && context.isConstant();
		}

		inline Statement constant() const
		{
			if (!isConstant())
				return Statement();

			return Statement(Constant(subject).resource(), Constant(predicate).resource(), Constant(object).resource(), Constant(context).resource());
		}

		inline operator RowPattern() const
		{
			return {X::Variant(), subject, predicate, object, context};
		}
	};
}

#include <QMetaType>
Q_DECLARE_METATYPE(Xtreeme::StatementPattern)

#endif
