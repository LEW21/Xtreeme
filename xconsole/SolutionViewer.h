#ifndef SolutionViewer_h
#define SolutionViewer_h

#include <QTableWidget>

namespace Xtreeme
{
	class Solution;
}

class SolutionViewer: public QTableWidget
{
	Q_OBJECT

public:
	SolutionViewer(const Xtreeme::Solution& solution, QWidget* parent = 0);

	void resizeEvent(QResizeEvent* event);
};

#endif
