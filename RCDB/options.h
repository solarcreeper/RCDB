#ifndef OPTIONS_H
#define OPTIONS_H
#include <string>
#include "file.h"

class Options
{
public:
	Options(int memtable_level = 100,
		int mem_table_size = 1000,
		std::string path = "./data/",
		std::string mem_table_name = "mem_table.dat",
		std::string index_name = "data_index.dat",
		std::string snapshot_path = "./snapshot/",
		int (*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size) = NULL);
		
	~Options();
	
public:
	int mem_table_level;
	int mem_table_size;
	std::string path;
	std::string mem_table_name;
	std::string index_name;
	std::string snapshot_path;
	int (*compare)(unsigned char* key, int key_size, unsigned char* value, int value_size);
};
#endif // !OPTIONS_H
