#include "StreamDispatcher.h"

#include "SignalDrivenStream.h"
#include "StreamDispatcher_Substream.h"
#include <QDataStream>
#include <QVector>

namespace Xtreeme
{
	struct StreamDispatcherP
	{
		QIODevice* device;
		QDataStream stream;

		QVector<SubStream*> substreams;

		inline StreamDispatcherP(QIODevice* d): device(d), stream(d) {}
	};

	StreamDispatcher::StreamDispatcher(QIODevice* device)
		: QObject(device)
		, p(new StreamDispatcherP(device))
	{
		connect(device, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
	}

	StreamDispatcher::~StreamDispatcher()
	{
		delete p;
	}

	void StreamDispatcher::onReadyRead()
	{
		while (p->device->bytesAvailable() > 8)
		{
			quint64 id;
			p->stream >> id;

			QByteArray message;
			p->stream >> message;

			if (id < quint64(p->substreams.size()) && p->substreams[id])
				p->substreams[id]->addData(message);
		}
	}

	void StreamDispatcher::write(qint64 subStream, const QByteArray& data)
	{
		p->stream << subStream << data;
	}

	QIODevice* StreamDispatcher::addSubstream()
	{
		return addSubstream(new SignalDrivenStream(this));
	}

	QIODevice* StreamDispatcher::addSubstream(SignalDrivenStream* stream)
	{
		quint64 id = p->substreams.size();
		SubStream* sub = new SubStream(this, id, stream);
		p->substreams << sub;
		return stream;
	}
}
