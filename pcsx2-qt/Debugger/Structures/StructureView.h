#pragma once

#include "ui_StructureView.h"

#include "DebuggerView.h"

class StructureView : public DebuggerView
{
	Q_OBJECT

public:
	StructureView(const DebuggerViewParameters& parameters);

	void openContextMenu(QPoint pos);
	void contextNew();

	void onDoubleClick(const QModelIndex& index);

	void resizeColumns();

private:
	Ui::StructureView m_ui;
};