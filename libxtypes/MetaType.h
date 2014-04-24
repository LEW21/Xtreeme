#ifndef X_MetaType_h
#define X_MetaType_h

#include <libxcore/Type.h>

#include "X.h"
#include "String.h"
#include "IRI.h"

#include <QHash>
#include <functional>
#include <libxcore/Variant.h>

#include <cassert>

namespace X
{
	class MetaType;
	extern TypeRegistry<MetaType*> metaTypes;

	struct ConversionError: public ConversionErrorBase
	{
		inline ConversionError(int f, int t)
			: ConversionErrorBase(f, t)
		{}

		operator String();
	};

	typedef std::function<Variant (const Variant&)> DynamicFunction;

//	QHash<IRI, QHash<const Type*, DynamicFunction>> functions;

	static QHash<IRI, int> namedTypes;

	class MetaType
	{
	public:
		IRI iri;

		QHash<int, DynamicFunction> constructors;

		inline MetaType(const IRI& i): iri(i)
		{}

		template <class T>
		inline Variant create(const T& param)
		{
			return constructors[typeOf<T>::type](param);
		}

		inline Variant create(const Variant& param)
		{
			return constructors[param.type](param);
		}
	};

	template <class F, class T>
	Variant vcast(const Variant& v)
	{
		return T(v.as<F>());
	}

	template <class F, class T>
	void bindCast()
	{
		MetaType* target = metaTypes[typeOf<T>::type];
		assert(target);
		target->constructors[typeOf<F>::type] = vcast<F, T>;
	}

	template <class A, class B>
	void bindCasts()
	{
		bindCast<A, B>();
		bindCast<B, A>();
	}

	/*	dynamic type:
	 *	int type = Type();
	 *	coreTypes[type] = coreTypes[X::typeOf<String>::type];
	 *	metaTypes[iri] = new MetaType(iri);*/
}

#endif
