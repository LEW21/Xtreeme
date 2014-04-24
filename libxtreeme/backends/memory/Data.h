#ifndef Xtreeme_Memory_Data_h
#define Xtreeme_Memory_Data_h

#include <libxcore/SharedData.h>

#include <libxcore/SharedDataPointer.h>
#include <QVector>
#include <QHash>
#include "Statements.h"

namespace Xtreeme
{
	namespace Memory
	{
		class Data: public X::SharedData
		{
			QVector<X::Variant> resources;
			QHash<X::Variant, Resource::ID> resourceIDs;
			Statements statements;

		public:
			inline Data();

			inline Resource::ID lastID() const;

			inline X::Variant resource(Resource::ID id) const;
			inline Resource::ID resourceID(const X::Variant&) const;

			inline Resource::ID insert(const X::Variant&);
			inline bool remove(const X::Variant&);

			inline QVector<Resource::ID> find(Resource::ID S, Resource::ID P, Resource::ID O, Resource::ID C) const;

			inline Data* copy() const;

			struct Pointer: public X::SharedDataPointer<Data>
			{
				inline Pointer()
					: X::SharedDataPointer<Data>(new Data())
				{}

				inline Pointer(Data* data)
					: X::SharedDataPointer<Data>(data)
				{}
			};
		};

		inline Data::Data()
		{
			// 0th element is null.
			resources.append(X::Variant());
		}

		inline Resource::ID Data::lastID() const
		{
			return resources.size() - 1;
		}

		inline X::Variant Data::resource(Resource::ID id) const
		{
			if (id > lastID())
				return X::Variant();

			return resources[id];
		}

		inline Resource::ID Data::resourceID(const X::Variant& res) const
		{
			return resourceIDs[res];
		}

		inline Resource::ID Data::insert(const X::Variant& res)
		{
			Resource::ID id = resourceID(res);
			if (id)
				return id; // or 0 (false)?

			X::Variant copy = res;

			if (copy.is<Statement>())
			{
				qDebug() << "Inserting a Statement...";

				Statement s = copy.as<Statement>();

				if (!s.isValid())
					return 0;

				qDebug() << "Still doing it...";

				if (!s.subject.id)
					s.subject.id = insert(s.subject.value);

				if (!s.predicate.id)
					s.predicate.id = insert(s.predicate.value);

				if (!s.object.id)
					s.object.id = insert(s.object.value);

				if (!s.context.id)
					s.context.id = insert(s.context.value);

				copy = s;
			}

			resources.append(copy);
			id = lastID();

			resourceIDs.insert(copy, id);

			if (copy.is<Statement>())
				statements.insert(id, copy.as<Statement>());

			return id;
		}

		inline bool Data::remove(const X::Variant& res)
		{
			Resource::ID id = resourceID(res);
			if (!id)
				return false;

			resources[id] = X::Variant();
			resourceIDs.remove(res);
			return true;
		}

		inline QVector<Resource::ID> Data::find(Resource::ID S, Resource::ID P, Resource::ID O, Resource::ID C) const
		{
			return statements.find(S, P, O, C);
		}

		inline Data* Data::copy() const
		{
			return new Data(*this);
		}
	}
}

#endif
