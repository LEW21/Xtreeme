#ifndef Xtreeme_TriG_h
#define Xtreeme_TriG_h

#include "../libxtreeme.h"

#include "Token.h"

#include <Generated.h>
#include <Iterable.h>

namespace Xtreeme
{
	Generated<StatementPattern> parseTriG(const Iterable<Token>& tokens);
}

#endif
