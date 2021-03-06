#include "Resource.h"

#include "Statement.h"

#include <libxtypes/Text.h>

#include <QDebug>

namespace Xtreeme
{
	static auto quote(QString s) -> QString
	{
		return "\"" + s.replace('"', "\\\"") + "\"";
	}

	QString Resource::asTurtle() const
	{
		if (!isValid())
			return QString();

//		QString turtle = variant->is<X::IRI>() ? QS("<") : QS("\"");

		if (value.is<Statement>())
		{
			auto s = value.as<Statement>();
			return quote(s.subject.asTurtle() + " " + s.predicate.asTurtle() + " " + s.object.asTurtle() + " " + s.context.asTurtle()) + "^^Statement"; // TODO delete
			return quote(s.subject.asTurtle() + " " + s.predicate.asTurtle() + " " + s.object.asTurtle() + " " + s.context.asTurtle()) + "^^<http://xtreeme.org/statement/>";
		}

		QString turtle;
		QString v;
		try
		{
			v = QString(X::variant_cast<X::String>(value));
		}
		catch (X::ConversionError& e)
		{
			qDebug() << QString(X::String(e));
			throw;
		}
		turtle.reserve(2 * v.size());

		if (value.is<X::IRI>())
		{
			if (v.startsWith(QLatin1Char('\0')))
				return "_:" + v.mid(2);

			return v.mid(v.lastIndexOf(QRegExp("[/#]"))+1); // TODO drop this
			turtle += QS("<");
		}
		else
		{
			turtle += QS("\"");
		}

		int i = 0;
		for (int N = v.size(); i < N; i++)
		{
			switch (v[i].unicode())
			{
				case '\\':
					turtle += "\\\\";
				break;

				case '\t':
					turtle += "\\t";
				break;

				case '\n':
					turtle += "\\n";
				break;

				case '\r':
					turtle += "\\r";
				break;

				case '>':
					if (!value.is<X::IRI>())
						goto def;

					turtle += "\\>";
				break;

				case '"':
					if (value.is<X::IRI>())
						goto def;

					turtle += "\\\"";
				break;

				default:
				def:
					turtle += v[i];
				break;
			}
		}

		turtle += value.is<X::IRI>() ? QC('>') : QC('\"');

		if (value.is<X::Text>())
		{

		}
		else if (!value.is<X::IRI>() && !value.is<X::String>())
		{
			turtle += QS("^^<") + QString(X::metaTypes[value.type]->iri) + QS(">");
		}

		return turtle;
	}
}
