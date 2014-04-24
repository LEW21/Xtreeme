#ifndef X_VariantAddOns_h
#define X_VariantAddOns_h

#include "X.h"

#include "MetaType.h"

#include <QDebug>

namespace X
{
	template <class T>
	X::Variant variant_createRuntime(const IRI& type, const T& value)
	{
		TypeID target = namedTypes[type];
		assert(target);
		assert(metaTypes[target]);
		try
		{
			return metaTypes[target]->create(value);
		}
		catch (std::bad_function_call&)
		{
			throw ConversionError(X::typeOf<T>::type, target);
		}
	}

	template <class T>
	T variant_cast(const X::Variant& v)
	{
		if (v.is<T>())
			return v.as<T>();

		TypeID target = X::typeOf<T>::type;
		try
		{
			return metaTypes[target]->create(v);
		}
		catch (std::bad_function_call&)
		{
			throw ConversionError(v.type, target);
		}
	}

	inline uint qHash(const X::Variant& v)
	{
		std::hash<X::Variant> hashfunc;
		return hashfunc(v);
	}
}

#endif
