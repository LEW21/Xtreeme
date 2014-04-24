#include "Type.h"
#include "CoreType.h"

namespace X
{
	TypeID newType()
	{
		static std::atomic<TypeID> lastID(0);
		return ++lastID;
	}
/*
	std::atomic<int>& Type::lastID()
	{
		static std::atomic<int> lastID(0);
		return lastID;
	}*/
}
