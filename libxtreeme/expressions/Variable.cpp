#include "Variable.h"

#include "ExpressionP.h"

namespace Xtreeme
{
	struct VariableP: public ExpressionP
	{
		QString name;

		inline VariableP(const QString& _name): ExpressionP(Expression::Variable), name(_name) {}

		SharedData* copy() const { return new VariableP(name); }
	};

	Variable::Variable(const QString& name)
		: Expression(new VariableP(name))
	{}

	Variable::Variable(const Expression& e)
		: Expression(e.isVariable() ? e : Expression())
	{}

	QString Variable::name() const
	{
		if (!isVariable())
			return QString();

		X_P(const VariableP)
		return p->name;
	}

	void Variable::setName(const QString& name)
	{
		if (!isVariable())
			return;

		X_EP(VariableP)
		p->name = name;
	}
}
