#ifndef Xtreeme_DataStream_h
#define Xtreeme_DataStream_h

#include "libxtreeme.h"

#include <libxcore/Object.h>

#include <libxcore/Signal.h>
#include "Header.h"
#include "Row.h"

namespace Xtreeme
{
	struct DataStreamInfo
	{
		X::Signal<Header> header;
		X::Signal<Row> data;
		X::Signal<> end;
	};

	struct XTREEME_EXPORT DataStream: public X::Object, public DataStreamInfo {};
}

#endif
