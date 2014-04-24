#ifndef Xtreeme_RDF_h
#define Xtreeme_RDF_h

#include <QUrl>

namespace RDF
{
	const QString BaseRDF("http://www.w3.org/1999/02/22-rdf-syntax-ns#");
	const QString BaseRDFS("http://www.w3.org/2000/01/rdf-schema#");

	// 2. Classes
	const QUrl Resource  (BaseRDFS + "Resource");
	const QUrl Class     (BaseRDFS + "Class");
	const QUrl Literal   (BaseRDFS + "Literal");
	const QUrl Datatype  (BaseRDFS + "Datatype");
	const QUrl XMLLiteral(BaseRDF  + "XMLLiteral");
	const QUrl Property  (BaseRDF  + "Property");

	// 3. Properties
	const QUrl range        (BaseRDFS + "range");
	const QUrl domain       (BaseRDFS + "domain");
	const QUrl type         (BaseRDF  + "type");
	const QUrl subClassOf   (BaseRDFS + "subClassOf");
	const QUrl subPropertyOf(BaseRDFS + "subPropertyOf");
	const QUrl label        (BaseRDFS + "label");
	const QUrl comment      (BaseRDFS + "comment");

	// 5.1 Container Classes and Properties
	const QUrl Container (BaseRDFS + "Container");
	const QUrl Bag       (BaseRDF  + "Bag");
	const QUrl Seq       (BaseRDF  + "Seq");
	const QUrl Alt       (BaseRDF  + "Alt");
	const QUrl ContainerMembershipProperty(BaseRDFS + "ContainerMembershipProperty");
	const QUrl member    (BaseRDFS + "member");

	// 5.2 RDF Collections
	const QUrl List      (BaseRDF  + "List");
	const QUrl first     (BaseRDF  + "first");
	const QUrl rest      (BaseRDF  + "rest");
	const QUrl nil       (BaseRDF  + "nil");

	// 5.3 Reification Vocabulary
	const QUrl Statement (BaseRDF  + "Statement");
	const QUrl subject   (BaseRDF  + "subject");
	const QUrl predicate (BaseRDF  + "predicate");
	const QUrl object    (BaseRDF  + "object");

	// 5.4 Utility Properties
	const QUrl seeAlso    (BaseRDFS + "seeAlso");
	const QUrl isDefinedBy(BaseRDFS + "isDefinedBy");
	const QUrl value      (BaseRDF  + "value");
}

#endif
