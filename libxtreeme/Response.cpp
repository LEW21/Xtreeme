#include "Response.h"

namespace Xtreeme
{
	struct ResponseP
	{
		Response::Error error;
		QString message;

		inline ResponseP(Response::Error _error): error(_error) {}
	};

	Response::Response()
		: QObject()
		, p(new ResponseP(Success))
	{}

	Response::Response(Error e, QString arg1, QString arg2, QString arg3)
		: QObject()
		, p(new ResponseP(e))
	{
		// TODO Message generation
	}

	Response::~Response()
	{
		delete p;
	}

	bool Response::hasSucceeded()
	{
		return p->error == Success;
	}

	bool Response::hasFailed()
	{
		return p->error != Success;
	}

	Response::Error Response::error()
	{
		return p->error;
	}

	QString Response::errorString()
	{
		return p->message;
	}
}
