#include "Statement.h"

#include <libxtypes/AutoRegister.h>

namespace X
{
	template<> TypeID typeOf<Xtreeme::Statement>::type = newType();
	static AutoRegister<Xtreeme::Statement> reg_Statement(X_NS u"Statement");
}

namespace Xtreeme
{
	X_DEFINE_METATYPE(Xtreeme::Statement, Statement)

	QString Statement::asTurtle() const
	{ // TODO
		return subject.asTurtle() + ' ' + predicate.asTurtle() + ' ' + object.asTurtle() + ' ' + '.';
	}

	uint qHash(const Statement& s)
	{
		return (qHash(s.subject.value) >> 2) + (qHash(s.predicate.value) >> 2) + (qHash(s.object.value) >> 2) + (qHash(s.context.value) >> 2);
	}
}

namespace std
{
	template<>
	struct hash<Xtreeme::Statement>
	{
		size_t operator()(const Xtreeme::Statement& s) const
		{
			return qHash(s);
		}
	};
}
