#ifndef Xtreeme_Backend_h
#define Xtreeme_Backend_h

namespace Xtreeme
{
	class Query;
	class RemoteQuery;

	class Backend
	{
	public:
		virtual RemoteQuery* query(const Query&) = 0;
		virtual ~Backend();
	};
}

#endif
