#include "Structure.h"

#include <variant>

std::map<std::string, Structure> CStructure::s_structureMap;

Structure::Structure()
{
	st_namespace = std::string();
	st_class = std::string();
	st_size = 0;

	start_address = 0;
}

void CStructure::addStructure(const Structure& structure)
{
	std::string fullClassName = getFullClassName(structure);
	s_structureMap[fullClassName] = structure;
}

void CStructure::removeStructure(const Structure& structure)
{
	std::string fullClassName = getFullClassName(structure);
	s_structureMap.erase(fullClassName);
}

void CStructure::addField(Structure& structure, const Structure::Field& field)
{
	if (&field == nullptr)
		return;

	structure.fields.push_back(field);
}

void CStructure::removeField(Structure& structure, std::string name)
{
	if (name.empty())
		return;

	for (auto i = structure.fields.begin(); i != structure.fields.end(); i++)
	{
		auto field = *i;

		if (field.name.compare(name))
		{
			structure.fields.erase(i);
			return;
		}
	}
}

void CStructure::assignAddress(Structure& structure, const u32 address)
{
	structure.start_address = address;
}

void CStructure::clearAllStructures()
{
	s_structureMap.clear();
}

void CStructure::clearAllFields(Structure& structure)
{
	if (&structure == nullptr)
		return;

	structure.fields.clear();
}

std::vector<Structure> CStructure::getStructures()
{
	std::vector<Structure> structures;

	for (auto pair : s_structureMap)
		structures.push_back(pair.second);

	return structures;
}

std::vector<Structure::Field> CStructure::getFields(const Structure& structure)
{
	std::vector<Structure::Field> fields;

	for (auto pair : s_structureMap)
		fields.insert(fields.begin(), pair.second.fields.begin(), pair.second.fields.end());

	return fields;
}

bool CStructure::isAddressValid(const u32 address)
{
	return true;
}

std::string CStructure::getFullClassName(const Structure& structure)
{
	std::string fullClassName;

	if (&structure == nullptr)
		return "";

	if (!structure.st_namespace.empty())
	{
		fullClassName.append(structure.st_namespace);
		fullClassName.append("::");
	}

	fullClassName.append(structure.st_class);

	return fullClassName;
}