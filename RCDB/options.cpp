#include "options.h"

Options::Options(int memtable_level = 100,
	int mem_table_size = 1000,
	std::string path = "./data/",
	std::string mem_table_name = "mem_table.dat",
	std::string index_name = "data_index.dat")
{
	this->mem_table_level = memtable_level;
	this->mem_table_size = mem_table_size;
	this->path = path;
	this->mem_table_name = mem_table_name;
	this->index_name = index_name;
}

Options::~Options()
{

}