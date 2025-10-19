#pragma once

#include "ui_StructureDialog.h"

#include <QtWidgets/QDialog>

#include "DebugTools/Structure.h"

#include "StructureView.h"
#include "StructureModel.h"
#include "StructureFieldModel.h"

class StructureDialog : public QDialog
{
	Q_OBJECT

public:
	StructureDialog(StructureModel& model, QWidget* parent = nullptr);

	void assignStructure(const Structure& structure);
	Structure& getStructure() { return m_structure; }

	void accepted();
	void addFieldClicked(bool clicked = false);

private:
	Ui::StructureDialog m_ui;
	StructureModel& m_model;
	StructureFieldModel* m_fieldModel;
	Structure m_structure;
};