#include "X.h"

#include "AutoRegister.h"

#include "Boolean.h"
#include "Binary.h"
#include "String.h"
#include "IRI.h"
#include "URI.h"
#include "Text.h"

namespace X
{
	template<> TypeID typeOf<Boolean>::type = newType();
	template<> TypeID typeOf<Binary>::type = newType();
	template<> TypeID typeOf<String>::type = newType();
	template<> TypeID typeOf<IRI>::type = newType();
	template<> TypeID typeOf<URI>::type = newType();
	template<> TypeID typeOf<Text>::type = newType();

	void init()
	{
		AutoRegister<Boolean, PlainType> reg_Boolean(X_NS u"Boolean");
		AutoRegister<Binary> reg_Binary(X_NS u"Binary");
		AutoRegister<String> reg_String(X_NS u"String");
		AutoRegister<IRI> reg_IRI(X_NS u"IRI");
		AutoRegister<URI> reg_URI(X_NS u"URI");
		AutoRegister<Text> reg_Text(X_NS u"Text");

		bindCasts<String, Boolean>();
		bindCasts<String, IRI>();
		bindCasts<String, Text>();
	}

	struct Initer
	{
		Initer() {init();}
	} initer;

}
