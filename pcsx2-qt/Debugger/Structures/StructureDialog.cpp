#include "StructureDialog.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>

StructureDialog::StructureDialog(StructureModel& model, QWidget* parent)
	: m_model(model)
{
	m_ui.setupUi(this);

	connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, &StructureDialog::accepted);
	connect(m_ui.toolButton, &QToolButton::clicked, this, &StructureDialog::addFieldClicked);

	Structure structure = getStructure();
	m_fieldModel = new StructureFieldModel();
	m_ui.tableView->setModel(m_fieldModel);
}

void StructureDialog::assignStructure(const Structure& structure)
{
	m_structure = structure;

	m_ui.lineEdit->setText(QString::fromStdString(m_structure.st_class));
}

void StructureDialog::accepted()
{
	std::string structName;

	if (m_ui.lineEdit->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Invalid Structure"), "A name was not set for the structure.");
		return;
	}

	structName = m_ui.lineEdit->text().toStdString();

	m_structure.st_class = structName;

	CStructure::addStructure(m_structure);

	m_model.insertStructureRows(0, 1, {m_structure});

	QDialog::accept();
}

void StructureDialog::addFieldClicked(bool clicked)
{
	Structure::Field field;
	field.name = "";
	field.size = 0;
	field.address = 0;

	CStructure::addField(m_structure, field);
	m_fieldModel->insertFieldRows(0, 1, {field});
}