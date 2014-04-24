#ifndef Xtreeme_RemoteQuery_h
#define Xtreeme_RemoteQuery_h

#include "libxtreeme.h"

#include <libxcore/Object.h>
#include <libxcore/Signal.h>

namespace Xtreeme
{
	struct XTREEME_EXPORT RemoteQuery: public X::Object
	{
		X::Signal<> start;
		X::Signal<> finish;
	};
}

#endif
