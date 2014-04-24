#ifndef X_Type_h
#define X_Type_h

#include <atomic>
#include <vector>
#include "Types.h"

namespace X
{
	using TypeID = uint;

	TypeID newType();

	template <class T>
	struct typeOf
	{
		static TypeID type;
	};

	template <class T>
	class TypeRegistry
	{
	public:
		static std::vector<T>& types();

		T& operator[](TypeID type)
		{
			if (type >= types().size())
				types().resize(type + 1); // TODO check if it fills with 0 on pointers

			return types()[type];
		}
	};
}

#endif
