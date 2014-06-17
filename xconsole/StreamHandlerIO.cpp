#include "StreamHandlerIO.h"

#include <libxtreeme/DataStream.h>
#include <iostream>

void StreamHandlerIO::handle(const X::SharedPointer<const Xtreeme::DataStream>& stream)
{
	int* len = new int(1);
	auto s = new X::SharedPointer<const Xtreeme::DataStream>(stream);

	stream->header.connect([=](const Xtreeme::Header& header) {
		std::cout << '|';
		for (const QString& column : header)
		{
			std::cout << ' ' << (const char*) column.toUtf8() << " |";
			*len += 3 + column.size();
		}
		std::cout << std::endl;
	});

	stream->data.connect([=](const Xtreeme::Row& row) {
		std::cout << '|';
		for (const Xtreeme::Resource& res : row)
		{
			std::cout << ' ' << '(' << res.id << ')' << (const char*) res.asTurtle().toUtf8() << " |";
		}
		std::cout << std::endl;
	});

	stream->end.connect([=]() {
		for (int i = *len; i > 0; --i)
			std::cout << '-';
		std::cout << std::endl;
		delete s;
		delete len;
	});
}
