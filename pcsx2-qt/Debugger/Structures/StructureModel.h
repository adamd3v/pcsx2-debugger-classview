#pragma once

#include <QtCore/QAbstractTableModel>
#include <QtWidgets/QHeaderView>

#include "DebugTools/DebugInterface.h"
#include "DebugTools/Structure.h"

class StructureModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	enum StructureColumns : int
	{
		NAME,
		SIZE,
		COLUMN_COUNT
	};

	enum StructureRoles : int
	{
		DataRole = Qt::UserRole
	};

	static constexpr QHeaderView::ResizeMode HeaderResizeModes[StructureColumns::COLUMN_COUNT] = {
		QHeaderView::ResizeMode::ResizeToContents,
		QHeaderView::ResizeMode::ResizeToContents
	};

	explicit StructureModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role);
	bool insertStructureRows(int row, int count, std::vector<Structure> structures, const QModelIndex& index = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& index = QModelIndex()) override;

	void refreshData();

	Structure at(const int index) const { return m_structures.at(index); }

private:
	std::vector<Structure> m_structures;
};