#include "StructureModel.h"
#include "QtUtils.h"

StructureModel::StructureModel(QObject* parent)
	: QAbstractTableModel(parent)
{

}

int StructureModel::rowCount(const QModelIndex& parent) const
{
	return 0;
}

int StructureModel::columnCount(const QModelIndex& parent) const
{
	return 0;
}

QVariant StructureModel::data(const QModelIndex& index, int role) const
{

}

QVariant StructureModel::headerData(const QModelIndex& index, int role) const
{

}