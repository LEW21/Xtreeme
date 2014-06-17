#ifndef Xtreeme_Memory_Data_h
#define Xtreeme_Memory_Data_h

#include <libxcore/SharedData.h>

#include <libxcore/SharedDataPointer.h>
#include <QVector>
#include <QHash>
#include <QUuid>
#include "Statements.h"
#include "../../RDF.h"
#include "Reasoner.h"

namespace Xtreeme
{
	namespace Memory
	{
		class Data: public X::SharedData
		{
			mutable QVector<X::Variant> resources;
			mutable QHash<X::Variant, Resource::ID> resourceIDs;
			Statements statements;

		public:
			inline Data();

			inline X::Variant resource(Resource::ID id) const;
			inline Resource::ID resourceID(const X::Variant&) const;

			inline auto operator[](const X::Variant& v)    const -> Resource {return {resourceID(v), v};}
			inline auto operator[](const Resource::ID& id) const -> Resource {return {id, resource(id)};}

			inline Resource::ID insert(const Statement&, bool addSource = true);

			inline QVector<Resource::ID> find(Resource::ID S, Resource::ID P, Resource::ID O, Resource::ID C) const;
			inline QVector<Statement> find(Resource S, Resource P, Resource O, Resource C) const;

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
			resources.append({});
			resourceIDs[{}] = 0;
		}

		inline X::Variant Data::resource(Resource::ID id) const
		{
			if (id >= resources.size())
				return X::Variant();

			return resources[id];
		}

		inline Resource::ID Data::resourceID(const X::Variant& v) const
		{
			if (!v.isValid())
				return 0;

			auto& id = resourceIDs[v];
			if (!id)
			{
				auto c = v;
				if (v.is<Statement>())
				{
					auto s = v.as<Statement>();
					s.subject.id   = resourceID(s.subject.value);
					s.predicate.id = resourceID(s.predicate.value);
					s.object.id    = resourceID(s.object.value);
					s.context.id   = resourceID(s.context.value);
					c = s;
				}

				resources.append(std::move(c));
				id = resources.size() - 1;
			}
			return id;
		}

		inline Resource::ID Data::insert(const Statement& sorig, bool addSource)
		{
			if (!sorig.isValid())
				throw std::invalid_argument("Data::insert");

			auto id = resourceID(sorig);
			auto s = resource(id).as<Statement>(); // load node IDs.

			if (find(s.subject.id, s.predicate.id, s.object.id, s.context.id).size())
				return id; // Already exists.

			statements.insert(id, s);

			auto inferred = think(*this, s);

			std::vector<Xtreeme::Statement> metadata;

			auto _type      = (*this)[RDF::type];
			auto _Statement = (*this)[RDF::Statement];
			auto _subject   = (*this)[RDF::subject];
			auto _predicate = (*this)[RDF::predicate];
			auto _object    = (*this)[RDF::object];
			auto _metagraph = (*this)[X::IRI{QString{"http://xtreeme.org/metagraph"}}];
			auto _source    = (*this)[X::IRI{QString{"http://xtreeme.org/source"}}];
			auto _Insertion = (*this)[X::IRI{QString{"http://xtreeme.org/Insertion"}}];
			auto _Inference = (*this)[X::IRI{QString{"http://xtreeme.org/Inference"}}];

			auto res = Resource(id, s);

			if (addSource)
			{
				auto source = (*this)[X::Variant{X::String(QUuid::createUuid().toString())}];
				metadata.emplace_back(res, _source, source);
				metadata.emplace_back(source, _type, _Insertion);
			}

			/*
				metadata.emplace_back(res, _type, _Statement);
				metadata.emplace_back(res, _subject, s.subject);
				metadata.emplace_back(res, _predicate, s.predicate);
				metadata.emplace_back(res, _object, s.object);
			*/

			for (auto& inf : inferred)
			{
				inf.s.context = _metagraph;
				auto infRes = (*this)[inf.s];

				auto source = (*this)[X::Variant{X::String(QUuid::createUuid().toString())}];

				metadata.emplace_back(infRes, _source, source);
				metadata.emplace_back(source, _type, _Inference);

				for (auto iFrom : inf.inferredFrom)
					metadata.emplace_back(source, _source, (*this)[iFrom]);
			}

			for (auto s : metadata)
			{
				s.context = _metagraph;
				statements.insert(resourceID(s), s);
			}

			for (auto inf : inferred)
				insert(inf.s, false);

			return id;
		}

		inline QVector<Resource::ID> Data::find(Resource::ID S, Resource::ID P, Resource::ID O, Resource::ID C) const
		{
			return statements.find(S, P, O, C);
		}

		inline QVector<Statement> Data::find(Resource S, Resource P, Resource O, Resource C) const
		{
			S.id = S.id ? S.id : resourceID(S.value);
			P.id = P.id ? P.id : resourceID(P.value);
			O.id = O.id ? O.id : resourceID(O.value);
			C.id = C.id ? C.id : resourceID(C.value);

			auto found = find(S.id, P.id, O.id, C.id);
			auto R = QVector<Statement>{};
			for (auto f : found)
				R.push_back((*this)[f].value.as<Statement>());
			return R;
		}

		inline Data* Data::copy() const
		{
			return new Data(*this);
		}
	}
}

#endif
