#include "Structure.h"

#include <variant>

std::map<std::string, Structure> CStructure::s_structures;

Structure::Structure()
{
	st_namespace = std::string();
	st_class = std::string();
	st_size = 0;

	start_address = 0;
}

void CStructure::addStructure(const Structure& structure)
{
	std::string fullClassName;

	if (&structure == nullptr)
		return;

	if (structure.st_class.empty())
		return;

	if (!structure.st_namespace.empty())
	{
		fullClassName.append(structure.st_namespace);
		fullClassName.append("::");
	}

	fullClassName.append(structure.st_class);

	s_structures[fullClassName] = structure;
}

void CStructure::removeStructure(const Structure& structure)
{
	std::string fullClassName;

	if (&structure == nullptr)
		return;

	if (!structure.st_namespace.empty())
	{
		fullClassName.append(structure.st_namespace);
		fullClassName.append("::");
	}

	fullClassName.append(structure.st_class);

	s_structures.erase(fullClassName);
}

void CStructure::assignAddress(Structure& structure, const u32 address)
{
	structure.start_address = address;
}

void CStructure::clearAllStructures()
{
	s_structures.clear();
}

void CStructure::clearAllFields(Structure& structure)
{
	if (&structure == nullptr)
		return;

	structure.fields.clear();
}

bool CStructure::isAddressValid(const u32 address)
{
	return true;
}