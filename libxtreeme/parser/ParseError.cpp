#include "ParseError.h"

namespace Xtreeme
{
	ParseError::ParseError(Component _component, const QString& _message)
		: component(_component)
		, message(_message)
	{}
}
