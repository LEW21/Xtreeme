#include "Graph.h"

#include "Database.h"
#include "Backend.h"
#include <QString>

namespace Xtreeme
{
	struct GraphP
	{
		Database* db;
		Xtreeme::Resource name;

		inline GraphP(Database* _db, const Xtreeme::Resource& _name): db(_db), name(_name) {}
	};

	Graph::Graph(Database* db, const Xtreeme::Resource& name, QObject* parent)
		: QObject(parent ? parent : db)
		, p(new GraphP(db, name))
	{}

	Graph::~Graph()
	{
		delete p;
	}

	Xtreeme::Resource Graph::name() const
	{
		return p->name;
	}

	Response* Graph::create()
	{
		return p->db->create(p->name);
	}

	Response* Graph::drop()
	{
		return p->db->drop(p->name);
	}

	QVector<Xtreeme::Statement> Graph::statements() const
	{
		return p->db->find(Statement(Resource(), Resource(), Resource(), p->name));
	}

	QVector<Xtreeme::Statement> Graph::find(const Xtreeme::Statement& s) const
	{
		Statement pattern = s;
		pattern.context = p->name;

		return p->db->find(pattern);
	}

	Response* Graph::insert(const Xtreeme::Statement& s)
	{
		return insert(QVector<Xtreeme::Statement>() << s)[0];
	}

	QList<Response*> Graph::insert(const QVector<Xtreeme::Statement>& data)
	{
		QVector<Xtreeme::Statement> copy;

		foreach (Xtreeme::Statement s, data)
		{
			s.context = name();
			copy << s;
		}

/*		QueryStream* stream = new QueryStream(p->db);
		stream->setQuery(new Xtreeme::InsertData());
		stream->addQueryData(copy);
		stream->endQuery();
		stream->waitForResponse();

		// TODO return
		return QList<Response*>() << stream->response();*/

		return QList<Response*>();
	}

	Response* Graph::remove(const Xtreeme::Statement& s)
	{
		return remove(QVector<Xtreeme::Statement>() << s)[0];
	}

	QList<Response*> Graph::remove(const QVector<Xtreeme::Statement>& data)
	{
		QVector<Xtreeme::Statement> copy;

		foreach (Xtreeme::Statement s, data)
		{
			s.context = name();
			copy << s;
		}

/*		QueryStream* stream = new QueryStream(p->db);
		stream->setQuery(new Xtreeme::DeleteData());
		stream->addQueryData(copy);
		stream->endQuery();
		stream->waitForResponse();

		// TODO return
		return QList<Response*>() << stream->response();*/

		return QList<Response*>();
	}

	Response* Graph::clear()
	{
/*
		QueryStream* stream = new QueryStream(p->db);
		stream->setQuery(new Clear(p->name));
		stream->endQuery();
		stream->waitForResponse();
		return stream->response();
*/
		return 0;
	}

}
