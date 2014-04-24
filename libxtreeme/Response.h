#ifndef Xtreeme_Response_h
#define Xtreeme_Response_h

#include "libxtreeme.h"

#include <QObject>

namespace Xtreeme
{
	struct ResponseP;
	class XTREEME_EXPORT Response: public QObject
	{
		protected:
			Response(ResponseP* p, QObject* parent = 0);
			ResponseP* p;

		public:
			enum Error
			{
				Success = 0,
				GraphNotFound = 1
			};

			Response();
			Response(Error e, QString arg1 = QString(), QString arg2 = QString(), QString arg3 = QString());
			virtual ~Response();

			bool hasSucceeded();
			bool hasFailed();
			Error error();
			QString errorString();
	};
}

#endif
