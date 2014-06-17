#ifndef Xtreeme_Memory_Statements_h
#define Xtreeme_Memory_Statements_h

#include <QtGlobal>

namespace Xtreeme
{
	namespace Memory
	{
		template <typename... T>
		struct ImplicitTuple: public std::tuple<T...>
		{
			template <typename... U>
			constexpr ImplicitTuple(U&&... a): std::tuple<T...>(std::forward<U>(a)...) {}
		};

		template <typename T>
		using P2 = ImplicitTuple<T, T>;

		template <typename T>
		using P3 = ImplicitTuple<T, T, T>;

		template <typename T>
		using P4 = ImplicitTuple<T, T, T, T>;
	}
}

uint qHash(const Xtreeme::Memory::P4<quint64>&);
uint qHash(const Xtreeme::Memory::P3<quint64>&);
uint qHash(const Xtreeme::Memory::P2<quint64>&);

#include <QMultiHash>
#include <QVector>
#include "../../Resource.h"
#include "../../Statement.h"

namespace Xtreeme
{
	namespace Memory
	{
		struct Statements
		{
			QVector<Resource::ID> all;

			QMultiHash<Resource::ID, Resource::ID> byS;
			QMultiHash<Resource::ID, Resource::ID> byP;
			QMultiHash<Resource::ID, Resource::ID> byO;
			QMultiHash<Resource::ID, Resource::ID> byC;

			QMultiHash<P2<Resource::ID>, Resource::ID> bySP;
			QMultiHash<P2<Resource::ID>, Resource::ID> bySO;
			QMultiHash<P2<Resource::ID>, Resource::ID> bySC;
			QMultiHash<P2<Resource::ID>, Resource::ID> byPO;
			QMultiHash<P2<Resource::ID>, Resource::ID> byPC;
			QMultiHash<P2<Resource::ID>, Resource::ID> byOC;

			QMultiHash<P3<Resource::ID>, Resource::ID> bySPO;
			QMultiHash<P3<Resource::ID>, Resource::ID> bySPC;
			QMultiHash<P3<Resource::ID>, Resource::ID> bySOC;
			QMultiHash<P3<Resource::ID>, Resource::ID> byPOC;

			QMultiHash<P4<Resource::ID>, Resource::ID> bySPOC;

			bool insert(Resource::ID, const Xtreeme::Statement&);
			bool remove(Resource::ID, const Xtreeme::Statement&);

			QVector<Resource::ID> find(Resource::ID S, Resource::ID P, Resource::ID O, Resource::ID C) const;
		};
	}
}

#endif
