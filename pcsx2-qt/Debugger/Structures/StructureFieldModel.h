#pragma once

#include <vector>

#include <QAbstractTableModel>
#include <QtWidgets/QHeaderView>

#include "DebugTools/Structure.h"

class StructureFieldModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	enum FieldColumns : int
	{
		NAME,
		SIZE,
		COLUMN_COUNT
	};

	static constexpr QHeaderView::ResizeMode HeaderResizeModes[FieldColumns::COLUMN_COUNT] = {
		QHeaderView::ResizeMode::ResizeToContents,
		QHeaderView::ResizeMode::ResizeToContents
	};

	explicit StructureFieldModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	bool insertFieldRows(int row, int count, std::vector<Structure::Field> fields, const QModelIndex& index = QModelIndex());
	bool removeRows(int row, int count, const QModelIndex& index = QModelIndex()) override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	bool setData(const QModelIndex& index, const QVariant& value, int role);

	void refreshData();

	Structure::Field& at(const size_t index) { return m_fields.at(index); }

private:
	std::vector<Structure::Field> m_fields;
};