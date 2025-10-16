#pragma once
#include "StructureDialog.h"

#include <QtWidgets/QDialog>
#include <QtWidgets/QMessageBox>

#include "DebugTools/Structure.h"

StructureDialog::StructureDialog(StructureModel& model, QWidget* parent)
	: m_model(model)
{
	m_ui.setupUi(this);

	connect(m_ui.buttonBox, &QDialogButtonBox::accepted, this, &StructureDialog::accepted);
	connect(m_ui.addIntButton, &QPushButton::clicked, this, &StructureDialog::clickedAddIntButton);
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

void StructureDialog::clickedAddIntButton(bool checked)
{
	Structure::Field field;
	field.name = "m_value";
	field.size = sizeof(s32);

	m_structure.st_size += field.size;

	m_structure.fields.push_back(field);
}