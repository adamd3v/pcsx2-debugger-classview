#pragma once

#include "ui_StructureDialog.h"

#include <QtWidgets/QDialog>

#include "DebugTools/Structure.h"
#include "StructureView.h"
#include "StructureModel.h"

class StructureDialog : public QDialog
{
	Q_OBJECT

public:
	StructureDialog(StructureModel& model, QWidget* parent = nullptr);

	void assignStructure(const Structure& structure);

	void accepted();

private:
	Ui::StructureDialog m_ui;
	StructureModel& m_model;
	Structure m_structure;
};