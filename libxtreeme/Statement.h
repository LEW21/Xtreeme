#ifndef Xtreeme_Statement_h
#define Xtreeme_Statement_h

#include "libxtreeme.h"

#include "Resource.h"
#include "Row.h"
#include "Quad.h"

namespace Xtreeme
{
	struct XTREEME_EXPORT Statement: public Quad<Resource>
	{
		using Quad::Quad;
		inline Statement() {}
		inline Statement(const X::String&) {/*TODO*/}

		inline bool isValid() const
		{
			return subject.isValid() && predicate.isValid() && object.isValid() && context.isValid();
		}

		inline bool matches(const Statement& pattern) const
		{
			return (!pattern.subject.isValid()   || subject == pattern.subject)
			    && (!pattern.predicate.isValid() || predicate == pattern.predicate)
			    && (!pattern.object.isValid()    || object == pattern.object)
			    && (!pattern.context.isValid()   || context == pattern.context);
		}

		inline operator Row() const
		{
			return {X::Variant(*this), subject, predicate, object, context};
		}

		QString asTurtle() const;
	};

	uint qHash(const Statement&);
}

namespace std
{
	template<> struct hash<Xtreeme::Statement>;
}

#include <QMetaType>
Q_DECLARE_METATYPE(Xtreeme::Statement)

namespace X
{
	template<> struct isX<Xtreeme::Statement> : public std::true_type {};
	template<> struct isStorable<Xtreeme::Statement> : public std::true_type {};
	template<> struct isTemporary<Xtreeme::Statement> : public std::false_type {};
}

#endif
