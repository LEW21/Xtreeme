#include <boost/optional.hpp>
#include <vector>
#include "../expressions/Variable.h"
#include <libxtypes/URI.h>

namespace Xtreeme
{
	using std::string;
	using std::vector;
	using boost::optional;
	using X::URI;

	struct GGP {};

	struct parse_error: public std::domain_error
	{
		explicit parse_error(const string& what_arg): domain_error(what_arg) {}
	};

	using ParseError = parse_error;

	struct Binding
	{
		Variable name;
		Expression value;

		Binding(Variable v): name(v), value(v) {}
		Binding(Variable v, Expression e): name(v), value(e) {}
		Binding(URI u): value(u) {}
	};

	struct From
	{
		vector<URI> defaultGraphs;
		vector<URI> namedGraphs;
	};

	struct Query
	{
		enum Type {
			Select,
			Construct,
			Describe,
			Ask
		} type;

		// SELECT
		bool distinct = false;
		bool reduced = false;

		// SELECT, DESCRIBE
		optional<vector<Binding>> projection;

		// CONSTRUCT
		optional<GGP> tpl;

		// everywhere
		From from;
		optional<GGP> where; // optional in DESCRIBE, required in others.
		optional<int> limit;
		optional<int> offset;

		Query(Type t): type(t) {}
	};

	auto parseQuery() -> Query;
}
