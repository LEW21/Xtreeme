#ifndef Xtreeme_debug_h
#define Xtreeme_debug_h

#include "Resource.h"
#include "Statement.h"
#include "StatementPattern.h"
#include "RDF.h"
#include "DC.h"
#include "OWL.h"
#include "XSD.h"
#include "Row.h"
#include "Solution.h"

#include "expressions/Constant.h"
#include "expressions/Variable.h"

inline QDebug operator<<(QDebug debug, const Xtreeme::Resource& node)
{
	debug << node.asTurtle().toUtf8().constData();

/*	switch (node.type())
	{
		case Xtreeme::Resource::Named:
		{
			QString iri = Xtreeme::Named(node).uri().toString();
			if (iri.startsWith(RDF::BaseRDF))
				debug.nospace() << "rdf:" << iri.mid(RDF::BaseRDF.size()).toUtf8().data();
			else if (iri.startsWith(RDF::BaseRDFS))
				debug.nospace() << "rdfs:" << iri.mid(RDF::BaseRDFS.size()).toUtf8().data();
			else if (iri.startsWith(DC::Base))
				debug.nospace() << "dc:" << iri.mid(DC::Base.size()).toUtf8().data();
			else if (iri.startsWith(OWL::Base))
				debug.nospace() << "owl:" << iri.mid(OWL::Base.size()).toUtf8().data();
			else if (iri.startsWith(XSD::Base))
				debug.nospace() << "xsd:" << iri.mid(XSD::Base.size()).toUtf8().data();
			else
				debug.nospace() << "<" << iri.toUtf8().constData() << ">";
		}
		break;

		case Xtreeme::Resource::Typed:
		{
			Xtreeme::Typed typed(node);
			debug.nospace() << typed.value() << "^^" << typed.type();
		}
		break;

		case Xtreeme::Resource::Plain:
		{
			Xtreeme::Plain plain(node);
			debug.nospace() << plain.value() << "@" << plain.lang().toUtf8().constData();
		}
		break;

		case Xtreeme::Resource::Statement:
			debug.nospace() << '(' << Xtreeme::Statement(node) << ')';
		break;

		case Xtreeme::Resource::Blank:
			debug.nospace() << "_:";
		break;

		case Xtreeme::Resource::Invalid:
			debug.nospace() << '?';
		break;

		case Xtreeme::Resource::XResource:
			debug.nospace() << Xtreeme::XResource(node).asTurtle().toUtf8().constData();
		break;
	}*/

	return debug.space();
}

inline QDebug operator<<(QDebug debug, const Xtreeme::Expression& e)
{
	if (e.isConstant())
		debug << Xtreeme::Constant(e).resource();
	else if (e.isVariable())
		debug << "?" + Xtreeme::Variable(e).name();
	else
		debug << "??";
	
	return debug;
}

inline QDebug operator<<(QDebug debug, const Xtreeme::Statement& s)
{
	debug << s.subject << s.predicate << s.object << s.context << ".";

	return debug;
}

inline QDebug operator<<(QDebug debug, const Xtreeme::StatementPattern& s)
{
	debug << s.subject << s.predicate << s.object << s.context << ".";

	return debug;
}

inline QDebug operator<<(QDebug debug, const QList<Xtreeme::Statement>& S)
{
	foreach (const Xtreeme::Statement& s, S)
	{
		debug << s;
	}

	return debug;
}

inline QDebug operator<<(QDebug debug, const Xtreeme::Row& s)
{
	foreach (const Xtreeme::Resource& res, s)
	{
		debug << res;
	}

	return debug;
}

inline QDebug operator<<(QDebug debug, const Xtreeme::Solution& s)
{
	foreach (const Xtreeme::Row& row, s.rows())
	{
		debug << row << "\n";
	}

	return debug;
}

#endif
