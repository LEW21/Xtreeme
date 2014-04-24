#ifndef Xtreeme_Database_h
#define Xtreeme_Database_h

#include "libxtreeme.h"

#include <QObject>
#include <QUrl>

#include "Graph.h"
#include "Resource.h"
#include "StatementPattern.h"
#include "Solution.h"

namespace Xtreeme
{
	class Query;
	class Response;
	class RemoteQuery;

	class Backend;
	class BackendFactory;
	class XTREEME_EXPORT Database: public QObject
	{
		Q_OBJECT
		Backend* p;
		friend class QueryStream;
		friend class Graph;

		Database(QObject* parent = 0);

		static bool factoriesLoaded;
		static QList<BackendFactory*> factories;

	public:
		static Database* open(const QUrl&, QObject* parent = 0);

		~Database();

		RemoteQuery* query(const Query&);
		QVector<RemoteQuery*> query(const QString& sparql);

		Graph* graph(const Xtreeme::Resource& res = Xtreeme::Resource());

		Response* create(const Xtreeme::Resource& graph);
		Response* drop(const Xtreeme::Resource& graph);

		QVector<Xtreeme::Statement> find(const Xtreeme::Statement&) const;

		Solution solve(const Xtreeme::StatementPattern&) const;
		Solution solve(const std::initializer_list<Xtreeme::StatementPattern>&) const;
		Solution solve(const QVector<Xtreeme::StatementPattern>&) const;
	};
}

#endif
