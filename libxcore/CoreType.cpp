#include "CoreType.h"

namespace X
{
	TypeRegistry<CoreType*> coreTypes;

	template<>
	std::vector<CoreType*>& TypeRegistry<CoreType*>::types()
	{
		static std::vector<CoreType*> types;
		return types;
	}
}
