#ifndef Xtreeme_StreamDispatcher_Substream_h
#define Xtreeme_StreamDispatcher_Substream_h

#include <QObject>

// Private part of StreamDispatcher.

namespace Xtreeme
{
	class StreamDispatcher;
	class SignalDrivenStream;

	class SubStreamP;
	class SubStream: public QObject
	{
		Q_OBJECT

		StreamDispatcher* dispatcher;
		quint64 id;

		friend class StreamDispatcher;

		SubStream(StreamDispatcher*, quint64 id, SignalDrivenStream* stream);

		void addData(const QByteArray& data);

	signals:
		void available(const QByteArray& data);

	private slots:
		void written(const QByteArray& data);
	};
}

#endif
