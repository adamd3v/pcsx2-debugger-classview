#pragma once

#include "ui_StructureView.h"

#include "DebuggerView.h"
#include "StructureModel.h"

class StructureView : public DebuggerView
{
	Q_OBJECT

public:
	StructureView(const DebuggerViewParameters& parameters);

	void openContextMenu(QPoint pos);
	void contextNew();
	void contextEdit();
	void contextDelete();

	void onDoubleClick(const QModelIndex& index);

	void resizeColumns();

private:
	Ui::StructureView m_ui;

	StructureModel* m_model;
};