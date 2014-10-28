#include "QueryParser2.h"

namespace Xtreeme
{

auto parseExpression()
{
	return Expression{};
}

auto parseGGP()
{
	return GGP{};
}

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
	// TODO report error if this GGP is not a TriplesTemplate.
	return parseGGP();
}

inline auto parseSelectClause()
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

inline auto parseWhereClause()
{
	(void) try_match("WHERE");

	return parseGGP();
}

inline auto parseSolutionModifier(Query& query)
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
		query.where = parseTriplesTemplate();
		query.tpl = query.where;
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
	if (is("SELECT"))
		return parseSelectQuery();
	else if (is("CONSTRUCT"))
		return parseConstructQuery();
	else if (is("DESCRIBE"))
		return parseDescribeQuery();
	else if (is("ASK"))
		return parseAskQuery();
}

}
