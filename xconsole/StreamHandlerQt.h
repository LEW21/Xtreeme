#ifndef StreamHandlerQt_h
#define StreamHandlerQt_h

#include <QObject>
#include "StreamHandler.h"

namespace Xtreeme
{
	class Solution;
}

class StreamHandlerQt: public QObject, public StreamHandler
{
	Q_OBJECT

public:
	StreamHandlerQt();
	void handle(const X::SharedPointer<const Xtreeme::DataStream>&);

signals:
	void solution(const Xtreeme::Solution&);

public slots:
	void show(const Xtreeme::Solution& sol);
};

#endif
