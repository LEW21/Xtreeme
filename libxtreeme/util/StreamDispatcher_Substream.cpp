#include "StreamDispatcher_Substream.h"

#include "StreamDispatcher.h"
#include "SignalDrivenStream.h"

namespace Xtreeme
{
	SubStream::SubStream(StreamDispatcher* d, quint64 i, SignalDrivenStream* stream)
		: QObject(d)
		, dispatcher(d)
		, id(i)
	{
		connect(this, SIGNAL(available(QByteArray)), stream, SLOT(available(QByteArray)));
		connect(stream, SIGNAL(written(QByteArray)), this, SLOT(written(QByteArray)));
	}

	void SubStream::addData(const QByteArray& data)
	{
		emit available(data);
	}

	void SubStream::written(const QByteArray& data)
	{
		dispatcher->write(id, data);
	}
}
