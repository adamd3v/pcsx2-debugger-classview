#include "QtUtils.h"

#include <QtWidgets/QMenu>
#include <QtWidgets/QTabBar>
#include <QtGui/QPainter>

#include "StructureView.h"

StructureView::StructureView(const DebuggerViewParameters& parameters)
	: DebuggerView(parameters, DISALLOW_MULTIPLE_INSTANCES)
{
	m_ui.setupUi(this);

	m_ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);

	connect(m_ui.tableView, &QTableView::customContextMenuRequested, this, &StructureView::openContextMenu);
	connect(m_ui.tableView, &QTableView::doubleClicked, this, &StructureView::onDoubleClick);

	this->resizeColumns();
}

void StructureView::openContextMenu(QPoint pos)
{
	// Create a new context menu object
	QMenu* menu = new QMenu(m_ui.tableView);
	menu->setAttribute(Qt::WA_DeleteOnClose);

	// Check if the EmotionEngine is running
	if (cpu().isAlive())
	{
		// Add a "New Structure" context menu action
		QAction* newAction = menu->addAction(tr("New Structure"));
		// Connect its callbacks
		connect(newAction, &QAction::triggered, this, &StructureView::contextNew);
	}

	// Tell the menu to position itself at the cursor relative to the window
	menu->popup(m_ui.tableView->viewport()->mapToGlobal(pos));
}

void StructureView::contextNew()
{
	// Bring up the "New Structure" dialog
	// Add a new structure model after we're done
}

void StructureView::onDoubleClick(const QModelIndex& index)
{

}

void StructureView::resizeColumns()
{

}