#ifndef Xtreeme_Statement_h
#define Xtreeme_Statement_h

#include "libxtreeme.h"

#include "Resource.h"
#include "Row.h"

namespace Xtreeme
{
	struct XTREEME_EXPORT Statement
	{
		Resource subject;
		Resource predicate;
		Resource object;
		Resource context;

		inline Statement() {}

		inline Statement(const Resource& S, const Resource& P, const Resource& O, const Resource& C = Resource())
			: subject(S)
			, predicate(P)
			, object(O)
			, context(C)
		{}

		inline Statement(const X::String&) {/*TODO*/}

		inline bool isValid() const
		{
			return subject.isValid() && predicate.isValid() && object.isValid() && context.isValid();
		}

		inline bool operator==(const Statement& other) const
		{
			return (subject == other.subject)
			    && (predicate == other.predicate)
			    && (object == other.object)
			    && (context == other.context);
		}
		inline bool operator!=(const Statement& other) const {return !(other == *this);}

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
