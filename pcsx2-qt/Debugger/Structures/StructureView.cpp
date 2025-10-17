#include "QtUtils.h"

#include <QtWidgets/QMenu>
#include <QtWidgets/QTabBar>
#include <QtWidgets/QMessageBox>
#include <QtGui/QPainter>

#include "StructureView.h"
#include "StructureDialog.h"

StructureView::StructureView(const DebuggerViewParameters& parameters)
	: DebuggerView(parameters, DISALLOW_MULTIPLE_INSTANCES)
	, m_model(new StructureModel())
{
	m_ui.setupUi(this);

	m_ui.tableView->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(m_ui.tableView, &QTableView::customContextMenuRequested, this, &StructureView::openContextMenu);
	connect(m_ui.tableView, &QTableView::doubleClicked, this, &StructureView::onDoubleClick);

	m_ui.tableView->setModel(m_model);
	m_ui.tableView->horizontalHeader()->setSectionsMovable(true);
	this->resizeColumns();
}

void StructureView::openContextMenu(QPoint pos)
{
	QMenu* menu = new QMenu(m_ui.tableView);
	menu->setAttribute(Qt::WA_DeleteOnClose);

	QAction* newAction = menu->addAction(tr("New Structure"));
	connect(newAction, &QAction::triggered, this, &StructureView::contextNew);

	const QItemSelectionModel* selection = m_ui.tableView->selectionModel();

	if (selection->hasSelection())
	{
		QAction* editAction = menu->addAction(tr("Edit Structure"));
		connect(editAction, &QAction::triggered, this, &StructureView::contextEdit);

		QAction* deleteAction = menu->addAction(tr("Delete Structure"));
		connect(deleteAction, &QAction::triggered, this, &StructureView::contextDelete);
	}

	menu->popup(m_ui.tableView->viewport()->mapToGlobal(pos));
}

void StructureView::contextNew()
{
	StructureDialog* dialog = new StructureDialog(*m_model);
	connect(dialog, &QDialog::accepted, this, &StructureView::resizeColumns);
	dialog->setWindowTitle("New Structure");
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	dialog->show();
}

void StructureView::contextEdit()
{
	const QItemSelectionModel* selection = m_ui.tableView->selectionModel();

	if (!selection->hasSelection())
		return;

	const int row = selection->selectedIndexes().first().row();
	auto structureObject = m_model->at(row);

	StructureDialog* dialog = new StructureDialog(*m_model);
	connect(dialog, &QDialog::accepted, this, &StructureView::resizeColumns);
	dialog->assignStructure(structureObject);
	dialog->setWindowTitle("Edit Structure");
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	dialog->show();
}

void StructureView::contextDelete()
{
	QMessageBox confirmBox;
	confirmBox.setIcon(QMessageBox::Warning);
	confirmBox.setText("This action cannot be undone.");
	confirmBox.setInformativeText("Do you wish to delete this structure?");
	confirmBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

	int choice = confirmBox.exec();

	if (choice == QMessageBox::No)
		return;

	const QItemSelectionModel* selection = m_ui.tableView->selectionModel();

	if (!selection->hasSelection())
		return;

	QModelIndexList indices = selection->selectedIndexes();

	std::set<int> rows;
	for (QModelIndex index : indices)
		rows.emplace(index.row());

	for (auto row = rows.rbegin(); row != rows.rend(); row++)
		m_model->removeRows(*row, 1);
}

void StructureView::onDoubleClick(const QModelIndex& index)
{

}

void StructureView::resizeColumns()
{
	for (std::size_t i = 0; auto mode : StructureModel::HeaderResizeModes)
	{
		m_ui.tableView->horizontalHeader()->setSectionResizeMode(i, mode);
		i++;
	}
}