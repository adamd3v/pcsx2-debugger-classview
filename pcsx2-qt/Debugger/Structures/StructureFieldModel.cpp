#include "StructureDialog.h"
#include "StructureFieldModel.h"

StructureFieldModel::StructureFieldModel(QObject* parent)
	: QAbstractTableModel(parent)
{
	connect(this, &StructureFieldModel::dataChanged, this, &StructureFieldModel::refreshData);
}

int StructureFieldModel::rowCount(const QModelIndex& parent) const
{
	return m_fields.size();
}

int StructureFieldModel::columnCount(const QModelIndex& parent) const
{
	return FieldColumns::COLUMN_COUNT;
}

bool StructureFieldModel::insertFieldRows(int row, int count, std::vector<Structure::Field> fields, const QModelIndex& index)
{
	if (fields.size() != static_cast<size_t>(count))
		return false;

	beginInsertRows(index, row, row + (count - 1));

	m_fields.insert(m_fields.begin(), fields.begin(), fields.end());

	endInsertRows();

	return true;
}

bool StructureFieldModel::removeRows(int row, int count, const QModelIndex& index)
{
	const size_t begin_index = static_cast<size_t>(row);
	const size_t end_index = static_cast<size_t>(row + count);

	if (end_index > m_fields.size())
		return false;

	beginRemoveRows(index, row, row + count - 1);

	for (size_t i = begin_index; i < end_index; i++)
	{
		auto field = m_fields.at(i);
		// CStructure::removeField(m_structure, field.name);
	}

	endRemoveRows();
}

QVariant StructureFieldModel::data(const QModelIndex& index, int role) const
{
	const size_t row = static_cast<size_t>(index.row());

	if (!index.isValid() || row >= m_fields.size())
		return QVariant();

	const Structure::Field& field = m_fields.at(row);

	if (role == Qt::DisplayRole)
	{
		switch (index.column())
		{
			case FieldColumns::NAME:
				return QString::fromStdString(field.name);
			case FieldColumns::SIZE:
				return QString::number(field.size);
		}
	}

	return QVariant();
}

QVariant StructureFieldModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
	{
		switch (section)
		{
			case FieldColumns::NAME:
				return tr("NAME");
			case FieldColumns::SIZE:
				return tr("SIZE");
		}
	}
}

bool StructureFieldModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	return true;
}

void StructureFieldModel::refreshData()
{
	const QPointer<StructureFieldModel> model(this);

	QtHost::RunOnUIThread([model, this]() mutable {
		if (!model)
			return;

		model->beginResetModel();
		model->m_fields = m_fields;
		model->endResetModel();
	});
}