#ifndef Xtreeme_Memory_Statements_h
#define Xtreeme_Memory_Statements_h

#include <QtGlobal>

namespace Xtreeme
{
	namespace Memory
	{
		template <typename T> struct P2
		{
			T p1;
			T p2;

			inline P2(T _p1, T _p2): p1(_p1), p2(_p2) {}

			inline bool operator==(const P2<T>& other) const
			{ return p1 == other.p1 && p2 == other.p2; }
		};

		template <typename T> struct P3
		{
			T p1;
			T p2;
			T p3;

			inline P3(T _p1, T _p2, T _p3): p1(_p1), p2(_p2), p3(_p3) {}

			inline bool operator==(const P3<T>& other) const
			{ return p1 == other.p1 && p2 == other.p2 && p3 == other.p3; }
		};

		template <typename T> struct P4
		{
			T p1;
			T p2;
			T p3;
			T p4;

			inline P4(T _p1, T _p2, T _p3, T _p4): p1(_p1), p2(_p2), p3(_p3), p4(_p4) {}

			inline bool operator==(const P4<T>& other) const
			{ return p1 == other.p1 && p2 == other.p2 && p3 == other.p3 && p4 == other.p4; }
		};
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
