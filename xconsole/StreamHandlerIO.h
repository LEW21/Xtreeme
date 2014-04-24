#ifndef StreamHandlerIO_h
#define StreamHandlerIO_h

#include "StreamHandler.h"

class StreamHandlerIO: public StreamHandler
{
public:
	void handle(const X::SharedPointer<const Xtreeme::DataStream>&);
};

#endif
