#ifndef Xtreeme_Remote_QueryStream_h
#define Xtreeme_Remote_QueryStream_h

#include "remote.h"

#include <QObject>

#include "../../Statement.h"

namespace Xtreeme
{
	class QueryStream;
	class Query;

	namespace Remote
	{
		class QueryStream: public QObject
		{
			Q_OBJECT

			QIODevice* device;
			Xtreeme::QueryStream* stream;

		public:
			QueryStream(QIODevice*, Xtreeme::QueryStream*);
			~QueryStream();

		private slots:
			void queryHeader(Xtreeme::Query*);
			void queryData(const QVector<Xtreeme::Statement>&);
			void queryEnd();
		};
	}
}

#endif
