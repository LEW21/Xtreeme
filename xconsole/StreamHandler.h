#ifndef StreamHandler_h
#define StreamHandler_h

#include <libxcore/SharedPointer.h>

namespace Xtreeme
{
	class DataStream;
}

class StreamHandler
{
public:
	virtual void handle(const X::SharedPointer<const Xtreeme::DataStream>&) = 0;
};

#endif
