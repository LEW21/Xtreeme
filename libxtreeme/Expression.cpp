#include "Expression.h"

#include "expressions/ExpressionP.h"
#include "expressions/Constant.h"

namespace Xtreeme
{
	ExpressionP::ExpressionP(Expression::Type _type)
		: type(_type)
	{}

	Expression::Expression(ExpressionP* _p)
		: p(_p)
	{}

	Expression::Expression()
	{}

	Expression::Expression(const Resource& res)
		: p(Xtreeme::Constant(res).p)
	{}

	Expression::Expression(const X::Variant& res)
		: p(Xtreeme::Constant(Resource(res)).p)
	{}

	Expression::~Expression()
	{}

	Expression::Type Expression::type() const
	{
		return p.isNull() ? Invalid : p->type;
	}
}
