#include "QueryParser2.h"

namespace Xtreeme
{
using namespace GraphPatterns;

inline auto parseSelectClause() -> Query;
inline auto parseWhereClause() -> Variant;
inline auto parseSolutionModifier(Query&) -> void;
inline auto parseValuesClause(Query&) -> void;
inline auto parseGroupGraphPattern() -> Variant;
inline auto parseDataBlock() -> Variant;
inline auto parseConstraint() -> Constraint;
inline auto parseExpression() -> Expression;
inline auto parseVarOrIri() -> URI;
inline auto parseTriplesBlockNullable() -> Basic;

auto match(const char*)
{
}

auto try_match(const char*)
{
	return true;
}

auto is(const char*)
{
	return true;
}

template <typename T>
auto is()
{
	return true;
}

template <typename T>
auto read()
{
	return T{};
}

inline auto SelectQuery()    { return Query(Query::Select); }
inline auto ConstructQuery() { return Query(Query::Construct); }
inline auto DescribeQuery()  { return Query(Query::Describe); }
inline auto AskQuery()       { return Query(Query::Ask); }

inline auto parseTriplesTemplate()
{
	// TODO report error if this TriplesBlock is not a TriplesTemplate.
	return parseTriplesBlockNullable();
}

auto parseSubSelect()
{
	auto query = parseSelectClause();
	query.where = parseWhereClause();
	parseSolutionModifier(query);
	parseValuesClause(query);
	return query;
}

auto parseGraphPatternNotTriples(Variant ggp) -> Variant
{
	if (is("{"))
	{
		auto tmp = parseGroupGraphPattern();
		while (try_match("UNION"))
			tmp = Union(tmp, parseGroupGraphPattern());
		return Join(ggp, tmp);
	}

	if (try_match("OPTIONAL"))
		return LeftJoin(ggp, parseGroupGraphPattern());

	if (try_match("MINUS"))
		return Minus(ggp, parseGroupGraphPattern());

	if (try_match("GRAPH"))
		return Join(ggp, Graph(parseVarOrIri(), parseGroupGraphPattern()));

	if (try_match("SERVICE"))
		return Join(ggp, Service(try_match("SILENT"), parseVarOrIri(), parseGroupGraphPattern()));

	if (try_match("FILTER"))
		throw ParseError("FILTER is handled in parseGroupGraphPatternSub.");

	if (try_match("BIND"))
	{
		match("(");
		auto exp = parseExpression();
		match("AS");
		auto var = read<Variable>();
		return Extend(var, exp, ggp);
	}

	if (try_match("VALUES"))
		return Join(ggp, parseDataBlock());
}

auto parseGroupGraphPatternSub()
{
	auto filters = vector<Constraint>{};

	auto ggp = Variant{parseTriplesBlockNullable()};

	while (is("{") || is("OPTIONAL") || is("MINUS") || is("GRAPH") || is("SERVICE") || is("BIND") || is("VALUES"))
	{
		if (try_match("FILTER"))
			filters.emplace_back(parseConstraint());
		else
			ggp = parseGraphPatternNotTriples(ggp);
		(void) try_match(".");

		ggp = Join(ggp, parseTriplesBlockNullable());
	}

	return Filter(filters, ggp);
}

auto parseGroupGraphPattern() -> Variant
{
	match("{");
	auto ggp = is("SELECT") ? Variant{parseSubSelect()} : Variant{parseGroupGraphPatternSub()};
	match("}");
	return ggp;
}

inline auto parseSelectClause() -> Query
{
	match("SELECT");
	auto query = SelectQuery();

	if (try_match("DISTINCT"))
		query.distinct = true;
	else if (try_match("REDUCED"))
		query.reduced = true;

	if (!try_match("*"))
	{
		query.projection = vector<Binding>{};

		do
		{
			if (is<Variable>())
				query.projection->emplace_back(read<Variable>());
			else if (try_match("("))
			{
				auto expr = parseExpression();
				match("AS");
				query.projection->emplace_back(read<Variable>(), expr);
			}
			else
				throw ParseError("Expected * or var or (expr AS var).");
		}
		while (is<Variable>() || is("("));
	}

	return query;
}

inline auto parseDatasetClauses()
{
	From from;
	while (try_match("FROM"))
	{
		if (is<URI>())
			from.defaultGraphs.emplace_back(read<URI>());
		else if (try_match("NAMED"))
			from.namedGraphs.emplace_back(read<URI>());
		else
			throw ParseError("Expected uri or NAMED.");
	}
	return from;
}

inline auto parseWhereClause() -> Variant
{
	(void) try_match("WHERE");

	return parseGroupGraphPattern();
}

inline auto parseSolutionModifier(Query& query) -> void
{
	if (try_match("GROUP"))
	{
		match("BY");

		// TODO
		throw ParseError("GROUP BY is not yet supported.");
	}

	if (try_match("HAVING"))
	{
		// TODO
		throw ParseError("HAVING is not yet supported.");
	}

	if (try_match("ORDER"))
	{
		match("BY");

		// TODO
		throw ParseError("ORDER BY is not yet supported.");
	}

	if (try_match("LIMIT"))
	{
		query.limit = read<int>();

		if (try_match("OFFSET"))
			query.offset = read<int>();
	}
	else if (try_match("OFFSET"))
	{
		query.offset = read<int>();

		if (try_match("LIMIT"))
			query.limit = read<int>();
	}
}

auto parseValuesClause()
{
	if (try_match("VALUES"))
	{
		// TODO
		throw ParseError("VALUES is not yet supported.");
	}
}

inline auto parseSelectQuery()
{
	auto query = parseSelectClause();
	query.from  = parseDatasetClauses();
	query.where = parseWhereClause();

	parseSolutionModifier(query);
	return query;
}

inline auto parseConstructQuery()
{
	match("CONSTRUCT");
	auto query = ConstructQuery();

	if (is("{"))
	{
		match("{");
		query.tpl = parseTriplesTemplate();
		match("}");
		query.from  = parseDatasetClauses();
		query.where = parseWhereClause();
	}
	else if (is("FROM") || is("WHERE"))
	{
		query.from = parseDatasetClauses();
		match("WHERE");
		match("{");
		query.tpl = parseTriplesTemplate();
		query.where = query.tpl;
		match("}");
	}
	else
		throw ParseError("Expected { or FROM or WHERE.");

	parseSolutionModifier(query);
	return query;
}

inline auto parseDescribeQuery()
{
	match("DESCRIBE");
	auto query = DescribeQuery();

	if (!try_match("*"))
	{
		query.projection = vector<Binding>{};

		do
		{
			if (is<Variable>())
				query.projection->emplace_back(read<Variable>());
			else if (is<URI>())
				query.projection->emplace_back(read<URI>());
			else
				throw ParseError("Expected var or uri.");
		}
		while (is<Variable>() || is<URI>());
	}

	query.from = parseDatasetClauses();
	if (is("WHERE") || is("{"))
		query.where = parseWhereClause();

	parseSolutionModifier(query);
	return query;
}

inline auto parseAskQuery()
{
	match("ASK");
	auto query = AskQuery();

	query.from  = parseDatasetClauses();
	query.where = parseWhereClause();

	parseSolutionModifier(query);
	return query;
}

auto parseQuery() -> Query
{
	auto q =
		is("SELECT")    ? parseSelectQuery() :
		is("CONSTRUCT") ? parseConstructQuery() :
		is("DESCRIBE")  ? parseDescribeQuery() :
		is("ASK")       ? parseAskQuery() :
		throw ParseError("Expected SELECT, CONSTRUCT, DESCRIBE or ASK.");
	parseValuesClause();
	return q;
}

}
