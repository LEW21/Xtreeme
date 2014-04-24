#ifndef Xtreeme_Memory_Solve_h
#define Xtreeme_Memory_Solve_h

#include "../Command.h"
#include "../../../DataStream.h"

namespace Xtreeme
{
	class Header;
	class Row;

	namespace Memory
	{
		class SolveP;
		class Solve: public Command
		{
			SolveP* p;

		public:
			Solve();

			void bind(const Xtreeme::Command* that, QHash<const Xtreeme::Command*, Command*>* bindings);

			void inputHeader(const Xtreeme::Header&);
			void input(const Xtreeme::Row&);
			void inputEnd();

			DataStreamInfo output;
			DataStreamInfo* outputInfo(int id);
		};
	}
}

#endif
