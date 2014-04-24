#ifndef Xtreeme_Tokenizer_h
#define Xtreeme_Tokenizer_h

#include "Token.h"

#include <libxcore/Object.h>

namespace Xtreeme
{
	class Tokenizer: public X::Object
	{
		QString buffer;

	public:
		void tokenizeData(const QString& data);
		void end();
		
		X::Signal<Token> token;
		X::Signal<> finished;
	};
}

#endif
