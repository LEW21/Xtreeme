#include "SignalDrivenStream.h"

namespace Xtreeme
{
	struct SignalDrivenStreamP
	{
		QByteArray available;
	};

	SignalDrivenStream::SignalDrivenStream(QObject* parent)
		: QIODevice(parent)
		, p(new SignalDrivenStreamP())
	{
		open(QIODevice::ReadWrite);
	}

	SignalDrivenStream::~SignalDrivenStream()
	{
		delete p;
	}

	bool SignalDrivenStream::isSequential() const
	{
		return true;
	}

	void SignalDrivenStream::available(const QByteArray& data)
	{
		p->available += data;
	}

	qint64 SignalDrivenStream::bytesAvailable() const
	{
		return p->available.size() + QIODevice::bytesAvailable();
	}

	qint64 SignalDrivenStream::readData(char* data, qint64 maxSize)
	{
		qint64 size = qMin(qint64(p->available.size()), maxSize);
		memcpy(data, p->available.left(size), size);
		p->available = p->available.mid(size);
		return size;
	}

	qint64 SignalDrivenStream::writeData(const char* data, qint64 maxSize)
	{
		qint64 size = maxSize;
		emit written(QByteArray(data, size));
		return size;
	}
}
