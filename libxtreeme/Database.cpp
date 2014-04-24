#include "Database.h"

#include "Graph.h"
#include "Backend.h"
#include "BackendFactory.h"

#include <QPluginLoader>
#include <QtPlugin>
#include "BackendFactory.h"

#ifdef XTREEME_LINK_MEMORY
#include "backends/memory/BackendFactory.h"
#endif

#ifdef XTREEME_LINK_REMOTE
#include "backends/remote/BackendFactory.h"
#endif

#ifdef XTREEME_INCLUDE_MEMORY
Q_IMPORT_PLUGIN(xtreeme_memory)
#endif

#ifdef XTREEME_INCLUDE_REMOTE
Q_IMPORT_PLUGIN(xtreeme_remote)
#endif

#include <libxcore/EventLoop.h>
#include "Query.h"
#include "Command.h"
#include "RemoteQuery.h"

namespace Xtreeme
{
	bool Database::factoriesLoaded = false;
	QList<BackendFactory*> Database::factories;

	Database::Database(QObject* parent):
		QObject(parent)
	{}

	Database::~Database()
	{
		delete p;
	}

	Database* Database::open(const QUrl& dsn, QObject* parent)
	{
		QString scheme = dsn.scheme();

		if (!factoriesLoaded)
		{
			factoriesLoaded = true;

			foreach (QObject* plugin, QPluginLoader::staticInstances())
			{
				BackendFactory* factory = qobject_cast<BackendFactory*>(plugin);
				if (factory)
					factories << factory;
			}

#if defined(XTREEME_LINK_MEMORY)
			factories << new Memory::BackendFactory();
#endif

#if defined(XTREEME_LINK_REMOTE)
			factories << new Remote::BackendFactory();
#endif
		}

		foreach (BackendFactory* factory, factories)
		{
			if (factory->supports(scheme))
			{
				Database* db = new Database(parent);
				db->p = factory->create(dsn, db);
				return db;
			}
		}

		qWarning("Scheme not supported.");
		return 0;
	}

	RemoteQuery* Database::query(const Xtreeme::Query& query)
	{
		return p->query(query);
	}

	Graph* Database::graph(const Xtreeme::Resource& res)
	{
		return new Graph(this, res);
	}

	Response* Database::create(const Xtreeme::Resource& graph)
	{
/*		QueryStream* stream = new QueryStream(this);
		stream->setQuery(new Create(graph));
		stream->endQuery();
		stream->waitForResponse();
		return stream->response();*/
		return 0;
	}

	Response* Database::drop(const Xtreeme::Resource& graph)
	{
/*		QueryStream* stream = new QueryStream(this);
		stream->setQuery(new Drop(graph));
		stream->endQuery();
		stream->waitForResponse();
		return stream->response();*/
		return 0;
	}

	QVector<Xtreeme::Statement> Database::find(const Xtreeme::Statement& pattern) const
	{
		DB* db = new DB;
		Match* match = new Match(pattern, db->data());
		OutputStream* output = new OutputStream(match->output());

		DataStream stream;
		output->stream = &stream;

		Query pipeline;
		pipeline << db << match << output;

		RemoteQuery* q = const_cast<Database*>(this)->query(pipeline);

		X::EventLoop::call(q->start, q->finish, q->thread);

//		return stream.data();
	}

	Solution Database::solve(const StatementPattern& pattern) const
	{
		return solve(QVector<Xtreeme::StatementPattern>() << pattern);
	}

	Solution Database::solve(const QVector<StatementPattern>& p) const
	{
		QVector<RowPattern> pattern;
		foreach (const StatementPattern& s, p)
			pattern << s;

		DB* db = new DB;
		Solve* solve = new Solve(pattern, db->data());
		OutputStream* output = new OutputStream(solve->output());

		DataStream stream;
		output->stream = &stream;

		Solution solution;
		stream.header.connect([&](const Header& header) {
			solution = header;
		});
		stream.data.connect([&](const Row& row) {
			solution.addRow(row);
		});

		Query pipeline;
		pipeline << db << solve << output;

		RemoteQuery* q = const_cast<Database*>(this)->query(pipeline);

		X::EventLoop::call(q->start, q->finish, q->thread);

		return solution;
	}

	Solution Database::solve(const std::initializer_list<StatementPattern>& pattern) const
	{
		QVector<Xtreeme::StatementPattern> p;
		for (auto it = pattern.begin(); it < pattern.end(); ++it)
			p << *it;

		return solve(p);
	}
}
