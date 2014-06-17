#pragma once

#include "libxtreeme.h"

namespace Xtreeme
{
	template <typename T>
	struct XTREEME_EXPORT Quad
	{
		T subject;
		T predicate;
		T object;
		T context;

		inline Quad() {}

		inline Quad(const Resource& S, const Resource& P, const Resource& O, const Resource& C = Resource())
			: subject(S)
			, predicate(P)
			, object(O)
			, context(C)
		{}
	};

	template <typename T>
	inline bool operator==(const Quad<T>& a, const Quad<T>& b)
	{
		return (a.subject == b.subject)
			&& (a.predicate == b.predicate)
			&& (a.object == b.object)
			&& (a.context == b.context);
	}
	template <typename T>
	inline bool operator!=(const Quad<T>& a, const Quad<T>& b) {return !(a == b);}
}
