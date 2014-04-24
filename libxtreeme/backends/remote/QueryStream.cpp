#include "QueryStream.h"

#include "../../QueryStream.h"
#include "../../Query.h"

#include <libxtypes/Variant.h>
#include <libxtypes/String.h>

#include <libxtreeme/Resource.h>
#include <libxtreeme/Statement.h>

QDataStream& operator<<(QDataStream& stream, const X::Variant& v)
{
	stream << QString(v.type()->iri);
	stream << QString(v.as<X::String>());
	return stream;
}

QDataStream& operator<<(QDataStream& stream, const Xtreeme::Resource& res)
{
	stream << (qint32) res.id();
	stream << res.value();
	return stream;
}

QDataStream& operator<<(QDataStream& stream, const Xtreeme::Statement& statement)
{
	stream << statement.subject();
	stream << statement.predicate();
	stream << statement.object();
	stream << statement.context();
	return stream;
}

namespace Xtreeme
{
	namespace Remote
	{
		QueryStream::QueryStream(QIODevice* d, Xtreeme::QueryStream* s)
			: QObject(d)
			, device(d)
			, stream(s)
		{
			connect(stream, SIGNAL(queryHeader(Xtreeme::Query*)), this, SLOT(queryHeader(Xtreeme::Query*)), Qt::QueuedConnection);
			connect(stream, SIGNAL(queryData(QVector<Xtreeme::Statement>)), this, SLOT(queryData(QVector<Xtreeme::Statement>)), Qt::QueuedConnection);
			connect(stream, SIGNAL(queryEnd()), this, SLOT(queryEnd()), Qt::QueuedConnection);

			connect(stream, SIGNAL(destroyed()), this, SLOT(deleteLater()), Qt::DirectConnection);
		}

		QueryStream::~QueryStream()
		{}

		void QueryStream::queryHeader(Xtreeme::Query* query)
		{
			QDataStream stream(device);
			stream << (qint32) query->type();

			switch (query->type())
			{
				case Query::InsertData:
				case Query::DeleteData:
				break;
			}
		}

		void QueryStream::queryData(const QVector<Xtreeme::Statement>& statements)
		{
			QDataStream stream(device);
			foreach (const Statement& s, statements)
				stream << (qint32) 1 << s;
		}

		void QueryStream::queryEnd()
		{
			QDataStream stream(device);
			stream << (qint32) 0;
		}
	}
}
