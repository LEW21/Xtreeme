#include "Statements.h"

using namespace std;

uint qHash(const Xtreeme::Memory::P4<Xtreeme::Resource::ID>& p)
{
	return (qHash(get<0>(p)) >> 2) + (qHash(get<1>(p)) >> 2) + (qHash(get<2>(p)) >> 2) + (qHash(get<3>(p)) >> 2);
}

uint qHash(const Xtreeme::Memory::P3<Xtreeme::Resource::ID>& p)
{
	return qHash(get<0>(p)) * 0.33 + qHash(get<1>(p)) * 0.33 + qHash(get<2>(p)) * 0.34;
}

uint qHash(const Xtreeme::Memory::P2<Xtreeme::Resource::ID>& p)
{
	return (qHash(get<0>(p)) >> 1) + (qHash(get<1>(p)) >> 1);
}

namespace Xtreeme
{
	namespace Memory
	{
		template <class I> inline static QVector<Resource::ID> V(I i, decltype(i.key()) k)
		{
			QVector<Resource::ID> V;

			for (; i.key() == k; ++i)
				V << i.value();

			return V;
		}

		bool Statements::insert(Resource::ID id, const Xtreeme::Statement& s)
		{
			if (!id || !s.isValid())
				return false;

			all.append(id);

			byS.insert(s.subject.id, id);
			byP.insert(s.predicate.id, id);
			byO.insert(s.object.id, id);
			byC.insert(s.context.id, id);

			bySP.insert({s.subject.id, s.predicate.id}, id);
			bySO.insert({s.subject.id, s.object.id}, id);
			bySC.insert({s.subject.id, s.context.id}, id);
			byPO.insert({s.predicate.id, s.object.id}, id);
			byPC.insert({s.predicate.id, s.context.id}, id);
			byOC.insert({s.object.id, s.context.id}, id);

			bySPO.insert({s.subject.id, s.predicate.id, s.object.id}, id);
			bySPC.insert({s.subject.id, s.predicate.id, s.context.id}, id);
			bySOC.insert({s.subject.id, s.object.id, s.context.id}, id);
			byPOC.insert({s.predicate.id, s.object.id, s.context.id}, id);

			bySPOC.insert({s.subject.id, s.predicate.id, s.object.id, s.context.id}, id);

			return true;
		}

		bool Statements::remove(Resource::ID id, const Xtreeme::Statement& s)
		{
			if (!id || !s.isValid())
				return false;

			int index = all.indexOf(id);
			if (index == -1)
				return false;

			all.remove(index);

			byS.remove(s.subject.id, id);
			byP.remove(s.predicate.id, id);
			byO.remove(s.object.id, id);
			byC.remove(s.context.id, id);

			bySP.remove({s.subject.id, s.predicate.id}, id);
			bySO.remove({s.subject.id, s.object.id}, id);
			bySC.remove({s.subject.id, s.context.id}, id);
			byPO.remove({s.predicate.id, s.object.id}, id);
			byPC.remove({s.predicate.id, s.context.id}, id);
			byOC.remove({s.object.id, s.context.id}, id);

			bySPO.remove({s.subject.id, s.predicate.id, s.object.id}, id);
			bySPC.remove({s.subject.id, s.predicate.id, s.context.id}, id);
			bySOC.remove({s.subject.id, s.object.id, s.context.id}, id);
			byPOC.remove({s.predicate.id, s.object.id, s.context.id}, id);

			bySPOC.remove({s.subject.id, s.predicate.id, s.object.id, s.context.id}, id);

			return true;
		}

#define FIND4(BY, A, B, C, D) return V(BY.find({A, B, C, D}), {A, B, C, D});
#define FIND3(BY, A, B, C)    return V(BY.find({A, B, C}),    {A, B, C});
#define FIND2(BY, A, B)       return V(BY.find({A, B}),       {A, B});
#define FIND1(BY, A)          return V(BY.find(A), A);

		QVector<Resource::ID> Statements::find(Resource::ID S, Resource::ID P, Resource::ID O, Resource::ID C) const
		{
			if (S)
			{
				if (P)
				{
					if (O)
					{
						if (C)
 							FIND4(bySPOC, S, P, O, C)
						else
							FIND3(bySPO, S, P, O);
					}
					else
					{
						if (C)
							FIND3(bySPC, S, P, C)
						else
							FIND2(bySP, S, P);
					}
				}
				else
				{
					if (O)
					{
						if (C)
							FIND3(bySOC, S, O, C)
						else
							FIND2(bySO, S, O);
					}
					else
					{
						if (C)
							FIND2(bySC, S, C)
						else
							FIND1(byS, S);
					}
				}
			}
			else
			{
				if (P)
				{
					if (O)
					{
						if (C)
							FIND3(byPOC, P, O, C)
						else
							FIND2(byPO, P, O);
					}
					else
					{
						if (C)
							FIND2(byPC, P, C)
						else
							FIND1(byP, P);
					}
				}
				else
				{
					if (O)
					{
						if (C)
							FIND2(byOC, O, C)
						else
							FIND1(byO, O);
					}
					else
					{
						if (C)
							FIND1(byC, C)
						else
							return all;
					}
				}
			}
		}
	}
}
