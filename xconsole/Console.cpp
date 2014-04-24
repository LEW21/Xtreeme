#include "Console.h"

#include <iostream>
#include <libxtreeme/SPARQLParser.h>
#include <libxtypes/IRI.h>
#include <libxtreeme/parser/ParseError.h>
#include <libxtreeme/Command.h>
#include <libxtreeme/Database.h>
#include <libxtreeme/RemoteQuery.h>

Console::Console(Xtreeme::Database* d)
	: db(d)
	, parser(newParser())
{}

Console::~Console()
{
	delete parser;
}

Xtreeme::SPARQLParser* Console::newParser()
{
	Xtreeme::SPARQLParser* ev = new Xtreeme::SPARQLParser(X::IRI(u"http://lew21.net/"));

	ev->query.connect([=](const Xtreeme::Query& query) {
		for (Xtreeme::Command* command : query)
		{
			if (command->type == Xtreeme::Command::OutputStream)
			{
				Xtreeme::OutputStream* oS = static_cast<Xtreeme::OutputStream*>(command);
				stream(oS->stream = new Xtreeme::DataStream());
			}
		}

		Xtreeme::RemoteQuery* remote = db->query(query);
		remote->start();
		std::cout << ":: Query sent." << std::endl;
	});

	return ev;
}

void Console::evaluateFragment(const QString& fragment)
{
	try
	{
		parser->parseFragment(fragment);
	}
	catch (Xtreeme::ParseError* e)
	{
		std::cerr << ":: " << (const char*) QString(*e).toUtf8() << '\n';

		delete parser;
		parser = newParser();
	}
}
