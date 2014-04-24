#ifndef Xtreeme_Expression_h
#define Xtreeme_Expression_h

#include "libxtreeme.h"

#include "util/SharedDataPointer.h"

#include <libxtypes/Variant.h>

namespace X
{
	class Variant;
}

namespace Xtreeme
{
	class Resource;

	class ExpressionP;
	class XTREEME_EXPORT Expression
	{
		protected:
			SharedDataPointer<ExpressionP> p;
			Expression(ExpressionP* p);

		public:
			enum Type
			{
				Invalid,
				Constant,
				Variable
			};

			Expression();
			~Expression();

			Expression(const Resource&);
			Expression(const X::Variant&);

			inline Expression& operator=(const Resource& res)
			{
				*this = Expression(res);
				return *this;
			}

			inline Expression& operator=(const X::Variant& v)
			{
				*this = Expression(v);
				return *this;
			}

			Type type() const;

			inline bool isValid() const { return type() != Invalid; }
			inline bool isConstant() const { return type() == Constant; }
			inline bool isVariable() const { return type() == Variable; }

			operator QString() const;
	};
}

#include <QMetaType>
Q_DECLARE_METATYPE(Xtreeme::Expression)

#endif
