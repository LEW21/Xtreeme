#ifndef Xtreeme_Variable_h
#define Xtreeme_Variable_h

#include "../Expression.h"

#include <QString>

namespace Xtreeme
{
	class XTREEME_EXPORT Variable: public Expression
	{
	public:
		inline Variable(): Expression() {}

		Variable(const QString& name);
		Variable(const Expression&);

		QString name() const;
		void setName(const QString&);
	};
}

#endif
