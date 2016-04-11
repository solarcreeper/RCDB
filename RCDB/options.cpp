#include "options.h"

Options::Options(int memtable_level, 
	int mem_table_size, 
	std::string path, 
	std::string mem_table_name, 
	std::string index_name, 
	std::string snapshot_path,
	int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size))
{
	this->mem_table_level = memtable_level;
	this->mem_table_size = mem_table_size;
	this->path = path;
	this->mem_table_name = mem_table_name;
	this->index_name = index_name;
	this->snapshot_path = snapshot_path;
	this->compare = compare;

	File().createDir(this->path);
}

Options::~Options()
{

}