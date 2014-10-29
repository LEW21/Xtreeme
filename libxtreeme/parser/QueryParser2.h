#include <boost/optional.hpp>
#include <vector>
#include "../expressions/Variable.h"
#include <libxtypes/URI.h>
#include "rtti_variant.h"

namespace Xtreeme
{
	using std::string;
	using std::vector;
	using boost::optional;
	using X::URI;

	struct Constraint {};

	namespace GraphPatterns
	{
		struct Basic
		{
		};

		struct Join
		{
			Variant a, b;
			Join(Variant a, Variant b): a(a), b(b) {}
		};

		struct LeftJoin
		{
			Variant a, b;
			LeftJoin(Variant a, Variant b): a(a), b(b) {}
		};

		struct Minus
		{
			Variant a, b;
			Minus(Variant a, Variant b): a(a), b(b) {}
		};

		struct Union
		{
			Variant a, b;
			Union(Variant a, Variant b): a(a), b(b) {}
		};

		struct Graph
		{
			URI graph;
			Variant data;
			Graph(URI graph, Variant data): graph(graph), data(data) {}
		};

		struct Service
		{
			bool silent;
			URI graph;
			Variant data;
			Service(bool silent, URI graph, Variant data): silent(silent), graph(graph), data(data) {}
		};

		struct Extend
		{
			Variable var;
			Expression exp;
			Variant data;
			Extend(Variable var, Expression exp, Variant data): var(var), exp(exp), data(data) {}
		};

		struct Filter
		{
			vector<Constraint> constraints;
			Variant data;
			Filter(vector<Constraint> constraints, Variant data): constraints(constraints), data(data) {}
		};
	}

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
		optional<GraphPatterns::Basic> tpl;

		// everywhere
		From from;
		optional<Variant> where; // optional in DESCRIBE, required in others.
		optional<int> limit;
		optional<int> offset;

		Query(Type t): type(t) {}
	};

	auto parseQuery() -> Query;
}
