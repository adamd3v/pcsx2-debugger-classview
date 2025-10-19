#pragma once
#include <map>

struct Structure
{
	struct Field
	{
		std::string name;
		u32 address;
		u32 size;
	};

	Structure();

	std::string st_namespace;
	std::string st_class;
	u32 st_size;

	u32 start_address;

	std::vector<Field> fields;
};

// Static class for the management and storage of automatic/user-made structures.
class CStructure
{
public:
	static void addStructure(const Structure& structure);
	static void removeStructure(const Structure& structure);

	static void addField(Structure& structure, const Structure::Field& field);
	static void removeField(Structure& structure, std::string name);

	static void clearAllStructures();
	static void clearAllFields(Structure& structure);

	static Structure& at(const size_t i);
	static std::vector<Structure> getStructures();
	static std::vector<Structure::Field> getFields(const Structure& structure);

	static const Structure& getStructure(const std::string& name);
	static const Structure::Field& getField(const Structure& structure, const std::string& name);

	static void assignAddress(Structure& structure, const u32 address);

	static bool isAddressValid(u32 address);

private:
	static std::string getFullClassName(const Structure& structure);

	static std::map<std::string, Structure> s_structureMap;
};