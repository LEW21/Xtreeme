#pragma once

#include "../../Statement.h"
#include <vector>

namespace Xtreeme
{
	namespace Memory
	{
		class Data;

		struct InferredStatement
		{
			Statement s;
			std::vector<Statement> inferredFrom;

			InferredStatement(Statement s, std::vector<Statement> i): s(s), inferredFrom(i) {}
		};

		auto think(Data&, Statement newStatement) -> std::vector<InferredStatement>;
	}
}
