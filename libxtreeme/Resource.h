#ifndef Xtreeme_Resource_h
#define Xtreeme_Resource_h

#include "libxtreeme.h"

#include <libxtypes/Variant.h>

namespace Xtreeme
{
	struct XTREEME_EXPORT Resource
	{
		typedef quint64 ID;

		ID id;
		X::Variant value;

		inline Resource(): id(0) {}

		inline Resource(ID i, const X::Variant& v): id(i), value(v) {}
		inline Resource(ID i, X::Variant&& v): id(i), value(std::move(v)) {}

		inline Resource(const X::Variant& v): id(0), value(v) {}
		inline Resource(X::Variant&& v): id(0), value(std::move(v)) {}

		inline operator X::Variant() const {return value;}

		inline bool isValid() const {return value.isValid();}

		inline bool operator==(const Resource& other) const {return value == other.value;}
		inline bool operator!=(const Resource& other) const {return value != other.value;}

		QString asTurtle() const;

// think-about:
//		QList<Resource> operator[](const Node& predicate) const;
//		QHash<Resource, Resource> properties() const;
	};
}

#endif
