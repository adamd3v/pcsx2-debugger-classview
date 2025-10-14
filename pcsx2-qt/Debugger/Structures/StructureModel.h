#pragma once

#include <QtCore/QAbstractTableModel>
#include <QtWidgets/QHeaderView>

class StructureModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit StructureModel(QObject* parent = nullptr);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

	void refreshData();

private:
};