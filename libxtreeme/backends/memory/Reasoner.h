#ifndef Database_Reasoner_h
#define Database_Reasoner_h

#include "Statements.h"

namespace Xtreeme
{
	namespace Memory
	{
		class Resource;
		class Graph;
		class Statement;

		class Reasoner
		{
			Resource::ID instanceOf;
			Resource::ID sameAs;
			Resource::ID inverseOf;
			Resource::ID equivalentProperty;
			Resource::ID subPropertyOf;
			Resource::ID equivalentClass;
			Resource::ID subClassOf;
			Resource::ID TransitiveProperty;
			Resource::ID SymmetricProperty;

		public:
			Reasoner(Data::Pointer);
			Statements resolve(Data::Pointer, Statement*);
		};
	}
}

#endif
