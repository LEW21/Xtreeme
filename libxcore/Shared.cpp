#include "Shared.h"

namespace X
{
	Shared::Shared()
		: refs(0)
	{}

	Shared::Shared(const Shared&)
		: refs(0)
	{}

	Shared::Shared(Shared&&)
		: refs(0)
	{}

	Shared::~Shared()
	{}
}
