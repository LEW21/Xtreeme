#include "Constant.h"

#include "ExpressionP.h"

namespace Xtreeme
{
	struct ConstantP: public ExpressionP
	{
		Resource resource;

		inline ConstantP(const Resource& _resource): ExpressionP(Expression::Constant), resource(_resource) {}

		SharedData* copy() const { return new ConstantP(resource); }
	};

	Constant::Constant(const Resource& resource)
		: Expression(new ConstantP(resource))
	{}

	Constant::Constant(const Expression& e)
		: Expression(e.isConstant() ? e : Expression())
	{}

	Resource Constant::resource() const
	{
		if (!isConstant())
			return Resource();

		X_P(const ConstantP)
		return p->resource;
	}

	void Constant::setResource(const Resource& resource)
	{
		if (!isConstant())
			return;

		X_EP(ConstantP)
		p->resource = resource;
	}
}
