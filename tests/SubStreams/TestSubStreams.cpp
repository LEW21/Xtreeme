#include <QtTest/QtTest>

#include <QLocalServer>
#include <QLocalSocket>

#include "../../libxtreeme/util/StreamDispatcher.h"
#include "../../libxtreeme/util/StreamDispatcher_Substream.h"
#include "../../libxtreeme/util/SignalDrivenStream.h"

class TestSubStreams: public QObject
{
	Q_OBJECT

	QLocalServer server;

	QLocalSocket* serverSideSocket;
	QLocalSocket* clientSideSocket;

	Xtreeme::StreamDispatcher* clientSide;
	Xtreeme::StreamDispatcher* serverSide;

private slots:
	void init();
	void cleanup();

	void test();
};

void TestSubStreams::init()
{
	QVERIFY(server.listen("TestSubStreams"));

	clientSideSocket = new QLocalSocket();
	clientSideSocket->connectToServer("TestSubStreams");

	QVERIFY(server.waitForNewConnection());
	QVERIFY(serverSideSocket = server.nextPendingConnection());

	QVERIFY(clientSideSocket->waitForConnected());

	clientSide = new Xtreeme::StreamDispatcher(clientSideSocket);
	serverSide = new Xtreeme::StreamDispatcher(serverSideSocket);
}

void TestSubStreams::cleanup()
{
	delete clientSide;
	delete serverSide;

	delete clientSideSocket;
	delete serverSideSocket;

	server.close();
}

void TestSubStreams::test()
{
	QIODevice* clientSub = clientSide->addSubstream();
	QIODevice* serverSub = serverSide->addSubstream();

	QTextStream client(clientSub);
	QTextStream server(serverSub);

	client << QString("Hey!");
	client.flush();

	clientSideSocket->waitForBytesWritten();

	QVERIFY(serverSideSocket->waitForReadyRead());

	QString msg;
	server >> msg;
	QCOMPARE(msg, QString("Hey!"));
}

QTEST_MAIN(TestSubStreams)
#include "TestSubStreams.moc"
