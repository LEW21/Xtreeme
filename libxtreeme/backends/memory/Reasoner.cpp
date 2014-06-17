#include "Reasoner.h"

#include "../../RDF.h"
#include "../../OWL.h"

#include "Data.h"

#define ASSERT(bool) Q_ASSERT(bool)

const auto instanceOf         = RDF::type;
const auto sameAs             = OWL::sameAs;
const auto inverseOf          = OWL::inverseOf;
const auto equivalentProperty = OWL::equivalentProperty;
const auto subPropertyOf      = RDF::subPropertyOf;
const auto equivalentClass    = OWL::equivalentClass;
const auto subClassOf         = RDF::subClassOf;

const auto TransitiveProperty = OWL::TransitiveProperty;
const auto SymmetricProperty  = OWL::SymmetricProperty;

using namespace std;

namespace Xtreeme
{
	namespace Memory
	{
		std::vector<InferredStatement> think(Data& data, Statement N)
		{
			auto R = std::vector<InferredStatement>{}; // reasoned statements

			auto sameAs             = data[::sameAs];
			auto inverseOf          = data[::inverseOf];
			auto equivalentProperty = data[::equivalentProperty];
			auto subPropertyOf      = data[::subPropertyOf];
			auto instanceOf         = data[::instanceOf];
			auto TransitiveProperty = data[::TransitiveProperty];
			auto SymmetricProperty  = data[::SymmetricProperty];

			// Check for special things related to our subject.
			for (auto id : data.find(N.subject.id, sameAs.id, 0, 0))
			{
				auto S_sameAs = data.resource(id).as<Statement>();

				R.emplace_back(Statement{S_sameAs.object, N.predicate, N.object}, std::vector<Statement>{N, S_sameAs});
			}

			// Check for special things related to our predicate.
			for (auto pID : data.find(N.predicate.id, 0, 0, 0))
			{
				auto p = data.resource(pID).as<Statement>();

				if (p.predicate == sameAs || p.predicate == equivalentProperty || p.predicate == subPropertyOf)
				{
					R.emplace_back(Statement(N.subject, p.object, N.object), std::vector<Statement>{N, p});
				}
				else if (p.predicate == inverseOf)
				{
					R.emplace_back(Statement(N.object, p.object, N.subject), std::vector<Statement>{N, p});
				}
				else if (p.predicate == instanceOf)
				{
					if (p.object == TransitiveProperty)
					{
						// We need A-Y-C for every A-Y-B B-Y-C pair.
						// If we are A-Y-B:
						for (auto s : data.find(N.object, N.predicate, {}, {}))
							R.emplace_back(Statement(N.subject, N.predicate, s.object), std::vector<Statement>{N, p, s});
						// If we are B-Y-C:
						for (auto s : data.find({}, N.predicate, N.subject, {}))
							R.emplace_back(Statement(s.subject, N.predicate, N.object), std::vector<Statement>{N, p, s});
					}
					else if (p.object == SymmetricProperty)
					{
						R.emplace_back(Statement(N.object, N.predicate, N.subject), std::vector<Statement>{N, p});
					}
				}
			}

			// Check for special things related to our object.
			for (auto id : data.find(N.object.id, sameAs.id, 0, 0))
			{
				auto O_sameAs = data.resource(id).as<Statement>();

				R.emplace_back(Statement{N.subject, N.predicate, O_sameAs.object}, std::vector<Statement>{N, O_sameAs});
			}

			// OKAY, and now the other way.

			if (N.predicate == instanceOf)
			{
				if (N.object == TransitiveProperty)
				{
					// OK, so this is a transitive property!
					// We need to create A-Y-C for every s(A-Y-B) z(B-Y-C) pair.
					for (auto s : data.find({}, N.subject, {}, {}))
						for (auto z : data.find(s.object, N.subject, {}, {}))
							R.emplace_back(Statement{s.subject, N.subject, z.object}, vector<Statement>{N, s, z});
				}
				else if (N.object == SymmetricProperty)
				{
					// OK, so this is a symmetric property!
					// We need to copy all the statements using it in a reversed way.
					for (auto s : data.find({}, N.subject, {}, {}))
						R.emplace_back(Statement{s.object, N.subject, s.subject}, vector<Statement>{N, s});
				}
			}
			else if (N.predicate == sameAs)
			{
				// Is currently added property sameAs? If so, then copy everything!
				// There is no difference in which way will we copy it - everything will be copied in the second way by reversed sameAs created before by the effect of SymmetricProperty.
				for (auto s : data.find(N.subject, {}, {}, {}))
					R.emplace_back(Statement{N.object, s.predicate, s.object}, vector<Statement>{N, s});

				for (auto s : data.find({}, N.subject, {}, {}))
					R.emplace_back(Statement{s.subject, N.object, s.object}, vector<Statement>{N, s});

				for (auto s : data.find({}, {}, N.subject, {}))
					R.emplace_back(Statement{s.subject, s.predicate, N.object}, vector<Statement>{N, s});
			}
			else if (N.predicate == equivalentProperty || N.predicate == subPropertyOf)
			{
				for (auto s : data.find({}, N.subject, {}, {}))
					R.emplace_back(Statement{s.subject, N.object, s.object}, vector<Statement>{N, s});
			}
			else if (N.predicate == inverseOf)
			{
				for (auto s : data.find({}, N.subject, {}, {}))
					R.emplace_back(Statement{s.object, N.object, s.subject}, vector<Statement>{N, s});
			}
			// TODO equivalentClass, subClassOf

			// Remove useless ideas, like A => A.
			auto Rbak = move(R);
			R = {};
			for (auto r : Rbak)
			{
				bool recursive = false;
				for (auto reason : r.inferredFrom)
					if (r.s.subject == reason.subject && r.s.predicate == reason.predicate && r.s.object == reason.object)
						recursive = true;
				if (!recursive)
					R.emplace_back(r);
			}

			return R;
		}
	}
}
