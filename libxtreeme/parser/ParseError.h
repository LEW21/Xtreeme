#ifndef Xtreeme_ParseError_h
#define Xtreeme_ParseError_h

#include "../libxtreeme.h"

#include <QList>
#include <QString>

namespace Xtreeme
{
	struct XTREEME_EXPORT ParseError
	{
		enum Component
		{
			Tokenizer,
			TokenParser,
			TurtleParser,
			QueryParser
		};

		ParseError(Component, const QString& message);

		Component component;
		QString message;

		inline operator QString()
		{
			QString com;
			switch (component)
			{
				case Tokenizer:
					com = "Tokenizer";
				break;

				case TokenParser:
					com = "TokenParser";
				break;

				case TurtleParser:
					com = "TurtleParser";
				break;

				case QueryParser:
					com = "QueryParser";
				break;
			}

			return com + ": " + message;
		}
	};
}

#endif
