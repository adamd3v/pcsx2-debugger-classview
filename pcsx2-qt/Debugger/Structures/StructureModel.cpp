#include "StructureModel.h"
#include "QtUtils.h"

#include "DebugTools/Structure.h"

StructureModel::StructureModel(QObject* parent)
	: QAbstractTableModel(parent)
{

}

int StructureModel::rowCount(const QModelIndex& parent) const
{
	return m_structures.size();
}

int StructureModel::columnCount(const QModelIndex& parent) const
{
	return StructureColumns::COLUMN_COUNT;
}

void StructureModel::refreshData()
{
	const QPointer<StructureModel> model(this);
}

QVariant StructureModel::data(const QModelIndex& index, int role) const
{
	const size_t row = static_cast<size_t>(index.row());

	if (!index.isValid() || row >= m_structures.size())
		return QVariant();

	const Structure& structure = m_structures.at(row);

	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
			case StructureColumns::NAME:
				return QString::fromStdString(structure.st_class);
			case StructureColumns::SIZE:
				return QString::number(structure.st_size);
		}
	}

	return QVariant();
}

QVariant StructureModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
			case StructureColumns::NAME:
				return tr("NAME");
			case StructureColumns::SIZE:
				return tr("SIZE");
			default:
				return QVariant();
		}
	}

	return QVariant();
}

bool StructureModel::insertStructureRows(int row, int count, std::vector<Structure> structures, const QModelIndex& index)
{
	if (structures.size() != static_cast<size_t>(count))
		return false;

	beginInsertRows(index, row, row + (count - 1));

	m_structures.insert(m_structures.begin(), structures.begin(), structures.end());

	endInsertRows();
	return true;
}

bool StructureModel::setData(const QModelIndex& index, const QVariant& value, int role) 
{
	if (role == Qt::EditRole)
	{
		if (index.column() == StructureColumns::NAME)
		{

		}

		emit dataChanged(index, index);
		return true;
	}

	return false;
}