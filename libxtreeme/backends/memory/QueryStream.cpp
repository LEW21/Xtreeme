#include "QueryStream.h"

#include "../../Query.h"
#include "../../RemoteQuery.h"
#include "../../Command.h"
#include "../../Response.h"
#include "../../Statement.h"
#include "../../Resource.h"

#include "Data.h"

#include "commands/DB.h"
#include "commands/Solve.h"
#include "commands/Insert.h"
#include "commands/InputStream.h"
#include "commands/OutputStream.h"

#include <libxcore/EventLoop.h>
#include <cassert>

namespace Xtreeme
{
	namespace Memory
	{
		QueryStream::QueryStream(const Data::Pointer& data, const Query& query)
			: remoteQuery(new RemoteQuery())
		{
			QHash<const Xtreeme::Command*, Command*> bindings;

			foreach (Xtreeme::Command* command, query)
			{
				Command* c = 0;

				switch (command->type)
				{
					case Xtreeme::Command::DB:
						c = new Xtreeme::Memory::DB;
						break;

					case Xtreeme::Command::Solve:
						c = new Xtreeme::Memory::Solve;
						break;
						
					case Xtreeme::Command::Insert:
						c = new Xtreeme::Memory::Insert;
						break;
						
					case Xtreeme::Command::InputStream:
						c = new Xtreeme::Memory::InputStream;
						break;
						
					case Xtreeme::Command::OutputStream:
						c = new Xtreeme::Memory::OutputStream;
						break;
				}

				c->registerDataAccess(&dispatcher);
				c->bind(command, &bindings);

				bindings[command] = c;

				c->destroyed.connect([=]() {
					if (!--refs)
						X::postEvent([=]() {
							delete this;
						}, this->thread);
				});

				X::EventLoop* loop = new X::EventLoop();

				loop->started.connect([=]() {
					c->thread = loop->thread;
				}, X::DirectConnection);

				c->destroyed.connect([=]() {
					loop->quit();
				}, X::DirectConnection);

				loop->finished.connect([=]() {
					delete loop;
				});

				loop->startAsThread();

				refs++;
			}

			remoteQuery->start.connect([=]() {
				dispatcher.pop(data);
			}, X::DirectConnection);

			destroyed.connect([=]() {
				remoteQuery->finish();
			}, remoteQuery);
		}

		QueryStream::~QueryStream()
		{}
	}
}
