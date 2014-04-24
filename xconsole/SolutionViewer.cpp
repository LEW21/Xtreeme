#include "SolutionViewer.h"

#include <libxtreeme/Solution.h>

SolutionViewer::SolutionViewer(const Xtreeme::Solution& solution, QWidget* parent)
	: QTableWidget(solution.rows().size(), solution.header().size(), parent)
{
	QStringList columns;
	for (const QString& column : solution.header())
	{
		columns << column;
	}

	setHorizontalHeaderLabels(columns);

	QVector<Xtreeme::Row> rows = solution.rows();
	int size = rows.size();
	int cSize = columns.size();

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < cSize; ++j)
		{
			setItem(i, j, new QTableWidgetItem(rows[i][j].asTurtle()));
		}
	}
}

void SolutionViewer::resizeEvent(QResizeEvent* event)
{
	int cSize = columnCount();
	int w = width() / cSize - 5;
	for (int i = 0; i < cSize; ++i)
	{
		setColumnWidth(i, w);
	}

	QWidget::resizeEvent(event);
}
