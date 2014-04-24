#ifndef Xtreeme_StreamDispatcher_h
#define Xtreeme_StreamDispatcher_h

#include <QObject>
class QIODevice;

namespace Xtreeme
{
	class SignalDrivenStream;

	class StreamDispatcherP;
	class StreamDispatcher: public QObject
	{
		Q_OBJECT

		StreamDispatcherP* p;

		friend class SubStream;
		void write(qint64 substream, const QByteArray& data);

	public:
		StreamDispatcher(QIODevice* device);
		~StreamDispatcher();

		QIODevice* addSubstream(SignalDrivenStream* stream);
		QIODevice* addSubstream();

	private slots:
		void onReadyRead();
	};
}

#endif
