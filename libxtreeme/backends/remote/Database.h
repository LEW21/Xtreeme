#ifndef Xtreeme_Remote_Database_h
#define Xtreeme_Remote_Database_h

#include "remote.h"

#include "../../Backend.h"

namespace Xtreeme
{
	class StreamDispatcher;

	namespace Remote
	{
		class REMOTE_EXPORT Database: public Xtreeme::Backend
		{
			StreamDispatcher* remote;

		public:
			Database(const QUrl& dsn, Xtreeme::Database* db);
			~Database();

			void connectStream(Xtreeme::QueryStream*);

			QVector<Xtreeme::Statement> find(const Xtreeme::Statement&) const;
		};
	}
}

#endif
