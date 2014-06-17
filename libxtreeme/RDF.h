#ifndef Xtreeme_RDF_h
#define Xtreeme_RDF_h

#include <libxtypes/IRI.h>

namespace RDF
{
	const QString BaseRDF("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
	const QString BaseRDFS("http://www.w3.org/2000/01/rdf-schema#");

	// 2. Classes
	const X::IRI Resource  (BaseRDFS + "Resource");
	const X::IRI Class     (BaseRDFS + "Class");
	const X::IRI Literal   (BaseRDFS + "Literal");
	const X::IRI Datatype  (BaseRDFS + "Datatype");
	const X::IRI XMLLiteral(BaseRDF  + "XMLLiteral");
	const X::IRI Property  (BaseRDF  + "Property");

	// 3. Properties
	const X::IRI range        (BaseRDFS + "range");
	const X::IRI domain       (BaseRDFS + "domain");
	const X::IRI type         (BaseRDF  + "type");
	const X::IRI subClassOf   (BaseRDFS + "subClassOf");
	const X::IRI subPropertyOf(BaseRDFS + "subPropertyOf");
	const X::IRI label        (BaseRDFS + "label");
	const X::IRI comment      (BaseRDFS + "comment");

	// 5.1 Container Classes and Properties
	const X::IRI Container (BaseRDFS + "Container");
	const X::IRI Bag       (BaseRDF  + "Bag");
	const X::IRI Seq       (BaseRDF  + "Seq");
	const X::IRI Alt       (BaseRDF  + "Alt");
	const X::IRI ContainerMembershipProperty(BaseRDFS + "ContainerMembershipProperty");
	const X::IRI member    (BaseRDFS + "member");

	// 5.2 RDF Collections
	const X::IRI List      (BaseRDF  + "List");
	const X::IRI first     (BaseRDF  + "first");
	const X::IRI rest      (BaseRDF  + "rest");
	const X::IRI nil       (BaseRDF  + "nil");

	// 5.3 Reification Vocabulary
	const X::IRI Statement (BaseRDF  + "Statement");
	const X::IRI subject   (BaseRDF  + "subject");
	const X::IRI predicate (BaseRDF  + "predicate");
	const X::IRI object    (BaseRDF  + "object");

	// 5.4 Utility Properties
	const X::IRI seeAlso    (BaseRDFS + "seeAlso");
	const X::IRI isDefinedBy(BaseRDFS + "isDefinedBy");
	const X::IRI value      (BaseRDF  + "value");
}

#endif
