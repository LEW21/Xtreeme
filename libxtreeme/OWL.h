#ifndef Xtreeme_OWL_h
#define Xtreeme_OWL_h

#include <libxtypes/IRI.h>

namespace OWL
{
	const QString Base("http://www.w3.org/2002/07/owl#");

	const X::IRI Class           (Base + "Class");
	const X::IRI DeprecatedClass (Base + "DeprecatedClass");

	const X::IRI Ontology (Base + "Ontology");

	const X::IRI Thing   (Base + "Thing");
	const X::IRI Nothing (Base + "Nothing");

	const X::IRI ObjectProperty            (Base + "ObjectProperty");
	const X::IRI DatatypeProperty          (Base + "DatatypeProperty");
	const X::IRI TransitiveProperty        (Base + "TransitiveProperty");
	const X::IRI SymmetricProperty         (Base + "SymmetricProperty");
	const X::IRI FunctionalProperty        (Base + "FunctionalProperty");
	const X::IRI InverseFunctionalProperty (Base + "InverseFunctionalProperty");
	const X::IRI AnnotationProperty        (Base + "AnnotationProperty");
	const X::IRI OntologyProperty          (Base + "OntologyProperty");
	const X::IRI DeprecatedProperty        (Base + "DeprecatedProperty");

	const X::IRI DataRange                 (Base + "DataRange");

	const X::IRI equivalentClass    (Base + "equivalentClass");
	const X::IRI disjointWith       (Base + "disjointWith");
	const X::IRI equivalentProperty (Base + "equivalentProperty");
	const X::IRI sameAs             (Base + "sameAs");
	const X::IRI differentFrom      (Base + "differentFrom");
	const X::IRI AllDifferent       (Base + "AllDifferent");
	const X::IRI distinctMembers    (Base + "distinctMembers");
	const X::IRI unionOf            (Base + "unionOf");
	const X::IRI intersectionOf     (Base + "intersectionOf");
	const X::IRI complementOf       (Base + "complementOf");
	const X::IRI oneOf              (Base + "oneOf");
	const X::IRI inverseOf          (Base + "inverseOf");

	const X::IRI Restriction        (Base + "Restriction");
	const X::IRI onProperty         (Base + "onProperty");
	const X::IRI allValuesFrom      (Base + "allValuesFrom");
	const X::IRI hasValue           (Base + "hasValue");
	const X::IRI someValuesFrom     (Base + "someValuesFrom");
	const X::IRI minCardinality     (Base + "minCardinality");
	const X::IRI maxCardinality     (Base + "maxCardinality");
	const X::IRI cardinality        (Base + "cardinality");

	const X::IRI versionInfo            (Base + "versionInfo");
	const X::IRI imports                (Base + "imports");
	const X::IRI priorVersion           (Base + "priorVersion");
	const X::IRI backwardCompatibleWith (Base + "backwardCompatibleWith");
	const X::IRI incompatibleWith       (Base + "incompatibleWith");
}

#endif
