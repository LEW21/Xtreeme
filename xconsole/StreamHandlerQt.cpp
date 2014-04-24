#include "StreamHandlerQt.h"

#include <libxtreeme/DataStream.h>
#include <libxtreeme/Solution.h>

#include "SolutionViewer.h"

StreamHandlerQt::StreamHandlerQt()
{
	connect(this, SIGNAL(solution(Xtreeme::Solution)), this, SLOT(show(Xtreeme::Solution)));
	qRegisterMetaType<Xtreeme::Solution>("Xtreeme::Solution");
}

void StreamHandlerQt::handle(const X::SharedPointer<const Xtreeme::DataStream>& stream)
{
	Xtreeme::Solution* solution = new Xtreeme::Solution();
	auto s = new X::SharedPointer<const Xtreeme::DataStream>(stream);

	stream->header.connect([=](const Xtreeme::Header& header) {
		*solution = Xtreeme::Solution(header);
	});

	stream->data.connect([=](const Xtreeme::Row& row) {
		solution->addRow(row);
	});

	stream->end.connect([=]() {
		emit this->solution(Xtreeme::Solution(*solution));
		delete s;
		delete solution;
	});
}

void StreamHandlerQt::show(const Xtreeme::Solution& sol)
{
	auto window = new SolutionViewer(sol);
	window->resize(800, 600);
	window->show();
}
