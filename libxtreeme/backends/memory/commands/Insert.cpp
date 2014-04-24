#include "Insert.h"

#include "../DataDispatcher.h"

namespace Xtreeme
{
	namespace Memory
	{
		void Insert::registerDataAccess(DataDispatcher* d)
		{
			dispatcher = d;

			dispatcher->data->connect([this](const Data::Pointer& data) {
				this->db = data;
			});

			dispatcher->push();
		}

		void Insert::bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings)
		{
			const Xtreeme::Insert* c = static_cast<const Xtreeme::Insert*>(that);

			DataStreamInfo* input = resolveSignal(c->input, bindings);

			input->header.connect([](const Xtreeme::Header& header) {
				// TODO check header.
			}, this);

			input->data.connect([this](const Xtreeme::Row& row) {
				Statement s(row[1], row[2], row[3], row[4]);
				this->db.editable()->insert(s);
			}, this);

			input->end.connect([this]() {
				this->dispatcher->pop(db);
				delete this;
			}, this);
		}
	}
}
