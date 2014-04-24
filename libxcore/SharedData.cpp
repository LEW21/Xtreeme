#include "SharedData.h"

namespace X
{
	SharedData::SharedData()
	{}

	SharedData::SharedData(const SharedData& other)
		: Shared(other)
	{}

	SharedData::SharedData(SharedData&& other)
		: Shared(other)
	{}
}
