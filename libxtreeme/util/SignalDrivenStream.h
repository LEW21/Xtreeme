#ifndef Xtreeme_SignalDrivenStream_h
#define Xtreeme_SignalDrivenStream_h

#include <QIODevice>

namespace Xtreeme
{
	class SignalDrivenStreamP;
	class SignalDrivenStream: public QIODevice
	{
		Q_OBJECT

		SignalDrivenStreamP* p;

	public:
		SignalDrivenStream(QObject* parent = 0);
		~SignalDrivenStream();

		bool isSequential() const;

		qint64 bytesAvailable() const;

	public slots:
		void available(const QByteArray& data);

	signals:
		void written(const QByteArray& data);

	protected:
		qint64 readData(char* data, qint64 maxSize);
		qint64 writeData(const char* data, qint64 maxSize);
	};
}

#endif
