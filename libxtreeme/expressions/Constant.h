#ifndef Xtreeme_Constant_h
#define Xtreeme_Constant_h

#include "../Expression.h"

#include "../Resource.h"

namespace Xtreeme
{
	class XTREEME_EXPORT Constant: public Expression
	{
	public:
		Constant(const Resource&);
		Constant(const Expression&);

		Resource resource() const;
		void setResource(const Resource&);
	};
}

#endif
