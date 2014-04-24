#ifndef Xtreeme_Command_h
#define Xtreeme_Command_h

#include "Resource.h"
#include <QVector>
#include "Row.h"
#include "RowPattern.h"
#include "Expression.h"
#include "expressions/Variable.h"
#include "DataStream.h"

namespace Xtreeme
{
	struct Command
	{
		enum Type {
			DB,
			Dataset,
			Match,
			Solve,
			Project,
			Distinct,
			Reduced,
			Delete,
			Insert,
			InputStream,
			OutputStream
		} type;

	private:
		inline Command() {};
		inline Command(const Command&) {};

	protected:
		inline Command(Type t): type(t) {}
	};

	struct Stream
	{
		const Command* creator;
		uint id;

		inline Stream(const Command* c, uint i): creator(c), id(i) {}
		inline Stream(): creator(0), id(0) {}
	};

	struct DB: public Command
	{
		inline DB(): Command(Command::DB) {}

		inline Stream data() const {return {this, 0};}
	};

	struct Dataset: public Command
	{
		QVector<Resource> defaultGraph;
		QVector<Resource> namedGraphs;

		inline Dataset(): Command(Command::Dataset) {}

		inline Stream data() const {return {this, 0};}
	};

	struct Match: public Command
	{
		Row pattern;

		inline Match(const Row& _pattern, const Stream& i)
			: Command(Command::Match)
			, pattern(_pattern)
			, input(i)
		{}

		Stream input;
		inline Stream output() const {return {this, 0};}
	};

	struct Solve: public Command
	{
		QVector<RowPattern> pattern;

		inline Solve(const QVector<RowPattern>& p, const Stream& i)
			: Command(Command::Solve)
			, pattern(p)
			, input(i)
		{}

		Stream input;
		inline Stream output() const {return {this, 0};}
	};

	struct Binding
	{
		Variable name;
		Expression value;
	};

	struct Project: public Command
	{
		QVector<Binding> bindings;

		inline Project(const QVector<Binding>& b, const Stream& i)
			: Command(Command::Project)
			, bindings(b)
			, input(i)
		{}

		Stream input;
		inline Stream output() const {return {this, 0};}
	};

	struct Distinct: public Command
	{
		inline Distinct(const Stream& i)
			: Command(Command::Distinct)
			, input(i)
		{}

		Stream input;
		inline Stream output() const {return {this, 0};}
	};

	struct Reduced: public Command
	{
		inline Reduced(const Stream& i)
			: Command(Command::Reduced)
			, input(i)
		{}

		Stream input;
		inline Stream output() const {return {this, 0};}
	};

	// Construct is a projection to ID S P O G

	struct Delete: public Command
	{
		inline Delete(const Stream& i)
			: Command(Command::Delete)
			, input(i)
		{}

		Stream input;
	};

	struct Insert: public Command
	{
		inline Insert(const Stream& i)
			: Command(Command::Insert)
			, input(i)
		{}

		Stream input;
	};

	struct DataStreamBase: public Command
	{
		DataStream* stream;

	protected:
		inline DataStreamBase(Type type): Command(type), stream(0) {}
	};

	struct InputStream: public DataStreamBase
	{
		inline InputStream(): DataStreamBase(Command::InputStream) {}

		inline Stream toServer() const {return {this, 0};}
	};

	struct OutputStream: public DataStreamBase
	{
		inline OutputStream(const Stream& i)
			: DataStreamBase(Command::OutputStream)
			, toClient(i)
		{}

		Stream toClient;
	};
}

#endif
