#include "options.h"

Options::Options()
{
	
}

Options::~Options()
{

}

void Options::setOptions(int memtable_level,
	int mem_table_size,
	std::string path,
	std::string snapshot_path,
	int(*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size))
{
	this->mem_table_level = memtable_level;
	this->mem_table_size = mem_table_size;
	this->path = path;
	this->snapshot_path = snapshot_path;
	this->compare = compare;
	this->mem_table_name = "mem_table.dat";
	this->index_name = "data_index.dat";

	File().createDir(this->path);

}

int Options::getMemTableLevel()
{
	return this->mem_table_level;
}

int Options::getMemTableSize() 
{
	return this->mem_table_size;
}

std::string Options::getDataSavePath()
{
	return this->path;
}

std::string Options::getSnapshotPath()
{
	return this->snapshot_path;
}

std::string Options::getIndexName()
{
	return this->index_name;
}

std::string Options::getMemTableName()
{
	return this->mem_table_name;
}