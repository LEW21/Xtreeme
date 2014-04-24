#include <QApplication>

#include <libxcore/EventLoop.h>

#include <libxtreeme/Database.h>
#include <libxtreeme/DataStream.h>

#include "Console.h"
#include <iostream>

#include "StreamHandlerQt.h"
#include "StreamHandlerIO.h"

using namespace X;
using namespace Xtreeme;

int main(int argc, char** argv)
{
	QApplication qtApp(argc, argv);
	qtApp.setQuitOnLastWindowClosed(false);

	EventLoop* app = new EventLoop;
	Database* db = Database::open(QUrl("memory://"));

	std::vector<StreamHandler*> streamHandlers;
	streamHandlers.push_back(new StreamHandlerQt());
	streamHandlers.push_back(new StreamHandlerIO());

	std::function<void (const DataStream*)> streamHandler = [&](const X::SharedPointer<const DataStream>& stream) {
		for (StreamHandler* handler : streamHandlers)
			handler->handle(stream);
	};

	app->started.connect([=]() {
		EventLoop* reader = new EventLoop;
		Signal<QString>* newFragment = new Signal<QString>;

		reader->started.connect([=]() {
			char line[4097];
			while (!std::cin.eof())
			{
				std::cin.getline(line, 4096);
				int len = strlen(line);
				line[len] = '\n';
				line[len + 1] = '\0';
				(*newFragment)(QString::fromUtf8(line));
			}

			reader->quit();
		}, reader);

		Console* console = new Console(db);
		newFragment->connect([=](const QString& fragment) {
			console->evaluateFragment(fragment);
		});

		console->stream.connect(streamHandler);

		reader->startAsThread();
	}, X::DirectConnection);

	return app->exec();
}
