#include "DB.h"

#include "../DataDispatcher.h"

namespace Xtreeme
{
	namespace Memory
	{
		DataStreamInfo* DB::outputInfo(int id)
		{
			switch (id)
			{
				case 0:
					return &data;

				default:
					return 0;
			}
		}
		
		void DB::registerDataAccess(DataDispatcher* dispatcher)
		{
			dispatcher->data->connect([this](const Data::Pointer& db) {
				this->data.header({"ID", "S", "P", "O", "C"});

				for (Resource::ID id : db->find(0, 0, 0, 0))
				{
					X::Variant res = db->resource(id);
					Statement s = res.as<Statement>();
					Resource r(id, s);
					this->data.data({r, s.subject, s.predicate, s.object, s.context});
				}

				this->data.end();
				delete this;
			}, this);
		}
	}
}
