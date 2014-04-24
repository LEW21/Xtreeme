#ifndef Xtreeme_Graph_h
#define Xtreeme_Graph_h

#include "libxtreeme.h"

#include <QObject>

#include <QString>
#include <QList>
#include "Statement.h"
#include "StatementPattern.h"

namespace Xtreeme
{
	class Database;
	class Response;

	class GraphP;
	class XTREEME_EXPORT Graph: public QObject
	{
		Q_OBJECT
		Q_PROPERTY(QVector<Xtreeme::Statement> statements READ statements)
		GraphP* p;

	public:
		Graph(Database* db, const Xtreeme::Resource& name, QObject* parent = 0);
		~Graph();

		Xtreeme::Resource name() const;

		Response* create();
		Response* drop();

		QVector<Xtreeme::Statement> statements() const;

		QVector<Xtreeme::Statement> find(const Xtreeme::Statement& pattern) const;

		Response* insert(const Xtreeme::Statement&);
		QList<Response*> insert(const QVector<Xtreeme::Statement>&);

		Response* remove(const Xtreeme::Statement&);
		QList<Response*> remove(const QVector<Xtreeme::Statement>&);

		Response* clear();
	};
}

#endif
