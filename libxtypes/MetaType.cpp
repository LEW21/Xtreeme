#ifndef QT4
#define QT4
#endif

#include "MetaType.h"

namespace X
{
	TypeRegistry<MetaType*> metaTypes;

	template<>
	std::vector<MetaType*>& TypeRegistry<MetaType*>::types()
	{
		static std::vector<MetaType*> types;
		return types;
	}

//	QHash<IRI, int> namedTypes;

	ConversionErrorBase::ConversionErrorBase(TypeID f, TypeID t) throw(): from(f), to(t) {}

	ConversionError::operator String()
	{
		return QString(QLatin1String("ConversionError: Conversion from %1 to %2 failed.")).arg(QString(metaTypes[from]->iri)).arg(QString(metaTypes[to]->iri));
	}
}
