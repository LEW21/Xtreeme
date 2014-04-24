#include "Database.h"

#include <QTcpSocket>
#include <QSslSocket>
#include <QUdpSocket>
#include <QLocalSocket>

#include "QueryStream.h"
#include "../../util/StreamDispatcher.h"

#include <QDebug>

namespace Xtreeme
{
	namespace Remote
	{
		QIODevice* open(const QUrl& dsn, QObject* parent)
		{
			QString scheme = dsn.scheme();

			if (scheme == "tcp" || scheme == "ssl" || scheme == "udp")
			{
				QAbstractSocket* socket;

				if (scheme == "tcp")
					socket = new QTcpSocket(parent);
				else if (scheme == "ssl")
					socket = new QSslSocket(parent);
				else
					socket = new QUdpSocket(parent);

				socket->connectToHost(dsn.host(), (dsn.port() == -1) ? 6216 : dsn.port());

				if (!socket->waitForConnected(3000))
				{
					qDebug("Cannot connect to the server.");
					delete socket;
					return 0;
				}

				return socket;
			}
			else if (scheme == "local")
			{
				QLocalSocket* socket = new QLocalSocket(parent);
				socket->connectToServer(dsn.path());

				if (!socket->waitForConnected(3000))
				{
					qDebug("Cannot connect to the server.");
					delete socket;
					return 0;
				}

				return socket;
			}

			qDebug("Incorrect DSN.");
			return 0;
		}

		Database::Database(const QUrl& dsn, Xtreeme::Database* db)
			: Xtreeme::Backend(db)
			, remote(new StreamDispatcher(open(dsn, this)))
		{}

		Database::~Database()
		{}

		void Database::connectStream(Xtreeme::QueryStream* stream)
		{
			QIODevice* device = remote->addSubstream();
			new QueryStream(device, stream);
		}
	}
}
