#ifndef X_AutoRegister_h
#define X_AutoRegister_h

#include <libxcore/PlainType.h>
#include <libxcore/ComplexType.h>

#include "MetaType.h"

namespace X
{
	template <class T, class CoreType = ComplexType<T>> struct AutoRegister
	{
		AutoRegister(const char16_t* iri)
		{
			coreTypes[typeOf<T>::type] = new CoreType();
			metaTypes[typeOf<T>::type] = new MetaType(X::IRI(iri));
		}
	};
}

#endif
