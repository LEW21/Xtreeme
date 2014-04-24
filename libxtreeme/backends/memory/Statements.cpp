#include "Statements.h"

uint qHash(const Xtreeme::Memory::P4<Xtreeme::Resource::ID>& p)
{
	return (qHash(p.p1) >> 2) + (qHash(p.p2) >> 2) + (qHash(p.p3) >> 2) + (qHash(p.p4) >> 2);
}

uint qHash(const Xtreeme::Memory::P3<Xtreeme::Resource::ID>& p)
{
	return qHash(p.p1) * 0.33 + qHash(p.p2) * 0.33 + qHash(p.p3) * 0.34;
}

uint qHash(const Xtreeme::Memory::P2<Xtreeme::Resource::ID>& p)
{
	return (qHash(p.p1) >> 1) + (qHash(p.p2) >> 1);
}

namespace Xtreeme
{
	namespace Memory
	{
		template <class I, class K> inline static QVector<Resource::ID> V(I i, const K& k)
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

			bySP.insert(P2<Resource::ID>(s.subject.id, s.predicate.id), id);
			bySO.insert(P2<Resource::ID>(s.subject.id, s.object.id), id);
			bySC.insert(P2<Resource::ID>(s.subject.id, s.context.id), id);
			byPO.insert(P2<Resource::ID>(s.predicate.id, s.object.id), id);
			byPC.insert(P2<Resource::ID>(s.predicate.id, s.context.id), id);
			byOC.insert(P2<Resource::ID>(s.object.id, s.context.id), id);

			bySPO.insert(P3<Resource::ID>(s.subject.id, s.predicate.id, s.object.id), id);
			bySPC.insert(P3<Resource::ID>(s.subject.id, s.predicate.id, s.context.id), id);
			bySOC.insert(P3<Resource::ID>(s.subject.id, s.object.id, s.context.id), id);
			byPOC.insert(P3<Resource::ID>(s.predicate.id, s.object.id, s.context.id), id);

			bySPOC.insert(P4<Resource::ID>(s.subject.id, s.predicate.id, s.object.id, s.context.id), id);

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

			bySP.remove(P2<Resource::ID>(s.subject.id, s.predicate.id), id);
			bySO.remove(P2<Resource::ID>(s.subject.id, s.object.id), id);
			bySC.remove(P2<Resource::ID>(s.subject.id, s.context.id), id);
			byPO.remove(P2<Resource::ID>(s.predicate.id, s.object.id), id);
			byPC.remove(P2<Resource::ID>(s.predicate.id, s.context.id), id);
			byOC.remove(P2<Resource::ID>(s.object.id, s.context.id), id);

			bySPO.remove(P3<Resource::ID>(s.subject.id, s.predicate.id, s.object.id), id);
			bySPC.remove(P3<Resource::ID>(s.subject.id, s.predicate.id, s.context.id), id);
			bySOC.remove(P3<Resource::ID>(s.subject.id, s.object.id, s.context.id), id);
			byPOC.remove(P3<Resource::ID>(s.predicate.id, s.object.id, s.context.id), id);

			bySPOC.remove(P4<Resource::ID>(s.subject.id, s.predicate.id, s.object.id, s.context.id), id);

			return true;
		}

#define FIND4(BY, A, B, C, D) return V(BY.find(P4<Resource::ID>(A, B, C, D)), P4<Resource::ID>(A, B, C, D));
#define FIND3(BY, A, B, C)    return V(BY.find(P3<Resource::ID>(A, B, C)),    P3<Resource::ID>(A, B, C));
#define FIND2(BY, A, B)       return V(BY.find(P2<Resource::ID>(A, B)),       P2<Resource::ID>(A, B));
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
