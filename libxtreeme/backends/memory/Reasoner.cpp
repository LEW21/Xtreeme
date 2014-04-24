#include "Reasoner.h"

#include "Graph.h"
#include "Statement.h"
#include "Resource.h"

#include "../../RDF.h"
#include "../../OWL.h"

#define ASSERT(bool) Q_ASSERT(bool)

const Xtreeme::Resource instanceOf         = RDF::type;
const Xtreeme::Resource sameAs             = OWL::sameAs;
const Xtreeme::Resource inverseOf          = OWL::inverseOf;
const Xtreeme::Resource equivalentProperty = OWL::equivalentProperty;
const Xtreeme::Resource subPropertyOf      = RDF::subPropertyOf;
const Xtreeme::Resource equivalentClass    = OWL::equivalentClass;
const Xtreeme::Resource subClassOf         = RDF::subClassOf;

const Xtreeme::Resource TransitiveProperty = OWL::TransitiveProperty;
const Xtreeme::Resource SymmetricProperty  = OWL::SymmetricProperty;

namespace Xtreeme
{
	namespace Memory
	{
		Reasoner::Reasoner(Graph* graph)
			: instanceOf(graph->fromAPI(::instanceOf))
			, sameAs(graph->fromAPI(::sameAs))
			, inverseOf(graph->fromAPI(::inverseOf))
			, equivalentProperty(graph->fromAPI(::equivalentProperty))
			, subPropertyOf(graph->fromAPI(::subPropertyOf))
			, equivalentClass(graph->fromAPI(::equivalentClass))
			, subClassOf(graph->fromAPI(::subClassOf))
			, TransitiveProperty(graph->fromAPI(::TransitiveProperty))
			, SymmetricProperty(graph->fromAPI(::SymmetricProperty))
		{}

		Statements Reasoner::resolve(Graph* graph, Statement* N)
		{
			Statements R; // reasoned statements

			// Check for special things related to our subject.
			foreach (Statement* p, data->find(N->subject, sameAs, null, null))
			{
				ASSERT(p->subject == N->subject); // p describes our subject.
				ASSERT(p->predicate == sameAs);

				R << new Statement(p->object, N->predicate, N->object, Statements() << N << p);
			}

			// Check for special things related to our predicate.
			foreach (Statement* p, data->find(N->predicate, null, null, null))
			{
				ASSERT(p->subject == N->predicate); // p describes our predicate.

				if (p->predicate == sameAs || p->predicate == equivalentProperty || p->predicate == subPropertyOf)
				{
					R << new Statement(N->subject, p->object, N->object, Statements() << N << p);
				}
				else if (p->predicate == inverseOf)
				{
					R << new Statement(N->object, p->object, N->subject, Statements() << N << p);
				}
				else if (p->predicate == instanceOf)
				{
					if (p->object == TransitiveProperty)
					{
						// We need A-Y-C for every A-Y-B B-Y-C pair.
						// If we are A-Y-B:
						foreach (Statement* s, graph->bySubject.values(N->object))
						{
							ASSERT(s->subject == N->object);
							if (N->predicate == s->predicate)
								R << new Statement(N->subject, N->predicate, s->object, Statements() << N << p << s);
						}
						// If we are B-Y-C:
						foreach (Statement* s, graph->byObject.values(N->subject))
						{
							ASSERT(s->object == N->subject);
							if (N->predicate == s->predicate)
								R << new Statement(s->subject, N->predicate, N->object, Statements() << N << p << s);
						}
					}
					else if (p->object == SymmetricProperty)
					{
						R << new Statement(N->object, N->predicate, N->subject, Statements() << N << p);
					}
				}
			}

			// Check for special things related to our object.
			foreach (Statement* p, data->find(N->object, sameAs, null, null))
			{
				ASSERT(p->subject == N->object); // p describes our object.
				ASSERT(p->predicate == sameAs);
				
				R << new Statement(N->subject, N->predicate, p->object, Statements() << N << p);
			}

			if (N->predicate == instanceOf)
			{
				if (N->object == TransitiveProperty)
				{
					// OK, so this is a transitive property!
					// We need to create A-Y-C for every s(A-Y-B) z(B-Y-C) pair.
					foreach (Statement* s, graph->byPredicate.values(N->subject))
					{
						foreach (Statement* z, graph->byPredicate.values(N->subject))
						{
							if (s->object == z->subject)
								R << new Statement(s->subject, N->subject, z->object, Statements() << N << s << z);
						}
					}
				}
				else if (N->object == SymmetricProperty)
				{
					// OK, so this is a symmetric property!
					// We need to copy all the statements using it in a reversed way.
					foreach (Statement* s, graph->byPredicate.values(N->subject))
					{
						R << new Statement(s->object, N->subject, s->subject, Statements() << N << s);
					}
				}
			}
			else if (N->predicate == sameAs)
			{
				// Is currently added property sameAs? If so, then copy everything!
				// There is no difference in which way will we copy it - everything will be copied in the second way by reversed sameAs created before by the effect of SymmetricProperty.
				foreach (Statement* s, graph->bySubject.values(N->subject))
				{
					ASSERT(s->subject == N->subject);
					R << new Statement(N->object, s->predicate, s->object, Statements() << N << s);
				}

				foreach (Statement* s, graph->byPredicate.values(N->subject))
				{
					ASSERT(s->predicate == N->subject);
					R << new Statement(s->subject, N->object, s->object, Statements() << N << s);
				}

				foreach (Statement* s, graph->byObject.values(N->subject))
				{
					ASSERT(s->object == N->subject);
					R << new Statement(s->subject, s->predicate, N->object, Statements() << N << s);
				}
			}
			else if (N->predicate == equivalentProperty || N->predicate == subPropertyOf)
			{
				foreach (Statement* s, graph->byPredicate.values(N->subject))
				{
					ASSERT(s->predicate == N->subject);
		//			R << new Statement(N->subject, p->object, N->object, Statements() << N << p);
					R << new Statement(s->subject, N->object, s->object, Statements() << N << s);
				}
			}
			else if (N->predicate == inverseOf)
			{
				foreach (Statement* s, graph->byPredicate.values(N->subject))
				{
					ASSERT(s->predicate == N->subject);
		//			R << new Statement(N->object, p->object, N->subject, Statements() << N << p);
					R << new Statement(s->object, N->object, s->subject, Statements() << N << s);
				}
			}
			// TODO equivalentClass, subClassOf

			return R;
		}
	}
}
