#include "Database.h"

#include <QThread>
#include "QueryStream.h"
#include "../../RemoteQuery.h"

#include <libxcore/EventLoop.h>

namespace Xtreeme
{
	namespace Memory
	{
		RemoteQuery* Database::query(const Query& query)
		{
			QueryStream* s = new QueryStream(data, query);
			
			s->dispatcher.data->connect([this](const Data::Pointer& newData) {
				// TODO compare data and newData, and rerun the query if they differ.
				this->data = newData;
			});

			return s->remoteQuery;
		}
/*
		bool Database::removeOne(const Xtreeme::Statement& s)
		{
			QWriteLocker locker(&lock);

			Statement* S = 0;

			foreach (Statement* s, findMemory(s))
			{
				if (!S)
				{
					S = s;
					continue;
				}

				if (s->basedOn.size() < S->basedOn.size())
					S = s;
			}

			return statements.remove(S);
		}

		bool Database::removeAll(const Xtreeme::Statement& s)
		{
			QWriteLocker locker(&lock);

			foreach (Statement* S, findMemory(s))
				statements.remove(S);

			return true;
		}
*/
	}
}

/*		void Database::dump()
		{
			QReadLocker lock(&p->lock);

			foreach (Statement* s, statements.all)
			{
				qDebug() << s->subject << s->predicate << s->object << s->context;
			}
		}

		void Database::addStatement(Statement* s)
		{
			Statements R = Reasoner::resolve(&p->cache, s);
			p->cache.add(s);

			foreach (Statement* r, R)
			{
				if (r->isBasedOn(r))
					continue;

				addStatement(r);
			}
		}*/
